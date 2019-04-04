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
    struct sockaddr_in server_addr, client_addr; // indirizzo del server a cui si manderanno i messaggi
    socklen_t length = sizeof(server_addr);
    char messaggio[100];
    int sockfd;
    int n;


    if (argc < 3) {
        printf("Use: sender IP_dest PORT_dest");
        return 0;
    }
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\nErrore nell'apertura del socket");
        return -1;
    }
    
    memset((char *)&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET; 
    client_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    client_addr.sin_port = htons(atoi(argv[2])); 

    if (bind(sockfd, (struct sockaddr *)&client_addr, sizeof(client_addr)) < 0) { // La system call bind associa un socket ad un "internet address"
        printf("\nErrore nel binding. Errore %d \n", errno);
        return -1;
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));
    printf("\nInserisci un numero intero ");
    scanf("%d", &n);
    int pid = fork();
    
    
    if (pid == 0) { // Processo figlio
        for (int i = 0; i < 10; ++i) {
            sprintf(messaggio, "%d", i + n);
            printf("%s\n", messaggio);
            sendto(sockfd, messaggio, strlen(messaggio) + 1, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        }
    } else { // Processo padre
		// Essendo che i due processi hanno diverso spazio di indirizzamento, possiamo riutilizzare server_addr per ricevere senza preoccuparci se l'altro processo ha finito
        while (1) {
            recvfrom(sockfd, messaggio, sizeof(messaggio), 0, (struct sockaddr *)&server_addr, &length);
            printf("From IP:%s Port:%d msg:%s \n", inet_ntoa(server_addr.sin_addr), ntohs(server_addr.sin_port), messaggio);
        }
    }
}
