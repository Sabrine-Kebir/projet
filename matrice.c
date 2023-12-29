#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 100 
#define N MAX_SIZE    

int n1 =3, m1=3 ; 
int n2=3 , m2=3 ; 
int B[MAX_SIZE][MAX_SIZE];
int C[MAX_SIZE][MAX_SIZE];
int A[MAX_SIZE][MAX_SIZE];
int T[MAX_SIZE]; 

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 

void *producer(void *arg) {
    int row = *((int *)arg);

    if (row >= n1) {
        fprintf(stderr, "Erreur : Indice de ligne en dehors des limites.\n");
        pthread_exit(NULL);
    }

    for (int j = 0; j < m2; j++) {
        int result = 0;

        for (int k = 0; k < n2; k++) {
            if (k >= m1 || j >= m2 || k >= n2 || j >= m2) {
                fprintf(stderr, "Erreur : Indices de colonne en dehors des limites.\n");
                pthread_exit(NULL);
            }

            result += B[row][k] * C[k][j];
        }

        pthread_mutex_lock(&mutex);
        T[row * m2 + j] = result; 
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            pthread_mutex_lock(&mutex);
            A[i][j] = T[i * m2 + j]; 
            pthread_mutex_unlock(&mutex);
        }
    }

    pthread_exit(NULL);
}

int main() {
  
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            B[i][j] = rand() % 10; 
        }
    }

    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            C[i][j] = rand() % 10; 
        }
    }
    
    pthread_t producer_threads[MAX_SIZE];
    int thread_args[MAX_SIZE];
    for (int i = 0; i < n1; i++) {
        thread_args[i] = i;
        pthread_create(&producer_threads[i], NULL, producer, &thread_args[i]);
    }

    pthread_t consumer_thread;
    pthread_create(&consumer_thread, NULL, consumer, NULL);


    for (int i = 0; i < n1; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    pthread_join(consumer_thread, NULL);

    
    printf("Matrice résultante A :\n");
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            printf("%d ", A[i][j]);
        }
        printf("\n");
    }

    return 0;
}

