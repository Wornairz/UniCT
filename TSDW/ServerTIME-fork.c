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

#define SERVER_PORT 3233
#define SIZE 256
#define DIM 20

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
  time_t t = time(NULL);
  retTime = localtime(&t);

  tempo=asctime(retTime)+'\n';
  
  //sprintf(tempo, "%d:%d", retTime->tm_hour, retTime->tm_min); //se non funziona provare "%d:%d\0"
  //sprintf(tempo, asctime(retTime));
  return tempo;
}

void service(int sockfd)
{
  char buffer[SIZE];
  int bytes_read = 0;
  char *reply; //stringa per la risposta

  while ((bytes_read = read(sockfd, buffer, SIZE - 1)) > 0)
  {
    buffer[bytes_read] = '\0';

    printf("%s", buffer);

    if (strncmp(buffer, "TIME", strlen("TIME")) == 0)
      reply = handleTime();
    else
      reply = "N/A\n";

    if (write(sockfd, reply, strlen(reply) + 1) == -1)
    {
      perror("write-service");
      exit(1);
    }
  }

  if (bytes_read < 0)
    perror("read-service");

  close(sockfd);
  exit(0);
}

int main(int argc, char *argv[])
{
  struct sockaddr_in server_addr, client_addr;
  int sockfd, connect_sockfd;
  unsigned long last_ip = 0;
  unsigned long client_banned[DIM];
  int current_len = 0;
  int banned = 0;


  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    handleError("socket");

  setAddr(&server_addr);

  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1)
    handleError("bind");

  if (listen(sockfd, 10) == -1)
    handleError("listen");

  socklen_t client_len = sizeof(client_addr);


  while (1)
  {
    banned = 0;

    if (current_len >= DIM)
      printf("Numero massimo di utenti bannati raggiunto\n");

    if ((connect_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_len)) == -1)
    {
      close(sockfd);
      handleError("connect_accept");
    }

    for (int i = 0; i < current_len; i++)
      if (client_banned[i] == client_addr.sin_addr.s_addr)
      {
        banned = 1;
        char *mess = "Sei un utente bannato";
        printf("%s\n", mess);
        if (write(sockfd, mess, strlen(mess) + 1) == -1)
        {
          perror("check-banned");
          exit(1);
        }
        break;
      }

    if (!banned && last_ip == client_addr.sin_addr.s_addr)
    {
      client_banned[current_len] = last_ip;
      char *mess = "Sei stato bannato";
      printf("%s\n", mess);
      if (write(sockfd, mess, strlen(mess) + 1) == -1)
      {
        perror("check-banned");
        exit(1);
      }
      current_len++;
    }
    else if (!banned)
    {
      last_ip = client_addr.sin_addr.s_addr;
      if (fork() == 0)
        service(connect_sockfd);
    }
  }
  close(sockfd);
  exit(0);
}