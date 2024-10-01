/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 24/09/2024
*******************************************************************
  CLIENTE
***************************************************************** */

#include <fcntl.h>     // Required for open
#include <stdio.h>     // Required for printf and fgets
#include <string.h>    // Required for strlen and strcmp
#include <sys/stat.h>  // Required for mkfifo
#include <sys/types.h> // Required for data types
#include <unistd.h>    // Required for close and write

#define FIFO_FILE "MYFIFO"

int main() {
  int fd;
  char readbuf[80];
  const char *end_str = "end";

  // Create FIFO if it does not exist
  mkfifo(FIFO_FILE, 0666);

  printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

  // Open FIFO for writing
  fd = open(FIFO_FILE, O_WRONLY);
  if (fd == -1) {
    perror("Failed to open FIFO");
    return 1;
  }

  while (1) {
    printf("Enter string: ");
    if (fgets(readbuf, sizeof(readbuf), stdin) == NULL) {
      perror("Failed to read input");
      break; // Exit on failure
    }

    // Remove newline character from input
    readbuf[strcspn(readbuf, "\n")] = '\0';

    // Check if the user wants to end
    if (strcmp(readbuf, end_str) == 0) {
      write(fd, readbuf,
            strlen(readbuf)); // Ignore return value if you're okay with it
      printf("Sent string: \"%s\" and string length is %lu\n", readbuf,
             strlen(readbuf));
      break; // Exit the loop
    } else {
      if (write(fd, readbuf, strlen(readbuf)) == -1) {
        perror("Failed to write to FIFO");
      } else {
        printf("Sent string: \"%s\" and string length is %lu\n", readbuf,
               strlen(readbuf));
      }
    }
  }

  close(fd); // Close the FIFO
  return 0;
}
