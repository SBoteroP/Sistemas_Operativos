/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 01/10/2024
*******************************************************************
Tema: Creación de Fork "Arbol de Creación"
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void creacion_fork(int linea) {
  pid_t proceso;
  proceso = fork();
  if (proceso < 0) {
    printf("Error creacion proceso\n");
    exit(1);
  } else if (proceso == 0)
    printf("%d: Proceso =HIJO=: %d\n", linea, getpid());
  else
    printf("%d: Proceso =PADRE= %d\n", linea, getpid());
}

int main(int argc, char *argv[]) {
  int p = (int)atoi(argv[1]);
  for (int i = 0; i < p; i++)
    creacion_fork(i);

  printf("\n---\n\n");
  return 0;
}