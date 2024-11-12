/* ****************************************************************
Autores: Santiago Botero
         Francisco Guzman 
         Juan Camilo Alba
         Jorge Fortich
         Brayan Fajardo
*******************************************************************
Materia: Sistemas Operativos - Proyecto
Fecha: 11/11/2024
*******************************************************************
Descripción: Este programa implementa un suscriptor que se 
conecta a un sistema de publicación/suscripción utilizando pipes 
FIFO. El suscriptor puede elegir un tema para el cual desea 
recibir noticias y establece un canal de comunicación a través 
de un FIFO privado. Permite suscribirse a varios temas y 
recibir notificaciones hasta que el usuario decida salir.
Además, gestiona la creación y eliminación de un FIFO específico 
para cada instancia del suscriptor.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>

#define BUFFER 256

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf( "Uso: %s -s pipeSSC\n", argv[0]);
        exit(1);
    }

    char *pipeSSC = argv[2];
    char nombre_fifo[100];
    int fd;
    snprintf(nombre_fifo, sizeof(nombre_fifo), "/tmp/fifo_suscriptor_%d", getpid());
    
    if (mkfifo(nombre_fifo, 0666) == -1) {
    printf("Error al crear el FIFO");
    exit(1);
    }
    // Enviar suscripciones al sistema
    int fdSSC = open(pipeSSC, O_WRONLY);
    if (fdSSC == -1) {
        printf("Error al abrir pipeSSC");
        exit(1);
    }

    while (1) {
        char tema[6];
      int a=0;
        printf("Suscríbete a un tema (A, E, C, P, S) o 'exit' para terminar: ");
        fgets(tema, sizeof(tema), stdin);
        tema[strcspn(tema, "\n")] = '\0';

        if (strcmp(tema, "exit") == 0) {
          printf("Saliendo.... \n ");
            break;  // Terminar la suscripción
        } 

        char subscripcion[200];
        snprintf(subscripcion, sizeof(subscripcion), "%s %s", tema, nombre_fifo);
        write(fdSSC, subscripcion, strlen(subscripcion) + 1);
        printf("Suscripción enviada: %s\n", subscripcion);
        
        if(a==0){
          fd = open(nombre_fifo, O_RDONLY);
          a=1;
        }
    }



    // Leer noticias en el pipe privado del suscriptor
    
    char noticias[BUFFER];

    while (1) {
        int bytesRead = read(fd, noticias, sizeof(noticias));
        if (bytesRead > 0) {
            noticias[bytesRead] = '\0';
            if (strcmp(noticias, "exit") == 0) {
                printf("Notificación de salida recibida.\n");
                write(fdSSC, "exit", 5);
                break;
            }
            printf("Noticia recibida: %s\n", noticias);
        }
    }
    close(fdSSC);
    close(fd);
    unlink(nombre_fifo);
    return 0;
}



