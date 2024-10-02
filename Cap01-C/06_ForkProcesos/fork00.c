/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 12/09/2024
*******************************************************************
Tema : Introducción a los procesos de Fork()
  Al ser invocado crea 2 procesos, padre e hijo. Cada
  uno de estos 2 procesos al ser invocados tienen diferente
  espacio de memoria (2 procesos diferentes), pero justo
  después de ser invocados ambos procesos son iguales hasta
  que el programador los cambie.
    "EL PROCESO HIJO SIEMPRE TENDRA UN ID = =" Con lo cual,
    siempre podremos identificar al proceso hijo, y a su vez 
    enviarle un "proceso" diferente.

  Se puede comunicar entre procesos con la función 'pipe()'. 
  Crea una tubería que enviara datos  de forma unidireccional
  entre el padre y el proceso hijo.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

  int id;

  printf(" \n Hola profesionales en formación \n\n");
  printf(" \n ---> PROGRAMA PRINCIPAL <--- \n\n");

  // Se crea un proceso hijo con la misma información
  id = fork();
  if (0 < id) {
    printf("\n - - - - Sección del PADRE - - - - \n");

    printf("ID: %d\n", id);

    printf("\n Soy el proceso PADRE ID = %d \n", getpid());
  } else if (id == 0) {
    printf("\n - - - - Sección del HIJO - - - - \n");

    printf("ID: %d\n", id);

    printf("\n Soy el proceso PADRE ID = %d \n", getpid());
    printf("\n Soy el proceso HIJO ID = %d \n", getpid());
  } else {
    printf("\n Error en la creación del FORK \n");
  }

  // Se imprimen numeros del 0 al 10
  for (int i = 10; i > 0; i--) {
    printf("\n=->: %d\n ", i);
  }

  printf("\n\n¡¡¡FIN DEL PROGRAMA!!!\n\n");

  return 0;
}