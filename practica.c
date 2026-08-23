#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N_FILOSOFOS  5
#define N_CICLOS     3

sem_t tenedor[N_FILOSOFOS];
sem_t acceso;

void pensar(int id) {
    printf("Filosofo %d  ->  PENSANDO...\n", id);
    sleep((rand() % 3) + 1);
}

void comer(int id) {
    printf("Filosofo %d  ->  COMIENDO  [tenedores %d y %d]\n",
           id, id, (id + 1) % N_FILOSOFOS);
    sleep((rand() % 2) + 1);
}

void *filosofo(void *arg) {
    int id  = *(int *)arg;
    int izq = id;
    int der = (id + 1) % N_FILOSOFOS;

    for (int c = 0; c < N_CICLOS; c++) {
        pensar(id);

        sem_wait(&acceso);

        sem_wait(&tenedor[izq]);
        printf("Filosofo %d  ->  Tomo tenedor IZQUIERDO (%d)\n", id, izq);

        sem_wait(&tenedor[der]);
        printf("Filosofo %d  ->  Tomo tenedor DERECHO   (%d)\n", id, der);

        comer(id);

        sem_post(&tenedor[izq]);
        sem_post(&tenedor[der]);
        sem_post(&acceso);

        printf("Filosofo %d  ->  Solto tenedores.\n\n", id);
    }

    printf("==> Filosofo %d  TERMINO sus %d ciclos.\n", id, N_CICLOS);
    return NULL;
}

int main(void) {
    pthread_t hilos[N_FILOSOFOS];
    int ids[N_FILOSOFOS];

    for (int i = 0; i < N_FILOSOFOS; i++)
        sem_init(&tenedor[i], 0, 1);

    sem_init(&acceso, 0, N_FILOSOFOS - 1);

    printf("=== Problema de los Filosofos Comensales ===\n");
    printf("Filosofos: %d  |  Ciclos por filosofo: %d\n\n", N_FILOSOFOS, N_CICLOS);

    for (int i = 0; i < N_FILOSOFOS; i++) {
        ids[i] = i;
        pthread_create(&hilos[i], NULL, filosofo, &ids[i]);
    }

    for (int i = 0; i < N_FILOSOFOS; i++)
        pthread_join(hilos[i], NULL);

    for (int i = 0; i < N_FILOSOFOS; i++)
        sem_destroy(&tenedor[i]);
    sem_destroy(&acceso);

    printf("\n=== Todos los filosofos comieron. Fin del programa. ===\n");
    return 0;
}
