/* UDP Sender - Client*/
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
int main(int argc, char *argv[]) {
    struct sockaddr_in interlocutore, local_addr; // indirizzo del server a cui si manderanno i messaggi
    char messaggio[100];
    int sockfd;


    if (argc < 3) {
        printf("Use: sender IP_dest PORT_dest");
        return 0;
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        printf("\nErrore nell'apertura del socket");
        return -1;
    }

    memset((char *)&local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    local_addr.sin_port = htons(atoi(argv[2]));

    if (bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr)) < 0) { // La system call bind associa un socket ad un "internet address"
        printf("\nErrore nel binding. Errore %d \n", errno);
        return -1;
    }

    interlocutore.sin_family = AF_INET;
    interlocutore.sin_addr.s_addr = inet_addr(argv[1]);
    interlocutore.sin_port = htons(atoi(argv[2]));

    if(connect(sockfd, (struct sockaddr *)&interlocutore, (socklen_t ) sizeof(interlocutore)) < 0) {
        listen(sockfd, 5);
        socklen_t len = sizeof(interlocutore);
        sockfd = accept(sockfd, (struct sockaddr *) &interlocutore, &len);
        printf("Connessione Stabilita - S\n");
    }
    else
        printf("Connessione Stabilita - C\n");

    int pid = fork();

    if (pid == 0) { // Processo figlio
        while (1) {
            scanf("%s", messaggio);
            int len = send(sockfd, messaggio, strlen(messaggio) + 1, 0);
            if(len > 0)
                printf("\rTu: %s\n", messaggio);
        }
    } else { // Processo padre
        // Essendo che i due processi hanno diverso spazio di indirizzamento, possiamo riutilizzare interlocutore per ricevere senza preoccuparci se l'altro processo ha finito
        while (1) {
            int len = recv(sockfd, messaggio, sizeof(messaggio), 0);
            if(len > 0)
                printf("Interlocutore: %s\n", messaggio);
        }
    }
}
