#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

pthread_mutex_t player_one = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t player_two = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; //ho dei dubbi sulla reale utilità di questa mutex

int posizione = 0;
int vittorie_tp0 = 0;
int vittorie_tp1 = 0;

void first_player(){
    while (vittorie_tp0 < 10 && vittorie_tp1 < 10)    {
        printf("Primo giocatore: %d\n", posizione);
        int recupero = rand() % 4;
        int forza = rand() % 6;
        sleep(recupero);
        pthread_mutex_lock(&mutex);
        if (posizione >= 10)        {
            ++vittorie_tp1;
            posizione = 0;
            printf("\t\t\t\tVittorie Secondo giocatore: %d\n", vittorie_tp1);
            pthread_mutex_unlock(&player_two);
        }else{
            posizione -= forza;
            if(posizione <= -10)
                pthread_mutex_lock(&player_one);
        }
        pthread_mutex_unlock(&mutex);   
    }
    pthread_exit(NULL);
}

void second_player(){
    while (vittorie_tp1 < 10 && vittorie_tp0 < 10)    {
        printf("\t\t\t\tSecondo giocatore: %d\n", posizione);
        int recupero = rand() % 4;
        int forza = rand() % 6;
        sleep(recupero);
        pthread_mutex_lock(&mutex);
        if (posizione <= -10){
            ++vittorie_tp0;
            posizione = 0;
            printf("Vittorie Primo giocatore: %d\n", vittorie_tp0);
            pthread_mutex_unlock(&player_one);
        }else{
            posizione += forza;
            if(posizione >= 10)
                pthread_mutex_lock(&player_two);
        }   
        pthread_mutex_unlock(&mutex);
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[]){
    pthread_t tp[2];
    srand(time(NULL));
    pthread_create(&tp[0], NULL, (void*) &first_player, ((void *)0));
    pthread_create(&tp[1], NULL, (void*) &second_player, ((void *)0));

    pthread_join(tp[0], NULL);
    pthread_join(tp[1], NULL);
    if(vittorie_tp0 > vittorie_tp1)
        printf("first player ha vinto con %d vittorie\n", vittorie_tp0);
    else
        printf("second player ha vinto con %d vittorie\n", vittorie_tp1);
    exit(0);
}