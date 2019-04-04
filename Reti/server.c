/* UDP Receiver - Server*/
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// --------------Dentro sockaddr_in c'è questo-----------
//	struct sockaddr_in {
//		short          sin_family;    /* AF_INET */
//		u_short        sin_port;      /* port number */
//		struct in_addr sin_addr;      /* Internet address */
//		char           sin_zero[8];   /* unused */
//	};

int main(int argc, char *argv[]) {
    FILE *file = fopen("tabella.txt", "w+"); // File che i due processi utilizzeranno per comunicare
    struct sockaddr_in server_addr; // SOCKetADDress INternet: struttura dati contente un "internet address"
    int sockfd; // variabile che conterrà il socket descriptor

    if (argc < 2) {
        printf("Use: receiver listening_PORT");
        return 0;
    }
    // Il secondo parametro indica il tipo di comunicazione SOCK_DGRAM è un socket datagram(si inviano messaggi) e non quindi un flusso continuo.
    // Il terzo parametro indica il protocollo da utilizzare, con 0 il SO sceglie quello più appropriato(in questo caso UDP con i datagram)
    // La system call socket crea quindi il socket e restituisce un integer che lo identifica (SOCKet File Descriptor)
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        printf("\nErrore nell'apertura del socket");
        return -1;
    }
    memset((char *)&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET; //Indica la famiglia di indirizzi con cui il socket può comunicare: quest'"acronimo" sta per Address Family InterNET(IPv4).
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Indica l'indirizzo effettivo, con INADDR_ANY, al momento del bind, si indica al sistema di accettare tutte le connessioni da qualsiasi interfaccia di rete presente nel sistema
    server_addr.sin_port = htons(atoi(argv[1])); // host to network short/long/... : https://bit.ly/2ViIvMS

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) { // La system call bind associa un socket ad un "internet address"
        printf("\nErrore nel binding. Errore %d \n", errno);
        return -1;
    }

    int pid = fork();

    if (pid == 0) { // Processo figlio
		struct sockaddr_in client_addr; // Struttura dati in cui verrà memorizzato l'"indirizzo" del client
        socklen_t length = sizeof(client_addr); // lunghezza dell'"indirizzo" del client
        char buffer[150];

        while(1) {
			// recvfrom mette il messaggio nel buffer e memorizza tutte le informazioni relative al client in client_addr
            recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &length); //Il terzo parametro è relativo a dei flag
            printf("From IP:%s Port:%d msg:%s \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer); // inet_ntoa converte l'indirizzo numerico in forma "xx.xx.xx.xx"
            fprintf(file, "%s\n%d\n%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer); // Scrive l'indirizzo, la porta ed il messaggio nel file in righe diverse
            fflush(file); // Forza la memorizzazione sul file
        }
    }
    else { // Processo padre
		struct sockaddr_in client_addr; // Struttura dati in cui verrà memorizzato l'"indirizzo" del client letto dal file(inizialmente è vuota, verra riempita in seguito)
		client_addr.sin_family = AF_INET;
		char indirizzo[50];
		char porta[50];
        char messaggio[50];
        
        while(1) {
			rewind(file);
            while (fgets(indirizzo, 50, file) != NULL) {
				fgets(porta, 50, file);
                fgets(messaggio, 50, file);
                client_addr.sin_addr.s_addr = inet_addr(indirizzo); 
				client_addr.sin_port = htons(atoi(porta));  
                sendto(sockfd, messaggio, strlen(messaggio) + 1, 0, (struct sockaddr *)&client_addr, sizeof(client_addr));
            }
            sleep(2);
        }
    }
    fclose(file);
}
