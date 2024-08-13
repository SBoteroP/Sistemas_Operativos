/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 13/08/2024
*******************************************************************
Programación en C |  Dynamic Memory Allocation

malloc() : 'malloc' asigna un bloque de memoria de un tamaño 
especificado en bytes y devuelve un puntero al inicio de ese 
bloque. La memoria asignada no está inicializada, y si no se 
puede asignar, devuelve NULL. Es necesario liberar la memoria 
con 'free' cuando ya no se necesita.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Se declaran las variables y punteros necesarios
  int *bloque00 =
      malloc(4 * sizeof(int)); // Asignación de vector de 4 tamaño int
  int *puntero = malloc(15 * sizeof(*puntero)); // Bloque de memoria de 14 int

  // Bucle para llenar los espacios Primer Bloque Reservado (bloque00)
  for (int i = 0; i < 4; i++) {
    bloque00[i] = i * 2;
    printf("El valor de memoria reservada en bloque00[%d] es: %d \n\n", i,
           bloque00[i]);
  }

  // Condicional para llenar los espacios Primer Bloque Reservado (puntero)
  if (puntero != NULL) {
    *(puntero+8) = 9889; // Se llena la posicion 9na con el valor 9889
    printf("El valor de memoria reservada en la 9na posición de puntero es es: %d \n", puntero[8]);
  }

  // Liberación o retorno de memoria
  free(bloque00);
  free(puntero);

  return 0;
}