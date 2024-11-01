/* ****************************************************************
    Autor: Santiago Botero Pacheco
    Materia: Sistemas Operativos
    Fecha: 02/10/2024
*******************************************************************
    Este programa simula un proceso padre que crea tres hijos, donde 
    cada hijo tiene una tarea asignada relacionada con la suma de 
    arreglos numéricos leídos desde archivos. Los hijos realizan 
    las sumas parciales, las envían de vuelta al proceso padre a través 
    de pipes, y el padre se encarga de imprimir la suma total y otros 
    resultados parciales. La estructura general es un ejemplo clásico 
    de comunicación entre procesos utilizando pipes y fork() en un 
    sistema operativo basado en UNIX.
    
    Detalles del programa:
    1. Lee dos arreglos de archivos de texto proporcionados como 
       argumentos.
    2. Un proceso hijo calcula la suma total de ambos arreglos y se la 
       pasa al proceso padre.
    3. Otro hijo calcula la suma del segundo arreglo y se la pasa al 
       padre.
    4. Un tercer proceso hijo calcula la suma del primer arreglo.
    5. El proceso padre espera a que terminen los hijos y muestra 
       los resultados.
***************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void read_array(char *filename, int *arr, int size)
{
    FILE *fp = fopen(filename, "r");
    for (int i = 0; i < size; i++)
    {
        fscanf(fp, "%d", &arr[i]);
    }
    fclose(fp);
}

int sum_array(int *arr, int size)
{
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
}

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        printf("Uso: %s N1 text1 N2 text2\n", argv[0]);
        return 1;
    }

    int N1 = atoi(argv[1]);
    char *file1 = argv[2];
    int N2 = atoi(argv[3]);
    char *file2 = argv[4];

    int arr1[N1], arr2[N2];
    read_array(file1, arr1, N1);
    read_array(file2, arr2, N2);

    pid_t pid1, pid2, pid3;
    int fd1[2], fd2[2];

    if (pipe(fd1) == -1)
    {
        perror("pipe");
        return 1;
    }
    pid1 = fork();
    if (pid1 == 0)
    {
        close(fd1[0]);
        int total = sum_array(arr1, N1) + sum_array(arr2, N2);
        printf("PrimerHijo: [%d] Suma total = %d\n", getpid(), total);
        write(fd1[1], &total, sizeof(int));
        close(fd1[1]);
        exit(0);
    }
    else if (pid1 == -1)
    {
        perror("fork");
        return 1;
    }

    if (pipe(fd2) == -1)
    {
        perror("pipe");
        return 1;
    }
    pid2 = fork();
    if (pid2 == 0)
    {
        close(fd2[0]);
        int sumaB = sum_array(arr2, N2);
        printf("SegundoHijo: [%d] Sum_text2 = %d\n", getpid(), sumaB);
        write(fd2[1], &sumaB, sizeof(int));
        close(fd2[1]);
        exit(0);
    }
    else if (pid2 == -1)
    {
        perror("fork");
        return 1;
    }

    pid3 = fork();
    if (pid3 == 0)
    {
        int sumaA = sum_array(arr1, N1);
        printf("GranHijo: [%d] Sum_text1 = %d\n", getpid(), sumaA);
        exit(0);
    }
    else if (pid3 == -1)
    {
        perror("fork");
        return 1;
    }

    int status, total, sumaB;
    waitpid(pid1, &status, 0);
    read(fd1[0], &total, sizeof(int));
    close(fd1[0]);

    waitpid(pid2, &status, 0);
    read(fd2[0], &sumaB, sizeof(int));
    close(fd2[0]);

    waitpid(pid3, &status, 0);

    printf("Padre: [%d] Suma total = %d\n", getpid(), total);

    return 0;
}
