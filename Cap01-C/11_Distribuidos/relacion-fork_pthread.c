#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 2

// Estructura para pasar argumentos a los hilos
typedef struct {
    int thread_id;
    int process_id;
} thread_data_t;

// Función que ejecutarán los hilos
void* thread_function(void* arg) {
    thread_data_t* data = (thread_data_t*)arg;
    printf("Proceso %d, Hilo %d: Ejecutando\n", data->process_id, data->thread_id);
    sleep(1); // Simula trabajo
    printf("Proceso %d, Hilo %d: Finalizando\n", data->process_id, data->thread_id);
    pthread_exit(NULL);
}

int main() {
    pid_t pid1, pid2;
    pthread_t threads[NUM_THREADS];
    thread_data_t thread_data[NUM_THREADS];

    // Crear el primer proceso hijo
    pid1 = fork();
    if (pid1 < 0) {
        perror("Fork fallido");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) { // Proceso Hijo 1
        printf("Proceso Hijo 1 creado (PID: %d)\n", getpid());
        for (int i = 0; i < NUM_THREADS; i++) {
            thread_data[i].thread_id = i + 1;
            thread_data[i].process_id = 1;
            pthread_create(&threads[i], NULL, thread_function, (void*)&thread_data[i]);
        }
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
        exit(0);
    }

    // Crear el segundo proceso hijo
    pid2 = fork();
    if (pid2 < 0) {
        perror("Fork fallido");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) { // Proceso Hijo 2
        printf("Proceso Hijo 2 creado (PID: %d)\n", getpid());
        for (int i = 0; i < NUM_THREADS; i++) {
            thread_data[i].thread_id = i + 1;
            thread_data[i].process_id = 2;
            pthread_create(&threads[i], NULL, thread_function, (void*)&thread_data[i]);
        }
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
        }
        exit(0);
    }

    // Proceso Padre
    printf("Proceso Padre (PID: %d)\n", getpid());
    wait(NULL); // Esperar a que los hijos terminen
    wait(NULL);
    printf("Todos los procesos hijos han terminado.\n");

    return 0;
}
