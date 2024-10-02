/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 13/08/2024
*******************************************************************
Programación en C |  Dynamic Memory Allocation

calloc() : 'calloc' asigna un bloque de memoria para un número
especificado de elementos, cada uno de un tamaño determinado en
bytes, e inicializa toda la memoria a cero. Devuelve un puntero
al inicio del bloque. Si no puede asignar la memoria, devuelve
NULL. Es necesario liberar la memoria con 'free'.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Se declaran las variables y punteros necesarios
  int *p1 = calloc(4, sizeof(int));
  int *puntero = calloc(10, sizeof(int));
  int *p3 = calloc(5, sizeof(*p3));

  // Bucle para llenar los espacios Primer Bloque Reservado (bloque00)
  printf(
      "Construccion y calculo de la secuencia de los primeros 10 terminos\n");
  for (int i = 0; i < 10; i++) {
    puntero[i] = i;
    printf("El valor de la secuencia es : [%d] \n", puntero[i]);
  }

  // Liberación o retorno de memoria
  free(p1);
  free(puntero);
  free(p3);

  return 0;
}