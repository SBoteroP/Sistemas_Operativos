/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 24/10/2024
***************************************************************** */

#include <fcntl.h>     
#include <stdio.h>     
#include <string.h>    
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h>    

#define FIFO_FILE "MYFIFO"  // Definir el nombre del archivo FIFO (Named Pipe)

int main() {
  int fd;                // Descriptor de archivo para FIFO
  char readbuf[80];      // Buffer para almacenar la entrada del usuario
  const char *end_str = "end"; // Cadena especial para finalizar el programa

  // Crear el archivo FIFO si no existe
  mkfifo(FIFO_FILE, 0666); 

  printf("FIFO_CLIENT: Enviar mensajes, para terminar ingrese \"end\"\n");

  // Abrir el archivo FIFO para escritura
  fd = open(FIFO_FILE, O_WRONLY); 
  if (fd == -1) { 
    perror("Error al abrir FIFO");
    return 1; 
  }

  // Bucle infinito para recibir y enviar mensajes a través de FIFO
  while (1) {
    printf("Ingrese un mensaje: ");
    if (fgets(readbuf, sizeof(readbuf), stdin) == NULL) {
      // Si no se puede leer la entrada, se muestra un mensaje de error
      perror("Error al leer la entrada");
      break;
    }

    // Remover el carácter de nueva línea '\n' del mensaje ingresado
    readbuf[strcspn(readbuf, "\n")] = '\0';

    // Verificar si el usuario desea terminar el programa
    if (strcmp(readbuf, end_str) == 0) {
      // Escribir el mensaje "end" en FIFO y finalizar
      write(fd, readbuf, strlen(readbuf)); 
      printf("Mensaje enviado: \"%s\" con longitud de %lu\n", readbuf, strlen(readbuf));
      break; 
    } else {
      // Si no se ingresó "end", escribir el mensaje en el FIFO
      if (write(fd, readbuf, strlen(readbuf)) == -1) {
        // Si falla la escritura en FIFO, mostrar un mensaje de error
        perror("Error al escribir en FIFO");
      } else {
        // Mostrar el mensaje enviado y su longitud
        printf("Mensaje enviado: \"%s\" con longitud de %lu\n", readbuf, strlen(readbuf));
      }
    }
  }

  // Cerrar el descriptor de archivo FIFO después de terminar
  close(fd);
  return 0; 
}
