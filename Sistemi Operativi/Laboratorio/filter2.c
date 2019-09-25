//INCOMPLETO - ERRORE INVALID ARGUMENT SU semop

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <stdbool.h>

#define SIZE 1024
#define MUTEX 0
#define PADRE 1

typedef struct{
    unsigned long mtype;
    char stringa[SIZE];
} msg;

int WAIT(int sem_des, unsigned short num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo, -1, 0}};
    return semop(sem_des, operazioni, 1);
}

int SIGNAL(int sem_des, unsigned short num_semaforo){
    struct sembuf operazioni[1] = {{num_semaforo, +1, 0}};
    return semop(sem_des, operazioni, 1);
}

void substrS(char * stringa, int start){
    char res[SIZE];
    strcpy(res, stringa);
    for(int i=start; i<strlen(stringa); i++){
        stringa[i-start] = res[i];
    }
    stringa[strlen(res)-1] = '\0';
}

int Filter(int n, char* file_path, char* filtro, msg* messaggio, int semfd, int last){
    bool flag = false;
    bool upper = false;
    bool lower = false;
    bool sost = false;

    if(filtro[0] == '^')
        upper = true;
    else if(filtro[0] == '^')
        lower = true;

    substrS(filtro, 1);

    while(true){
        WAIT(semfd, n);
        WAIT(semfd, MUTEX);
        if(strcmp(messaggio->stringa, "FINE") == 0)
            flag = true;
        else{
            if(upper){
                char * tmp;
                tmp = strstr(messaggio->stringa, filtro);
                if(tmp != NULL){
                    printf("La sottostringa è: %s\n", tmp);
                    printf("Il filtro è: %s\n", filtro);
                    printf("La linea è: %s\n", messaggio->stringa);
                    break;
                }
            }
        }
        SIGNAL(semfd, MUTEX);
        if(n == last)
            SIGNAL(semfd, PADRE);
        else
            SIGNAL(semfd, n+1);

        if(flag)
            break;
    }
    exit(0);
}

int main(int argc, char** argv){
    int memfd, semfd;
    char path[SIZE];
    msg* messaggio;

    if(argc<3){
        printf("Numero di parametri insufficiente\n");
        exit(0);
    }

    if((memfd = shmget(IPC_PRIVATE, sizeof(msg) - sizeof(long), IPC_CREAT | 0660)) == -1){
        perror("shmget");
        exit(1);
    }

    if((messaggio = (msg*) shmat(memfd, NULL, 0)) == NULL){
        perror("shmat");
        exit(1);
    }

    if((semfd = semget(IPC_PRIVATE, 2, IPC_CREAT | 0660) == -1)){
        perror("semfd");
        exit(1);
    }

    if(semctl(semfd, MUTEX, SETVAL, 0) == -1){
        perror("semctl-s");
        exit(1);
    }
    semctl(semfd, PADRE, SETVAL, 0);
    /*for(int i=2; i<argc; i++){
        semctl(semfd, i, SETVAL, 0);
    }*/

    strcpy(path, argv[1]);

    /*for(int i=2; i<argc; i++){
        if(fork() == 0)
            Filter(i, path, argv[i], messaggio, semfd, argc-1);
    }*/

    FILE* file = fopen(path, "r");
    char line[SIZE];

    while(fgets(line, SIZE, file) != NULL){
        WAIT(semfd, MUTEX);
        strcpy(messaggio->stringa, line);
        SIGNAL(semfd, MUTEX);
        SIGNAL(semfd, 2);
        WAIT(semfd, PADRE);
        WAIT(semfd, MUTEX);
        printf("%s\n", messaggio->stringa);
        SIGNAL(semfd, MUTEX);
    }
    WAIT(semfd, MUTEX);
    strcpy(messaggio->stringa, "FINE");
    SIGNAL(semfd, MUTEX);
    //SIGNAL(semfd, 2);
    //WAIT(semfd, PADRE);

    if(shmctl(memfd, IPC_RMID, NULL) == -1){
        perror("shmctl");
        exit(1);
    }

    if(semctl(semfd, 0, IPC_RMID, 0) == -1){
        perror("semctl");
        exit(1);
    }

    exit(0);

}
