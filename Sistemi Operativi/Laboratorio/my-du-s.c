#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/stat.h>
#include <stdbool.h>

#define SIZE 1024
#define MUTEX 0
#define PADRE 1
#define SCANNER 2
#define STATER 3

typedef struct {
   long m_size;
   char stringa[SIZE];
} msg;

int WAIT(int sem_des, unsigned short int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, unsigned short int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

void scanner(msg* mem_addr, int sem_des, const char * path, int check){
    struct stat buffer;
    if(stat(path, &buffer) == -1){
        perror("stat_sc");
        exit(0);
    }
    if(S_ISREG(buffer.st_mode)){
        WAIT(sem_des, MUTEX);
        mem_addr->m_size = 0;
        strcpy(mem_addr->stringa, path);
        //printf("prova scanner: %s\n", mem_addr->stringa);
        SIGNAL(sem_des, MUTEX);
        SIGNAL(sem_des, STATER);
        WAIT(sem_des, SCANNER);
    }
    else if(S_ISDIR(buffer.st_mode)){
        DIR* dir = opendir(path);
        struct dirent* dir_ent;
        while((dir_ent = readdir(dir)) != NULL){
            char tmp_path[SIZE];
            strcpy(tmp_path, path);
            if(strcmp(dir_ent->d_name, ".") == 0 || strcmp(dir_ent->d_name, "..") == 0)
                continue;
            scanner(mem_addr, sem_des, strcat(strcat(tmp_path, "/"), dir_ent->d_name), check+1);
        }
    }
    if(check == 0){
        WAIT(sem_des, MUTEX);
        strcpy(mem_addr->stringa, "");
        mem_addr->m_size = -1;
        SIGNAL(sem_des, MUTEX);
        SIGNAL(sem_des, STATER);
        exit(0);
    }
}

void stater(msg* mem_addr, int sem_des, int n){
    struct stat buffer;
    while(n>0){
        WAIT(sem_des, STATER);
        WAIT(sem_des, MUTEX);
        if(mem_addr->m_size == -1)
            n--;
        else{
            //printf("prova stater: %s\n", mem_addr->stringa);
            if(stat(mem_addr->stringa, &buffer) == -1){
                perror("stat_st");
                exit(0);
            }
            mem_addr->m_size = buffer.st_blocks;
            //printf("blocks = %d\n", buffer.st_blocks);
        }
        SIGNAL(sem_des, MUTEX);
        SIGNAL(sem_des, PADRE);
    }
    exit(0);
}


int main(int argc, char** argv){
    int mem_des, sem_des;
    msg* mem_addr;


    if((mem_des = shmget(IPC_PRIVATE, sizeof(msg)-sizeof(long), IPC_CREAT | 0660)) == -1){
        perror("shmget");
        exit(1);
    }

    if((mem_addr = (msg*) shmat(mem_des, NULL, 0)) == -1){
        perror("shmat");
        exit(1);
    }

    if((sem_des = semget(IPC_PRIVATE, 4, IPC_CREAT | 0660)) == -1){
        perror("semget");
        exit(1);
    }

    semctl(sem_des, MUTEX, SETVAL, 1);
    semctl(sem_des, PADRE, SETVAL, 0);
    semctl(sem_des, SCANNER, SETVAL, 0);
    semctl(sem_des, STATER, SETVAL, 0);

    for(int i=1; i<argc; i++)
        if(fork()==0)
            scanner(mem_addr, sem_des, argv[i], 0);

    if(fork() == 0)
        stater(mem_addr, sem_des, argc-1);

    int sum[argc-1];
    for(int i = 0; i<argc-1; i++)
        sum[i] = 0;
    for(int i=0; i<argc-1; i++){
        bool flag = false;
        while(true){
            WAIT(sem_des, PADRE);
            WAIT(sem_des, MUTEX);
            if(mem_addr->m_size != -1){
                for(int j=1; j<argc; j++)
                    if(strstr(mem_addr->stringa, argv[j]))
                        sum[j-1] += mem_addr->m_size;
            }
            else
                flag = true;
            SIGNAL(sem_des, MUTEX);
            SIGNAL(sem_des, SCANNER);
            if(flag)
                break;
        }
    }

    for(int i = 0; i<argc-1; i++)
        printf("%d\n", sum[i]);

    if(shmctl(mem_des, IPC_RMID, NULL) == -1){
        perror("shmctl-r");
        exit(1);
    }

    if(semctl(sem_des, 0, IPC_RMID, NULL) == -1){
        perror("semctl-r");
        exit(1);
    }

    return 0;
}
