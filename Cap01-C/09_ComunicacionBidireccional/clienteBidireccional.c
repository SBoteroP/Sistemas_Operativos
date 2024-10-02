/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 01/10/2024
*******************************************************************
  Este programa actúa como cliente en una arquitectura FIFO (First In, 
First Out) bidireccional. El cliente envía mensajes a través de un FIFO 
al servidor y espera una respuesta del servidor con la cadena invertida. 
El cliente sigue enviando mensajes hasta que el mensaje "exit()" se 
introduce, lo que indica el final del proceso.
*******************************************************************
   CLIENTE - Servidor
***************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define FIFO_FILE "/tmp/fifo_twoway"
int main() {
  int fd;
  int end_process;
  int stringlen;
  int read_bytes;
  char readbuf[80];
  char end_str[5];
  printf("FIFO_CLIENT: ¡Envía todos los mensajes que quieras! Para salir "
         "escribe \"exit()\"\n");
  fd = open(FIFO_FILE, O_CREAT | O_RDWR);
  strcpy(end_str, "exit()");

  while (1) {
    printf("Tu mensaje: ");
    fgets(readbuf, sizeof(readbuf), stdin);
    stringlen = strlen(readbuf);
    readbuf[stringlen - 1] = '\0';
    end_process = strcmp(readbuf, end_str);

    if (end_process != 0) {
      write(fd, readbuf, strlen(readbuf));
      printf("FIFO_CLIENT: Tu mensaje enviado fue: \"%s\", y tuvo una longitud "
             "de %d caracteres.\n",
             readbuf, (int)strlen(readbuf));
      read_bytes = read(fd, readbuf, sizeof(readbuf));
      readbuf[read_bytes] = '\0';
      printf("FIFO_CLIENT: El mensaje recibido fue: \"%s\" y tuvo una longitud "
             "de %d caracteres.\n",
             readbuf, (int)strlen(readbuf));
    } else {
      write(fd, readbuf, strlen(readbuf));
      printf("FIFO_CLIENT: El mensaje enviado fue: \"%s\" y tuvo una longitud "
             "de %d caracteres.\n",
             readbuf, (int)strlen(readbuf));
      close(fd);
      break;
    }
  }
  return 0;
}
