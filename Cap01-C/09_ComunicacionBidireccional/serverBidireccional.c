/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 01/10/2024
*******************************************************************
Este programa actúa como servidor en una arquitectura FIFO bidireccional. 
   El servidor lee mensajes enviados por el cliente a través de un FIFO. 
   Una vez que recibe un mensaje, lo invierte y lo envía de vuelta al cliente. 
   El proceso termina cuando el mensaje "end" se recibe desde el cliente, 
   indicando al servidor que cierre la conexión.
*******************************************************************
   SERVIDOR - Cliente
***************************************************************** */

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

#define FIFO_FILE "/tmp/fifo_twoway"
void reverse_string(char *);
int main() {
  int fd;
  char readbuf[80];
  char end[10];
  int to_end;
  int read_bytes;

  /* Crear el FIFO si no existe */
  mkfifo(FIFO_FILE, S_IFIFO | 0640);
  strcpy(end, "end");
  fd = open(FIFO_FILE, O_RDWR);
  while (1) {
    read_bytes = read(fd, readbuf, sizeof(readbuf));
    readbuf[read_bytes] = '\0';
    printf("FIFOSERVIDOR: Recibido mensaje: \"%s\" y tiene una longitud de %d caracteres.\n", readbuf, (int)strlen(readbuf));
    to_end = strcmp(readbuf, end);

    if (to_end == 0) {
      close(fd);
      break;
    }
    reverse_string(readbuf);
    printf("FIFOSERVIDOR: Enviando cadena invertida: \"%s\" y tiene una longitud de %d caracteres.\n", readbuf, (int)strlen(readbuf));
    write(fd, readbuf, strlen(readbuf));
    /*
    sleep - Esto es para asegurarse de que el otro proceso lea este mensaje, 
    de lo contrario este proceso lo recuperaría.
    */
    sleep(2);
  }
  return 0;
}

void reverse_string(char *str) {
  int last, limit, first;
  char temp;
  last = strlen(str) - 1;
  limit = last / 2;
  first = 0;

  while (first < last) {
    temp = str[first];
    str[first] = str[last];
    str[last] = temp;
    first++;
    last--;
  }
  return;
}
