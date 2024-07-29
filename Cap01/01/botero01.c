/***************************************************
Autor: Santiago Botero Pacheco
Fecha: 23/07/2024
Materia: Sistemas Operativos
****************************************************
Programación en C |
Requerimientos:
  -Función que sume 2 números enteros.
  -Función que calcule el área de una circunferencia.
  -Funcion que de la bienvenida.
***************************************************/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Suma dos números enteros (a , b) y luego imprime el resultado

void suma(int a, int b) {
  int result = a + b;
  printf("La suma es: %d \n", result);
}

// Calcula el área de una circunferencia dado su radio e imprime el resultado.

void areaCircunferencia(double radio) {
  float result = (pow(radio, 2))*3.1416;
  printf("La circunferencia es: %lf \n", result);
}

int main(int argc, char *argv[]) {

  int num1, num2;
  double radio;
  
  printf("Hola Mundo!...\n");
  printf("\t\t ¡Bienvenidos a mi clase de SO! :) \n \n");

  printf("Ingrese dos numeros para sumar: ");
  scanf("%d %d", &num1, &num2);
  suma(num1 , num2);

  printf("Ingrese el radio para calcular el area de la circunferencia: ");
  scanf("%lf", &radio);
  areaCircunferencia(radio);
  return 0;
}

