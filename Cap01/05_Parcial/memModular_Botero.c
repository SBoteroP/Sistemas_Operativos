/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 20/08/2024
*******************************************************************
Gestión de Memoria, Punteros, Compilación Modular |
  Gestión de memoria (dinámica. estática), manipulación de
  espacio de memoria según necesite la aplicación, por parte
  del usuario. Se presenta la memoria estática que solo
  se dispone en tiempo de compilación. Variables globales,
  vectores fijos, etc. No es necesario liberar la memoria dinámica
  que el ususario en función del problema puede cambiar, modificar,
  el espacio de memoria que necesite. El tema a señalar, es que
  se debe liberar la memoria al final.

***************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define CAPACIDAD_INICIAL 4

/*Creación Estructura de Datos para el Vector*/
typedef struct vectorDinamico {
  int capacidad;
  int totalElementos;
  void **elementos;
} vectorDinamico;

/*Crea un nuevo vector dinámico con la capacidad inicial definida*/
void vectorInicio(vectorDinamico *V) {
  // Inicializa la capacidad del vector a la capacidad inicial definida.
  V->capacidad = CAPACIDAD_INICIAL;
  // Inicializa el número total de elementos del vector a 0.
  V->totalElementos = 0;
  // Asigna memoria para el arreglo de elementos del vector.
  V->elementos = malloc(sizeof(void *) * V->capacidad);
}

/*Devuelve el número total de elementos en el vector*/
int totalVector(vectorDinamico *V) { return V->totalElementos; }

/*Redimensiona el vector para una nueva capacidad*/
static void resizeVector(vectorDinamico *V, int capacidad) {
  printf("Redimensión: %d a %d \n", V->capacidad, capacidad);

  void **elementos = realloc(V->elementos, sizeof(void *) * capacidad);
  if (elementos) {
    V->elementos = elementos;
    V->capacidad = capacidad;
  }
}

/*Agrega un nuevo elemento al vector*/
void addVector(vectorDinamico *V, void *elemento) {
  if (V->capacidad == V->totalElementos)
    resizeVector(V, V->capacidad * 2);
  V->elementos[V->totalElementos++] = elemento;
}

/*Libera la memoria asignada al vector*/
void freeVector(vectorDinamico *V) { free(V->elementos); }

/*Devuelve el elemento en la posición indicada del vector*/
void *getVector(vectorDinamico *V, int indice) {
  if (indice >= 0 && indice < V->totalElementos)
    return V->elementos[indice];
  return NULL;
}

/*Asigna un nuevo valor al elemento en la posición indicada del vector*/
void setVector(vectorDinamico *V, int indice, void *elemento) {
  if (indice >= 0 && indice < V->totalElementos)
    V->elementos[indice] = elemento;
}

/*Elimina el elemento en la posición indicada del vector*/
void borrarVector(vectorDinamico *V, int indice) {
  if (indice < 0 || indice >= V->totalElementos)
    return;

  V->elementos[indice] = NULL;

  for (int i = indice; i < V->totalElementos - 1; i++) {
    V->elementos[i] = V->elementos[i + 1];
    V->elementos[i + 1] = NULL;
  }
  V->totalElementos--;
  if (V->totalElementos > 0 && V->totalElementos == V->capacidad / 4)
    resizeVector(V, V->capacidad / 2);
}

int main() {
  printf("\n");
  int i = 0;
  vectorDinamico editor;
  vectorInicio(&editor);

  addVector(&editor, "Hola ");
  addVector(&editor, "Profesional ");
  addVector(&editor, "en ");
  addVector(&editor, "Formacion ");
  addVector(&editor, "de ");
  addVector(&editor, "Ingenieria ");

  printf("\n");
  for (i = 0; i < totalVector(&editor); i++)
    printf("%s", (char *)getVector(&editor, i));

  printf("\n\n");

  while (i > 1) {
    borrarVector(&editor, i);
    i--;
  }

  setVector(&editor, 1, "¡Buenos");
  addVector(&editor, "Días!");

  printf("\n");

  for (int i = 0; i < totalVector(&editor); i++)
    printf("%s ", (char *)getVector(&editor, i));
}