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
Compilación Modular: Se divide el programa en módulos, cada uno
  con una función principal. Se puede compilar el programa en
  varios módulos, cada uno con una función principal.
***************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

#define CAPACIDAD_INICIAL 4

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