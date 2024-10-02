/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 06/08/2024
*******************************************************************
Programación en C | Evaluación Rendimiento de Sistemas de Computo
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DATA_RESERVA (1024 * 1024 * 64 * 3)

static double MEM_CHUNK[DATA_RESERVA];

/******** Funcion para multiplicar matrices *********/
void Mult_Matriz(int SZ, double *a, double *b, double *c) {
  int i, j, k;

  for (i = 0; i < SZ; i++) {
    for (j = 0; j < SZ; j++) {
      double *pA, *pB, SumaTemp;
      SumaTemp = 0.0;
      pA = a + (i * SZ);
      pB = b + j;
      for (k = SZ; k > 0; k--, pA++, pB += SZ) {
        SumaTemp += (*pA * *pB);
        c[i * SZ + j] = SumaTemp;
      }
    }
  }
}

/************* Funcion para inicializar la Matriz *************/
void Init_Matriz(int SZ, double *a, double *b, double *c) {
  int i, j, k;
  for (k = 0; k < SZ; k++) {
    for (j = 0; j < SZ; j++) {
      a[j + k * SZ] = 2.3 * (j + k);
      b[j + k * SZ] = 3.2 * (j - k);
      c[j + k * SZ] = 1.3;
    }
  }
}

/****** Funcion para imprimir la Matriz ******/
void Print_Matriz(int SZ, double *a) {
  int j, k;
  for (k = 0; k < SZ; k++) {
    for (j = 0; j < SZ; j++) {
      printf("%f |  ", a[j + k * SZ]);
    }
    printf("\n");
  }
  printf("___________________________\n");
}

int main(int argc, char *argv[]) {
  int N = (int)atof(argv[1]); // Tamaño de la matriz
  int h = (int)atof(argv[2]); // Numero de hilos

  double *A, *B, *C;
  // Reserva de memoria para las matrices
  A = MEM_CHUNK;
  B = A + N * N;
  C = B + N * N;

  if (strcmp(argv[3], "time") == 0) {
    clock_t inicio;
    inicio = clock();

    Init_Matriz(N, A, B, C);
    Mult_Matriz(N, A, B, C);

    clock_t fin;
    fin = clock();

    double time_spent = (double)(fin - inicio) / CLOCKS_PER_SEC;
    printf("El tiempo de ejecución fué de  %f  segundos", time_spent);
  }

  else if (argc != 3) {
    printf("./MatMult MatrizSize NumHilos . . . .\n \n");
  } else {
    printf("Valores ingresados: \n");
    printf("Matriz size (NxN): %d x %d \n", N, N);
    printf("Numero de hilos (h): %d \n", h);

    Init_Matriz(N, A, B, C);

    Print_Matriz(N, A);
    Print_Matriz(N, B);
    Mult_Matriz(N, A, B, C);
    Print_Matriz(N, C);
  }

  return 0;
}