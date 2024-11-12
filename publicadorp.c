/* ****************************************************************
Autores: Santiago Botero
         Francisco Guzman 
         Juan Camilo Alba
         Jorge Fortich
         Brayan Fajardo
Fecha: 11/11/2024
Materia: Sistema Operativo
*******************************************************************
Descripción: Este programa se encarga de leer noticias desde un 
archivo de texto y enviarlas a un pipe FIFO para su posterior 
distribución. Cada noticia debe cumplir con un formato específico: 
debe comenzar con una letra mayúscula de un conjunto válido ('P', 
'A', 'S', 'C', 'E'), seguida de una coma, y terminar con un 
punto. El programa verifica el formato de cada línea leída del 
archivo y, si es válido, la envía al pipe. Además, se puede 
especificar un tiempo de espera entre el envío de cada noticia.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <ctype.h>

#define BUFFER 256

// Función para verificar si una línea cumple con el formato adecuado
int verificar_formato(const char* linea) {
    // Eliminar espacios al principio y al final de la línea
    while (isspace(*linea)) linea++; // Eliminar espacios al principio
    size_t len = strlen(linea);
    while (len > 0 && isspace(linea[len - 1])) {
        len--;
    }
    char buffer[len + 1];
    strncpy(buffer, linea, len);
    buffer[len] = '\0'; // Línea sin espacios

    if (strlen(buffer) < 3) return 0;  // Al menos una letra, dos puntos y algo más

    // Comprobar que la primera letra es mayúscula y es uno de los tipos válidos
    if (buffer[0] != 'P' && buffer[0] != 'A' && buffer[0] != 'S' && buffer[0] != 'C' && buffer[0] != 'E') {
        return 0;
    }

    // Verificar que la segunda posición sea un colon ':'
    if (buffer[1] != ':') {
        return 0;
    }

    // Verificar que la última posición de la noticia sea un punto '.'
    if (buffer[len - 1] != '.') {
        return 0;
    }

    return 1; // El formato es válido
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        printf("Uso: %s -p pipePSC -f file -t timeN\n", argv[0]);
        exit(1);
    }

    // Abrir el pipe
    int fdPSC = open(argv[2], O_WRONLY);
    if (fdPSC == -1) {
        printf("Error al abrir el pipe\n");
        exit(1);
    }

    // Abrir el archivo de noticias
    FILE* archivo = fopen(argv[4], "r");
    if (!archivo) {
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    int timeN = atoi(argv[6]);
    char buffer[BUFFER];

    // Leer cada línea del archivo
    while (fgets(buffer, sizeof(buffer), archivo) != NULL) {
        // Verificar el formato de la línea
        if (verificar_formato(buffer)) {
            // Si el formato es correcto, enviar la noticia al pipe
            write(fdPSC, buffer, strlen(buffer) + 1); // +1 para incluir el nulo
            sleep(timeN); // Esperar el tiempo especificado
        } else {
            // Si no es válido, imprimir mensaje de error
            printf("Línea no válida: '%s'\n", buffer);
        }
    }

    fclose(archivo);
    close(fdPSC);
    return 0;
}
