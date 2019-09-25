#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SIZE 2048

typedef struct{
    unsigned long tipo;
    char stringa[SIZE];
} msg;


void figlio_file(int coda_rcv, int coda_snd, char* file_path, int id){
    FILE* file;
    if((file = fopen(file_path, "r")) == NULL){
        perror("fopen");
        exit(1);
    }
    char file_lines[SIZE][SIZE];
    int tot_line = 0;

    while(tot_line < SIZE && fgets(file_lines[tot_line++], SIZE, file) != NULL){}

    msg messaggio;
    char words[10][SIZE];
    int wc = 0;
    while(true){
        if(msgrcv(coda_rcv, &messaggio, sizeof(msg)-sizeof(long), id, 0) == -1){
            perror("msgrcvf");
            exit(1);
        }
        if(strcmp(messaggio.stringa, "FINE") == 0)
            break;
        else{
            strcpy(words[wc++], messaggio.stringa);
        }
    }

    for(int i=0; i<tot_line; i++){
        for(int j=0; j<wc; j++){
            if(strstr(file_lines[i], words[j]) != NULL){
                snprintf(messaggio.stringa, SIZE, "%s@%s:%d:%s", words[j], file_path, i, file_lines[i]);
                messaggio.tipo = 999;
                sleep(1);
                if(msgsnd(coda_snd, &messaggio, sizeof(msg)-sizeof(long), 0) == -1){
                    perror("msgsndf");
                    exit(1);
                }
            }
        }
    }
    strcpy(messaggio.stringa, "FINE");
    messaggio.tipo = 999;
    msgsnd(coda_snd, &messaggio, sizeof(msg)-sizeof(long), 0);
    exit(0);
}


int main(int argc, char** argv){
    int word_count, file_count;
    char *words[10], *files[10];
    word_count = file_count = 0;
    bool flag = false;
    for(int i=1; i<argc; i++){
        if(strcmp(argv[i], "@") == 0){
            flag = true;
            continue;
        }
        if(flag){
            files[file_count++] = argv[i];
        }
        else {
            words[word_count++] = argv[i];
        }
    }

    int coda_richieste, coda_risposte;

    if((coda_richieste = msgget(IPC_PRIVATE, IPC_CREAT | 0660)) == -1){
        perror("msgget1");
        exit(1);
    }
    if((coda_risposte = msgget(IPC_PRIVATE, IPC_CREAT | 0660)) == -1){
        perror("msgget2");
        exit(1);
    }

    for(int i=0; i<file_count; i++)
        if(fork() == 0)
            figlio_file(coda_richieste, coda_risposte, files[i], i+1);

    msg messaggio;
    for(int j=0; j<file_count; j++){
        for(int i=0; i<word_count; i++){
            messaggio.tipo=j+1;
            strcpy(messaggio.stringa, words[i]);
            sleep(1);
            if(msgsnd(coda_richieste, &messaggio, sizeof(msg)-sizeof(long), 0) == -1){
                perror("msgsendp");
                exit(1);
            }
        }
        messaggio.tipo=j+1;
        strcpy(messaggio.stringa, "FINE");
        sleep(1);
        msgsnd(coda_richieste, &messaggio, sizeof(msg)-sizeof(long), 0);
    }

    while(true){
        if(msgrcv(coda_risposte, &messaggio, sizeof(msg)-sizeof(long), 999, 0) == -1){
            perror("msgrcvp");
            exit(1);
        }
        if(strcmp(messaggio.stringa, "FINE") == 0)
            break;
        printf("%s\n", messaggio.stringa);
    }

    if(msgctl(coda_richieste, IPC_RMID, NULL) == -1){
        perror("msgctl1");
        exit(1);
    }
    if(msgctl(coda_risposte, IPC_RMID, NULL) == -1){
        perror("msgctl2");
        exit(1);
    }


    exit(0);
    return 0;
}
