/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
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

*******************************************************************
*******************************************************************
         IMPLEMENTACIÓN DE FUNCIONES DE LA BIBLIOTECA
***************************************************************** */

#ifndef LIBRARY_H 
#define LIBRARY_H 

#define CAPACIDAD_INICIAL 4

/*Creación Estructura de Datos para el Vector*/
typedef struct vectorDinamico {
  int capacidad;
  int totalElementos;
  void **elementos;
} vectorDinamico;

/*Crea un nuevo vector dinámico con la capacidad inicial definida*/
void vectorInicio(vectorDinamico *V);

/*Devuelve el número total de elementos en el vector*/
int totalVector(vectorDinamico *V);

/*Redimensiona el vector para una nueva capacidad*/
static void resizeVector(vectorDinamico *V, int capacidad);

/*Agrega un nuevo elemento al vector*/
void addVector(vectorDinamico *V, void *elemento);

/*Libera la memoria asignada al vector*/
void freeVector(vectorDinamico *V);

/*Devuelve el elemento en la posición indicada del vector*/
void *getVector(vectorDinamico *V, int indice);

/*Asigna un nuevo valor al elemento en la posición indicada del vector*/
void setVector(vectorDinamico *V, int indice, void *elemento);

/*Elimina el elemento en la posición indicada del vector*/
void borrarVector(vectorDinamico *V, int indice);

#endif