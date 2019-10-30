#include <stdio.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>

#define SERVER_PORT 3233
#define SIZE 256
#define MAX_BANNED 20
typedef struct{
	int connect_sockfd;
	struct sockaddr_in client_addr;
}service_arg;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long client_banned[MAX_BANNED];
unsigned long last_ip = 0;  
int banned_count = 0;
int banned = 0;

void handleError(char *const error_name)
{
  perror(error_name);
  exit(-1);
}

void setAddr(struct sockaddr_in *server_addr)
{
  server_addr->sin_family = AF_INET;
  server_addr->sin_addr.s_addr = INADDR_ANY;
  server_addr->sin_port = htons(SERVER_PORT);
}

char *handleTime()
{
  struct tm *retTime;
  char *tempo;
  time_t t = time(NULL); //prende il tempo in secondi a partire da 1 gennaio 1970
  retTime = localtime(&t); //restituisce un breakdown time, una struct in cui il tempo viene suddiviso in secondi, minuti, ore
  tempo=asctime(retTime)+'\n'; //formatta il breakdown time restituito
  return tempo;
}
int isBanned(struct sockaddr_in client_addr, int connect_sockfd){
	pthread_mutex_lock(&mutex);
	for (int i = 0; i < banned_count; i++) // check for banned clients
	{  
		  if (client_banned[i] == client_addr.sin_addr.s_addr)
		  {
			char *mess = "Sei un utente bannato\n";
			if (write(connect_sockfd, mess, strlen(mess) + 1) == -1)
			{
			  perror("check-banned");
			  exit(1);
			}
			close(connect_sockfd);
			pthread_mutex_unlock(&mutex);	
			return 1;
		  }
	}

	if (last_ip == client_addr.sin_addr.s_addr)
	{
	  client_banned[banned_count++] = last_ip;
	  char *mess = "Sei stato bannato\n";
	  if (write(connect_sockfd, mess, strlen(mess) + 1) == -1)
	  {
		perror("check-banned");
		exit(1);
	  }
	  pthread_mutex_unlock(&mutex);	
	  return 1;
	}
	pthread_mutex_unlock(&mutex);	
	return 0;	
}

void service(service_arg * arg)
{
  int connect_sockfd = arg->connect_sockfd;
  struct sockaddr_in client_addr = arg->client_addr;
  char buffer[SIZE];
  int bytes_read = 0;
  int count = 0;
  char *reply; //stringa per la risposta
  while ((bytes_read = read(connect_sockfd, buffer, SIZE - 1)) > 0)
  {
    buffer[bytes_read] = '\0';

    printf("%s", buffer);

    if (strncmp(buffer, "TIME", strlen("TIME")) == 0)
    {
		reply = handleTime();
		if((++count)==2 && isBanned(client_addr, connect_sockfd))
		{
			close(connect_sockfd);
			pthread_exit(NULL);	
		}
	}
    else {
		reply = "N/A\n";
		count = 0;
	}
	
    if (write(connect_sockfd, reply, strlen(reply) + 1) == -1)
    {
      perror("write-service");
      pthread_exit(NULL);
    }
  }

  if (bytes_read < 0)
    perror("read-service");

  close(connect_sockfd);
  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_t thread1;
  struct sockaddr_in server_addr, client_addr;
  socklen_t client_len = sizeof(client_addr);
  int sockfd, connect_sockfd;


  /*for (int i = 0; i < DIM; i++)
    client_banned[i] = 1234;
  */
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    handleError("socket");

  setAddr(&server_addr);

  int enable = 1;
  if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) ==-1)    //don't wait for bind() "address already in use"
    handleError("setsockopt");
  
  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    handleError("bind");

  if (listen(sockfd, 10) == -1)
    handleError("listen");

  while (1)
  {
    banned = 0;

    if (banned_count >= MAX_BANNED)
      printf("Numero massimo di utenti bannati raggiunto\n");

    if ((connect_sockfd = accept(sockfd, (struct sockaddr *) &client_addr, &client_len)) == -1)
    {
      close(sockfd);
      handleError("connect_accept");
    }
  
    if(!isBanned(client_addr, connect_sockfd))
    {
		last_ip = client_addr.sin_addr.s_addr;
		service_arg * arg;
		arg->connect_sockfd = connect_sockfd;
		arg->client_addr = client_addr;
		pthread_create(&thread1, NULL,(void *) &service, (void *) arg);	
	}
	
    
  }
  //pthread_join(thread1,NULL); //si aspetta la terminazione del thread
  exit(0);
}
