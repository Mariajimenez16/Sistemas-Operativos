#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 10

// Hilo 1: Suma Acumulada
void* hilo_acumulada(void* arg) {
    int suma = 0;
    for(int i = 1; i <= N; i++)
        suma += i;

    printf("[Hilo 1] Suma Acumulada hasta %d = %d\n", N, suma);
    sleep(30);
    pthread_exit(NULL);
}

// Hilo 2: Productoria
void* hilo_productoria(void* arg) {
    long long producto = 1;
    for(int i = 1; i <= N; i++)
        producto *= i;

    printf("[Hilo 2] Productoria hasta %d = %lld\n", N, producto);
    sleep(30);
    pthread_exit(NULL);
}

// Hilo 3: 2^N
void* hilo_potencia(void* arg) {
    long long resultado = 1;
    for(int i = 0; i < N; i++)
        resultado *= 2;

    printf("[Hilo 3] 2 a la potencia de %d = %lld\n", N, resultado);
    sleep(30);
    pthread_exit(NULL);
}

// Hilo 4: Fibonacci
void* hilo_fibonacci(void* arg) {
    int t1 = 0, t2 = 1, siguiente;

    for(int i = 1; i <= N; i++) {
        siguiente = t1 + t2;
        t1 = t2;
        t2 = siguiente;
    }

    printf("[Hilo 4] Termino %d de Fibonacci = %d\n", N, t1);
    sleep(30);
    pthread_exit(NULL);
}

int main() {

    pthread_t hilos[4];
    pid_t mi_pid = getpid();

    printf("\n====================================================\n");
    printf(" PROCESO PRINCIPAL INICIADO\n");
    printf(" EL PID DE ESTE PROCESO ES: %d\n", mi_pid);
    printf(" ABRE OTRA TERMINAL RAPIDO Y EJECUTA: pstree -p %d\n", mi_pid);
    printf("====================================================\n\n");

    // Creación de los 4 hilos
    pthread_create(&hilos[0], NULL, hilo_acumulada, NULL);
    pthread_create(&hilos[1], NULL, hilo_productoria, NULL);
    pthread_create(&hilos[2], NULL, hilo_potencia, NULL);
    pthread_create(&hilos[3], NULL, hilo_fibonacci, NULL);

    for(int i = 0; i < 4; i++)
        pthread_join(hilos[i], NULL);

    printf("\nTodos los hilos han terminado con éxito.\n");
    return 0;
}