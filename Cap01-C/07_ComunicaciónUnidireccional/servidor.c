/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 24/09/2024
*******************************************************************
   SERVIDOR - Comunicación mediante FIFO (Named Pipe)
***************************************************************** */

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define FIFO_FILE "MYFIFO" // Nombre del archivo FIFO

int main() {
     int fd;                 // Descriptor de archivo
     char readbuf[80];       // Buffer de lectura
     char end[10];           // Cadena para comparar "end"
     int to_end;             // Flag para finalizar
     int read_bytes;         // Cantidad de bytes leídos

     // Crear FIFO si no existe
     mknod(FIFO_FILE, S_IFIFO | 0640, 0);
     strcpy(end, "end");

     while(1) {
        // Abrir FIFO en modo lectura
        fd = open(FIFO_FILE, O_RDONLY);

        // Leer datos del FIFO
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0'; // Añadir terminador de cadena

        // Mostrar el mensaje recibido
        printf("Mensaje recibido: \"%s\", longitud: %d\n", readbuf, (int)strlen(readbuf));

        // Comparar si el mensaje es "end" para terminar
        to_end = strcmp(readbuf, end);
        if (to_end == 0) {
           close(fd);  // Cerrar el FIFO
           break;      // Salir del bucle
        }
     }

     return 0;
}
