/* **************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 30/07/2024
*****************************************************
Programación en C | Taller edad
************************************************** */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_usage() {
  printf("Uso del programa:\n");
  printf("  ./nombre-del-programa <edad> <nombre> <apellido> <telefono> <mes_nacimiento> "
         "<dia_nacimiento> <anho_nacimiento> <ciudad_residencia>\n");
  printf("\nEjemplo:\n");
  printf("  ./programa 25 Juan Perez 555-1234 Enero 15 1999 Madrid\n");
}

int main(int argc, char *argv[]) {

if (argc != 9 || (strcmp(argv[1], "help") == 0) || (strcmp(argv[1], "-h") == 0 )){
    printf("Uso equivocado de la linea de comando. \n");
    print_usage();
    return 0;
}
  
  printf("Ha ingresado la siguiente cantidad de valores: [%d] \n \n", argc);
  printf("Ha ingresado la edad: %s \n \n", argv[1]);
  printf("Ha ingresado el nombre: %s \n \n", argv[2]);
  printf("Ha ingresado el apellido: %s \n \n", argv[3]);
  printf("Ha ingresado el número de teléfono: %s \n \n", argv[4]);
  printf("Ha ingresado el mes de nacimiento: %s \n \n", argv[5]);
  printf("Ha ingresado el día de nacimiento: %s \n \n", argv[6]);
  printf("Ha ingresado el año de nacimiento: %s \n \n", argv[7]);
  printf("Ha ingresado la ciudad de residencia: %s \n \n", argv[8]);
  
  return 0;
}