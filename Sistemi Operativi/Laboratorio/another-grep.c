#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/msg.h>
#include <ctype.h>
#include <string.h>
#include <sys/ipc.h>
#include <stdbool.h>

#define SIZE 1024

typedef struct{
    unsigned long mtype;
    char mstring[SIZE];
} msg;

void R(char* file_path, int* fildes){
    FILE* file = fopen(file_path, "r");
    FILE* pipa = fdopen(fildes[1], "w");
    char line[SIZE];
    while(fgets(line, SIZE, file) != NULL){
        fputs(line, pipa);
    }
    fclose(pipa);
    fclose(file);
}

void W(int msg_des){
    msg messaggio;
    while(true){
        if(msgrcv(msg_des, &messaggio, sizeof(msg)-sizeof(long), 1, 0) == -1){
            perror("msgrcv");
            exit(1);
        }
        if(strcmp(messaggio.mstring, "FINE") == 0)
            break;
        else
            printf("%s", messaggio.mstring);
    }
    exit(0);
}

int main(int argc, char ** argv){
    int fildes[2];
    int msg_des;

    if(argc<3){
        printf("Numero di parametri insufficiente\n");
        exit(0);
    }

    char parola[SIZE];
    strcpy(parola, argv[1]);
    char file_path[SIZE];
    strcpy(file_path, argv[2]);

    if(pipe(fildes) == -1){
        perror("pipe");
        exit(1);
    }

    if(fork() == 0){
        close(fildes[0]);
        R(file_path, fildes);
        close(fildes[1]);
        exit(0);
    }

    close(fildes[1]);

    if((msg_des = msgget(IPC_PRIVATE, IPC_CREAT | 0660)) == -1){
        perror("msgget");
        exit(1);
    }

    if(fork() == 0){
        close(fildes[0]);
        W(msg_des);
    }

    char line[SIZE];
    FILE* pipa = fdopen(fildes[0], "r");
    msg messaggio;
    while(fgets(line, SIZE, pipa) != NULL){
        if(strstr(line, parola) != NULL){
            messaggio.mtype = 1;
            strcpy(messaggio.mstring, line);
            sleep(1);
            if(msgsnd(msg_des, &messaggio, sizeof(msg)-sizeof(long), 0) == -1){
                perror("msgsnd");
                exit(1);
            }
        }
    }
    messaggio.mtype = 1;
    strcpy(messaggio.mstring, "FINE");
    sleep(1);
    msgsnd(msg_des, &messaggio, sizeof(msg)-sizeof(long), 0);

    if((msg_des = msgctl(msg_des, IPC_RMID, NULL)) == -1){
        perror("msgctl-r");
        exit(1);
    }
    exit(0);
}
