/* ****************************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 13/08/2024
*******************************************************************
Programación en C | Dynamic Memory Allocation

realloc() : 'realloc' redimensiona un bloque de memoria previamente
asignado con 'malloc' o 'calloc'. Ajusta el tamaño del bloque a la
cantidad de bytes especificada. Si el nuevo tamaño es mayor, el
contenido nuevo se inicializa con datos indeterminados, pero los datos
existentes se preservan. Si no se puede redimensionar, devuelve NULL
y el bloque de memoria original permanece sin cambios. Es necesario
liberar la memoria con 'free' cuando ya no se necesita.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void imprimir_vector(int *vector, size_t tamaño) {
    printf("Contenido del vector:\n");
    for (size_t i = 0; i < tamaño; i++) {
        printf("posición %zu: %d\n", i, vector[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    // Asignación inicial de memoria
    int *bloque00 = malloc(4 * sizeof(int)); // Bloque inicial de 4 enteros
    int *puntero = malloc(15 * sizeof(*puntero)); // Bloque inicial de 15 enteros

    if (bloque00 == NULL || puntero == NULL) {
        fprintf(stderr, "Error al asignar memoria.\n");
        return 1;
    }

    // Inicialización del bloque00
    for (int i = 0; i < 4; i++) {
        bloque00[i] = i * 2;
    }

    // Inicialización del puntero
    for (int i = 0; i < 15; i++) {
        puntero[i] = i * 3; // Llenar con múltiplos de 3 para diferenciar
    }

    // Mostrar el contenido inicial
    printf("Contenido inicial de bloque00 (4 enteros):\n");
    imprimir_vector(bloque00, 4);

    printf("Contenido inicial de puntero (15 enteros):\n");
    imprimir_vector(puntero, 15);

    // Redimensionar el bloque de memoria usando realloc
    int *nuevo_puntero = realloc(puntero, 25 * sizeof(*puntero)); // Ampliar a 25 enteros

    if (nuevo_puntero == NULL) {
        fprintf(stderr, "Error al redimensionar la memoria.\n");
        free(puntero); // Liberar el bloque original si realloc falla
        return 1;
    }
    puntero = nuevo_puntero; // Actualizar el puntero si realloc tuvo éxito

    // Inicializar el nuevo espacio en el bloque redimensionado
    for (int i = 15; i < 25; i++) {
        puntero[i] = i * 4; // Llenar con múltiplos de 4 para diferenciar
    }

    // Mostrar el contenido después del redimensionamiento
    printf("Contenido después del redimensionamiento de puntero (25 enteros):\n");
    imprimir_vector(puntero, 25);

    // Modificar y mostrar un valor específico
    *(puntero + 8) = 9889; // Modificar el valor en la posición 9
    printf("El valor de memoria reservada en la 9na posición de puntero es: %d \n", puntero[8]);

    // Liberación de memoria
    free(bloque00);
    free(puntero);

    return 0;
}
