#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <dirent.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/sem.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

#define SIZE 1024
#define MUTEX 0
#define DIRC 1
#define FILEC 2
#define READER 3

typedef struct{
    bool fine;
    char mstring[SIZE];
} msg;


int WAIT(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,-1,0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, int num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo,+1,0}};
    return semop(sem_des, operazioni, 1);
}

void reader(msg* messaggio, int semfd, const char* path){
    DIR* dir = opendir(path);
    struct dirent* buffer;
    while((buffer = readdir(dir)) != NULL){
        if((strcmp(buffer->d_name, ".") == 0) || (strcmp(buffer->d_name, "..") == 0))
            continue;

        WAIT(semfd, READER);
        char tmp[SIZE];
        strcpy(tmp, path);
        strcat(tmp, buffer->d_name);
        struct stat sbuf;
        stat(tmp, &sbuf);
        if(S_ISDIR(sbuf.st_mode)){
            WAIT(semfd, MUTEX);
            messaggio->fine = false;
            strcpy(messaggio->mstring, tmp);
            SIGNAL(semfd, MUTEX);
            SIGNAL(semfd, DIRC);
        }
        else if(S_ISREG(sbuf.st_mode)){
            WAIT(semfd, MUTEX);
            messaggio->fine = false;
            strcpy(messaggio->mstring, tmp);
            SIGNAL(semfd, MUTEX);
            SIGNAL(semfd, FILEC);
        }
    }
    WAIT(semfd, MUTEX);
    messaggio->fine = true;
    strcpy(messaggio->mstring, "FINE");
    SIGNAL(semfd, MUTEX);
    SIGNAL(semfd, DIRC);

    WAIT(semfd, MUTEX);
    messaggio->fine = true;
    strcpy(messaggio->mstring, "FINE");
    SIGNAL(semfd, MUTEX);
    SIGNAL(semfd, FILEC);
    closedir(dir);
    exit(0);
}

void dir_consumer(msg* messaggio, int semfd, int n){
    while(n>0){
        WAIT(semfd, DIRC);
        WAIT(semfd, MUTEX);
        if(messaggio->fine)
            n--;
        else{
            struct stat buffer;
            if(stat(messaggio->mstring, &buffer) == -1){
                perror("statd");
                printf("---%s---\n", messaggio->mstring);
                exit(1);
            }
            printf("%s [directory]\n", messaggio->mstring);
        }
        SIGNAL(semfd, MUTEX);
        SIGNAL(semfd, READER);
    }
    exit(0);
}

void file_consumer(msg* messaggio, int semfd, int n){
    while(n>0){
        WAIT(semfd, FILEC);
        WAIT(semfd, MUTEX);
        if(messaggio->fine)
            n--;
        else{
            struct stat buffer;
            if(stat(messaggio->mstring, &buffer) == -1){
                perror("statf");
                printf("---%s---\n", messaggio->mstring);
                exit(1);
            }
            printf("%s [file di %d bytes]\n", messaggio->mstring, buffer.st_size);
        }
        SIGNAL(semfd, MUTEX);
        SIGNAL(semfd, READER);
    }
    exit(0);
}

int main(int argc, char ** argv){
    int memfd, semfd;
    msg* messaggio;

    if(argc<2){
        printf("Numero di parametri insufficiente\n");
        exit(0);
    }

    if((memfd = shmget(IPC_PRIVATE, sizeof(msg), IPC_CREAT | 0660)) == -1){
        perror("shmget");
        exit(1);
    }

    if((messaggio = (msg*) shmat(memfd, NULL, 0)) == NULL){
        perror("shmat");
        exit(1);
    }

    if((semfd = semget(IPC_PRIVATE, 4, IPC_CREAT | 0660)) == -1){
        perror("semget");
        exit(1);
    }

    semctl(semfd, MUTEX, SETVAL, 1);
    semctl(semfd, DIRC, SETVAL, 0);
    semctl(semfd, FILEC, SETVAL, 0);
    semctl(semfd, READER, SETVAL, 1);

    if(fork() == 0)
        dir_consumer(messaggio, semfd, argc-1);

    if(fork() == 0)
        file_consumer(messaggio, semfd, argc-1);

    for(int i=1; i<argc; i++){
        if(fork() == 0)
            reader(messaggio, semfd, argv[i]);
    }

    wait(NULL);
    wait(NULL);
    wait(NULL);

    if(shmctl(memfd, IPC_RMID, 0) == -1){
        perror("shmctl-r");
        exit(1);
    }

    if(semctl(semfd, 0, IPC_RMID, 0) == -1){
        perror("semctl-r");
        exit(1);
    }
}
