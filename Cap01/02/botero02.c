/* **************************************************
Autor: Santiago Botero Pacheco
Materia: Sistemas Operativos
Fecha: 30/07/2024
*****************************************************
Programación en C | Taller edad
************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

/* Función para imprimir el uso del programa */
void print_usage() {
    printf("Uso del programa:\n");
    printf("  ./nombre-del-programa <edad> <nombre> <apellido> <telefono> "
           "<mes_nacimiento> <dia_nacimiento> <anho_nacimiento> <ciudad_residencia>\n");
    printf("\nEjemplo:\n");
    printf("  ./programa 25 Juan Perez 555-1234 Enero 15 1999 Madrid\n");
}

/* Función para imprimir ejemplos de tipos de datos */
void print_tipo_datos() {
    int x = 42;
    unsigned int u = 42u;
    float f = 3.14f;
    double d = 3.14159265358979;
    char c = 'A';
    const char *s = "Hola"; // Cambio a const char *
    void *p = &x;
    long l = 123456789L;
    long long ll = 123456789012345LL;
    size_t sz = sizeof(int);

    // Imprimir enteros con signo
    printf("Entero con signo (%%d): %d\n", x);

    // Imprimir enteros sin signo
    printf("Entero sin signo (%%u): %u\n", u);

    // Imprimir número de punto flotante
    printf("Número de punto flotante (%%f): %f\n", f);

    // Imprimir número de punto flotante doble precisión
    printf("Número doble precisión (%%lf): %lf\n", d);

    // Imprimir carácter
    printf("Carácter (%%c): %c\n", c);

    // Imprimir cadena de caracteres
    printf("Cadena de caracteres (%%s): %s\n", s);

    // Imprimir dirección de memoria
    printf("Dirección de memoria (%%p): %p\n", (void *)p);

    // Imprimir entero largo
    printf("Entero largo (%%ld): %ld\n", l);

    // Imprimir entero largo largo
    printf("Entero largo largo (%%lld): %lld\n", ll);

    // Imprimir tamaño
    printf("Tamaño de un entero (%%zu): %zu\n", sz);
}

/* Función para mostrar la información de punteros */
void print_pointer_info() {
    int x = 102;
    int *p = &x;
    int **pp = &p;

    printf("El valor de x es: %d\n", x);
    printf("La dirección de memoria de x es: %p\n", (void*)&x);
    printf("El valor de *p ((*p --> x)) es: %d\n", *p);
    printf("La dirección de memoria de x ((p --> &x)) es: %p\n", (void*)p);
    printf("El valor de **pp ((**pp --> *p --> x)): %d\n", **pp);
    printf("La dirección de memoria de p ((pp --> &p)) es: %p\n", (void*)pp);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        int choice;
        while (1) {
            printf("\nMenú:\n");
            printf("1. Mostrar ejemplos de tipos de datos\n");
            printf("2. Mostrar información sobre punteros\n");
            printf("3. Salir\n");
            printf("Ingrese su elección: ");

            // Verificar el valor de retorno de scanf
            if (scanf("%d", &choice) != 1) {
                fprintf(stderr, "Error en la entrada. Por favor, ingrese un número.\n");
                while (getchar() != '\n'); // Limpiar el buffer de entrada
                continue;
            }

            switch (choice) {
                case 1:
                    print_tipo_datos();
                    break;
                case 2:
                    print_pointer_info();
                    break;
                case 3:
                    printf("Saliendo del programa.\n");
                    return 0;
                default:
                    printf("Opción inválida. Por favor, ingrese un número del 1 al 3.\n");
            }
        }
    } else if (argc == 9) {
        printf("Ha ingresado la siguiente cantidad de valores: [%d] \n \n", argc);
        printf("Ha ingresado la edad: %s \n \n", argv[1]);
        printf("Ha ingresado el nombre: %s \n \n", argv[2]);
        printf("Ha ingresado el apellido: %s \n \n", argv[3]);
        printf("Ha ingresado el número de teléfono: %s \n \n", argv[4]);
        printf("Ha ingresado el mes de nacimiento: %s \n \n", argv[5]);
        printf("Ha ingresado el día de nacimiento: %s \n \n", argv[6]);
        printf("Ha ingresado el año de nacimiento: %s \n \n", argv[7]);
        printf("Ha ingresado la ciudad de residencia: %s \n \n", argv[8]);
    } else if (strcmp(argv[1], "help") == 0 || strcmp(argv[1], "-h") == 0) {
        print_usage();
    } else {
        printf("Uso equivocado de la línea de comando.\n");
        print_usage();
    }

    return 0;
}
