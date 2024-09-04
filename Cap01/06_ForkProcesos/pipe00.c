/* ****************************************************************
Autor   : Santiago Botero Pacheco
Materia : Sistemas Operativos
Fecha   : 12/09/2024
*******************************************************************
Tema    : Introducción a los procesos de Pipe()
          Se puede comunicar entre procesos con la función 'pipe()'.
          Crea una tubería que enviará datos de forma unidireccional
          entre el padre y el proceso hijo.
***************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t id;
    int aux;

    printf("===== PROGRAMA PRINCIPAL =====\n\n");
    printf(">> Creación de PIPES entre procesos <<\n\n");

    // Se crea el mensaje a enviar
    char sms[] = "Hola, te envío este mensaje, profesional en formación";
    // Se crea un buffer para recibir el mensaje
    char lectorMensaje[80];
    // Se crea un arreglo para identificar el INICIO y el FIN del Pipe
    int tuberia[2];

    // Se crea un pipe para comunicar los procesos
    if (pipe(tuberia) == -1) {
        perror("Error creando el pipe");
        return 1;
    }

    id = fork();
    if (id > 0) {
        // Proceso padre
        printf(">> Proceso Padre <<\n");
        // El padre cierra el extremo de escritura del pipe
        close(tuberia[1]);
        // El padre lee el mensaje desde el pipe
        aux = read(tuberia[0], lectorMensaje, sizeof(lectorMensaje));
        if (aux == -1) {
            perror("Error leyendo del pipe");
            return 1;
        }
        printf("\nEl mensaje recibido es: %s\n\n", lectorMensaje);
        // Se cierra el extremo de lectura del pipe
        close(tuberia[0]);
    } else if (id == 0) {
        // Proceso hijo
        printf(">> Proceso Hijo <<\n\n");
        // El hijo cierra el extremo de lectura del pipe
        close(tuberia[0]);

        printf("El proceso hijo está pensando el mensaje a enviar...\n");
        sleep(2); // Pausa de 2 segundos para mostrar el orden de ejecución

        // El hijo escribe el mensaje en el pipe
        if (write(tuberia[1], sms, strlen(sms) + 1) == -1) {
            perror("Error escribiendo en el pipe");
            exit(1);
        }
        // Se cierra el extremo de escritura del pipe
        close(tuberia[1]);
        exit(0);
    } else {
        perror("Error en la creación del FORK");
        return 1;
    }

    printf("\n¡¡¡FIN DEL PROGRAMA!!!\n\n");
    return 0;
}