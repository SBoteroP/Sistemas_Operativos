#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Variables globales
int counter = 0;
const int max = 4;

// Mutexes y variables de condición
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condVarProd = PTHREAD_COND_INITIALIZER;
pthread_cond_t condVarCons = PTHREAD_COND_INITIALIZER;

// Función para ejecutar el hilo (función cualquiera)
static void *funcion(void *argumentos) {
    size_t job = *(size_t *)argumentos;
    printf("\n\tJob %zu\n", job);
    return NULL;
}

// Función Productor
void *productor() {
    while (1) {
        pthread_mutex_lock(&condp_mutex);
        while (counter >= 10) 
            pthread_cond_wait(&condVarProd, &condp_mutex);
        pthread_mutex_unlock(&condp_mutex);

        pthread_mutex_lock(&counter_mutex);
        counter++;
        pthread_cond_signal(&condVarCons);
        printf("Soy el PRODUCTOR %d || Contador = %d\n", (int)pthread_self(), counter);
        pthread_mutex_unlock(&counter_mutex);

        if (counter > 7)
            sleep(4);
    }
}

// Función Consumidor
void *consumidor() {
    while (1) {
        sleep(1);

        pthread_mutex_lock(&condc_mutex);
        while (counter <= 0) {
            pthread_cond_signal(&condVarProd);
            pthread_cond_wait(&condVarCons, &condc_mutex);
        }
        pthread_mutex_unlock(&condc_mutex);

        pthread_mutex_lock(&counter_mutex);
        if (counter > 0) {
            printf("Soy el CONSUMIDOR %d || Contador = %d\n", (int)pthread_self(), counter);
            counter--;
            pthread_cond_signal(&condVarProd);
        }
        pthread_mutex_unlock(&counter_mutex);
    }
}

// Programa principal para manejo de trabajos
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <N>\n", argv[0]);
        return 1;
    }

    int N = atoi(argv[1]);
    size_t jobs[N];
    pthread_t hilos[N];

    // Creación de hilos para trabajos
    for (int i = 0; i < N; i++) {
        jobs[i] = i;
        pthread_create(&hilos[i], NULL, funcion, &jobs[i]);
    }

    // Esperar a que los hilos terminen
    for (int i = 0; i < N; i++) {
        pthread_join(hilos[i], NULL);
    }

    // Manejo de hilos Productor y Consumidor
    pthread_t prodHilo[max], consHilo[max];

    for (int i = 0; i < max; i++) {
        pthread_create(&prodHilo[i], NULL, productor, NULL);
        pthread_create(&consHilo[i], NULL, consumidor, NULL);
    }

    for (int i = 0; i < max; i++) {
        pthread_join(prodHilo[i], NULL);
        pthread_join(consHilo[i], NULL);
    }

    return 0;
}
