/* ****************************************************************
Nombres: Santiago Botero
         Francisco Guzman 
         Juan Camilo Alba
         Jorge Fortich
         Brayan Fajardo
Fecha: 11/11/2024
Materia: Sistema Operativo
*******************************************************************
*******************************************************************
Descripción: Este programa implementa un sistema de 
publicación/suscripción utilizando pipes FIFO. Permite a los 
suscriptores registrarse a un máximo de 5 temas predefinidos y 
recibir noticias enviadas por los publicadores. El sistema maneja 
múltiples suscriptores (hasta 10) y se asegura de que cada 
suscriptor pueda recibir noticias solo sobre los temas a los que 
está suscrito. Además, gestiona la creación y eliminación de 
pipes para cada suscriptor, así como la sincronización entre 
publicadores y suscriptores utilizando hilos.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/stat.h>  // Para mkfifo

#define BUFFER 256
#define MAX_SUBSCRIPTORES 10
#define MAX_TEMAS 5  // Solo hay 5 tópicos predefinidos
typedef struct {
    char* pipePSC; // Pipe de publicadores
    char* pipeSSC; // Pipe de suscriptores
    int timeF;
} sistema_config;
typedef struct {
    char temas[MAX_TEMAS];  // Lista de tópicos (solo 5 posibles, cada uno una letra)
    int contador_temas;          // Número de tópicos suscritos (independiente por suscriptor)
    char nombre_pipe[BUFFER];  // Nombre del pipe del suscriptor
    int fd;  // Descriptor del pipe
} subscriptor;

subscriptor subscriptores[MAX_SUBSCRIPTORES];
int contador_suscriptores = 0;


// Función para manejar las suscripciones
void* procesar_subscriptores(void* arg) {
    sistema_config* config = (sistema_config*)arg;
    int fdSSC = open(config->pipeSSC, O_RDONLY);

    if (fdSSC == -1) {
        printf("Error abriendo pipe de suscripciones");
        return NULL;
    }

    char subscripcion[BUFFER];
    while (1) {
        int bytesRead = read(fdSSC, subscripcion, sizeof(subscripcion));

        

        subscripcion[strcspn(subscripcion, "\n")] = '\0';  // Eliminar salto de línea
        // Si el mensaje es "exit", cerrar todas las conexiones y salir
        if (strcmp(subscripcion, "exit") == 0) {
            for (int i = 0; i < contador_suscriptores; i++) {
                write(subscriptores[i].fd, "exit", 5);
            }
            break;
        }
        printf("Suscripción recibida: %s\n", subscripcion);

        

        // Parsear el tópico y el pipe del mensaje
        char tema = subscripcion[0];  // El primer carácter es el tema
        char nombre_pipe[BUFFER];
        sscanf(subscripcion, "%c %s", &tema, nombre_pipe);

        // Buscar si el suscriptor ya está registrado
        int i;
        bool encontrado = false;
        for (i = 0; i < contador_suscriptores; i++) {
            if (strcmp(subscriptores[i].nombre_pipe, nombre_pipe) == 0) {
                encontrado = true;
                // Si el suscriptor existe, agregar el nuevo tema si no está ya suscrito
                if (subscriptores[i].contador_temas < MAX_TEMAS) {
                    bool existe = false;
                    for (int j = 0; j < subscriptores[i].contador_temas; j++) {
                        if (subscriptores[i].temas[j] == tema) {
                            existe = true;
                            break;
                        }
                    }

                    if (!existe) {
                        subscriptores[i].temas[subscriptores[i].contador_temas++] = tema;
                        printf("Nuevo tema agregado: %c para el suscriptor %s\n", tema, nombre_pipe);
                    } else {
                        printf("El suscriptor %s ya está suscrito al tema %c\n", nombre_pipe, tema);
                    }
                }
                break;
            }
        }

        // Si no se encontró, agregamos el suscriptor
        if (!encontrado && contador_suscriptores < MAX_SUBSCRIPTORES) {
            if (strlen(nombre_pipe) > 0) {
              
                strcpy(subscriptores[contador_suscriptores].nombre_pipe, nombre_pipe);
                subscriptores[contador_suscriptores].temas[0] = tema;
                subscriptores[contador_suscriptores].contador_temas = 1;
                subscriptores[contador_suscriptores].fd = open(nombre_pipe, O_WRONLY);
             
                if (subscriptores[contador_suscriptores].fd == -1) {
                    printf("Error abriendo pipe del suscriptor");
                    continue;
                }
                contador_suscriptores++;
                printf("Nuevo suscriptor registrado: %s con tema %c\n", nombre_pipe, tema);
            } else {
                printf("Error: El nombre del pipe está vacío\n");
            }
        }
    }

    close(fdSSC);
    return NULL;
}





// Función para manejar las noticias
// Función para manejar las noticias
void* prosesar_noticias(void* arg) {
    sistema_config *config = (sistema_config *)arg;
  int ppsc_fd = open(config->pipePSC, O_RDONLY);
    
    char buffer[BUFFER];
    while (1) {
      int bytesRead = read(ppsc_fd, buffer, sizeof(buffer));
      if(bytesRead == 0){
        for(int h = 0; h < config->timeF; h++){
          sleep(1);
          bytesRead = read(ppsc_fd, buffer, sizeof(buffer));
          if(bytesRead > 0){
            break;
          }
        }
        if(bytesRead == 0){
          printf("La emision a terminado \n");
          break;
        }
      }
        printf("Recibida la noticia '%s'.\n", buffer);
        buffer[strcspn(buffer, "\n")] = '\0'; // Eliminar salto de línea

        char tema = buffer[0]; // El tema es el primer carácter del mensaje
        for (int i = 0; i < contador_suscriptores; i++) {
            for (int j = 0; j < subscriptores[i].contador_temas; j++) {
                if (subscriptores[i].temas[j] == tema) {  // Compara el tema (ya es un carácter)
                    write(subscriptores[i].fd, buffer, strlen(buffer) + 1);
                    printf("Enviando noticia '%s' al suscriptor del tópico '%c'.\n", buffer, buffer[0]);
                    break;
                }
            }
        }
      
    }
    
    
  
    for (int i = 0; i < contador_suscriptores; i++) {
      write(subscriptores[i].fd, "exit", 5);
    }
    close(ppsc_fd);
    return NULL;
}



// Función para procesar argumentos
void procesar_argumentos(int argc, char *argv[], sistema_config *config) {
    if (argc < 7) {
        fprintf(stderr, "Uso: %s -p pipePSC -s pipeSSC -t timeF\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            config->pipePSC = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            config->pipeSSC = argv[++i];
        } else if (strcmp(argv[i], "-t") == 0) {
            config->timeF = atoi(argv[++i]);
        }
    }
}

int main(int argc, char* argv[]) {
    sistema_config config = {NULL, NULL, 0};
    procesar_argumentos(argc, argv, &config);

    // Crear los pipes antes de abrirlos
    if (mkfifo(config.pipePSC, 0666) == -1) {
        perror("Error creando pipe de publicadores");
        exit(1);
    }
    if (mkfifo(config.pipeSSC, 0666) == -1) {
        perror("Error creando pipe de suscriptores");
        exit(1);
    }

    printf("Configuración del sistema:\n");
    printf("Pipe de publicadores: %s\n", config.pipePSC);
    printf("Pipe de suscriptores: %s\n", config.pipeSSC);
    printf("Tiempo de espera: %d\n", config.timeF);

    pthread_t hilo_suscripciones;
    pthread_create(&hilo_suscripciones, NULL, procesar_subscriptores, &config);

    pthread_t hilo_noticias;
    pthread_create(&hilo_noticias, NULL, prosesar_noticias, &config);

    pthread_join(hilo_suscripciones, NULL);
    pthread_join(hilo_noticias, NULL);

    // Cerrar y eliminar pipes
    for (int i = 0; i < contador_suscriptores; i++) {
        close(subscriptores[i].fd);
        unlink(subscriptores[i].nombre_pipe); // Eliminar el pipe del suscriptor
    }
     
    unlink(config.pipePSC);
    unlink(config.pipeSSC);
    return 0;
}