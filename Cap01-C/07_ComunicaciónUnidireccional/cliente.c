/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 24/09/2024
*******************************************************************
  CLIENTE - Comunicación mediante FIFO (Named Pipe)
***************************************************************** */

#include <fcntl.h>     // Biblioteca para control de archivos
#include <stdio.h>     // Biblioteca estándar de entrada/salida
#include <string.h>    // Biblioteca para manejo de cadenas de texto
#include <sys/stat.h>  // Biblioteca para trabajar con propiedades de archivos
#include <sys/types.h> // Biblioteca para tipos de datos específicos del sistema
#include <unistd.h>    // Biblioteca para la llamada al sistema POSIX

#define FIFO_FILE "MYFIFO"  // Definir el nombre del archivo FIFO (Named Pipe)

int main() {
  int fd;                // Descriptor de archivo para FIFO
  char readbuf[80];      // Buffer para almacenar la entrada del usuario
  const char *end_str = "end"; // Cadena especial para finalizar el programa

  // Crear el archivo FIFO si no existe
  mkfifo(FIFO_FILE, 0666); // 0666 define permisos de lectura/escritura para todos

  printf("FIFO_CLIENT: Enviar mensajes, para terminar ingrese \"end\"\n");

  // Abrir el archivo FIFO para escritura
  fd = open(FIFO_FILE, O_WRONLY); // Abrir en modo escritura
  if (fd == -1) { // Comprobar si la apertura falló
    perror("Error al abrir FIFO");
    return 1; // Terminar el programa si no se puede abrir FIFO
  }

  // Bucle infinito para recibir y enviar mensajes a través de FIFO
  while (1) {
    printf("Ingrese un mensaje: ");
    if (fgets(readbuf, sizeof(readbuf), stdin) == NULL) {
      // Si no se puede leer la entrada, se muestra un mensaje de error
      perror("Error al leer la entrada");
      break; // Salir del bucle en caso de fallo
    }

    // Remover el carácter de nueva línea '\n' del mensaje ingresado
    readbuf[strcspn(readbuf, "\n")] = '\0';

    // Verificar si el usuario desea terminar el programa
    if (strcmp(readbuf, end_str) == 0) {
      // Escribir el mensaje "end" en FIFO y finalizar
      write(fd, readbuf, strlen(readbuf)); // Enviar el mensaje al FIFO
      printf("Mensaje enviado: \"%s\" con longitud de %lu\n", readbuf, strlen(readbuf));
      break; // Salir del bucle para terminar el programa
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
  return 0; // Terminar el programa con éxito
}
