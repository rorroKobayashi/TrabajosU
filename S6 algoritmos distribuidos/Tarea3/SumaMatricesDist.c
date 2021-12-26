#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mpi.h"

#define MASTER 0
#define METADATA 1
#define TRANSFER 2
#define RESULT 3

int whoami, hm_are_we;
MPI_Status status;
/*
 * 
 * Shows the usage of the program
 * 
 */
void Usage(char *message)
{

    printf("\nUsage : mpirun -np 3 %s a b c\n", message);
    fflush(stdout);
}

void printMatrix(float **m, int rows, int cols)
{
    int i = 0, j = 0;
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            printf("%f\t", m[i][j]);
            j++;
        }
        printf("\n");
        i++;
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int me, i = 0, j = 0, k = 0, datos[3], rows = 0, cols = 0, rowsPorProceso, restoProceso, rowPos;
    float *arr, **sumando1, **sumando2, **resultado;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &hm_are_we);
    MPI_Comm_rank(MPI_COMM_WORLD, &whoami);
    MPI_Get_processor_name(processor_name, &me);
    printf("\n\nProcess [%d] Alive on %s\n", whoami, processor_name);
    fflush(stdout);
    if (whoami == MASTER)
    {
        printf("ingrese el numero de filas que tendran las matrices por sumar:  ");
        scanf("%d", &rows);
        printf("\ningrese el numero de columnas que tendran las matrices por sumar: ");
        scanf("%d", &cols);
        float **M1 = calloc(cols, sizeof(float *));
        float **M2 = calloc(cols, sizeof(float *));
        for (i = 0; i < cols; i++)
        {
            M1[i] = calloc(rows, sizeof(float));
            M2[i] = calloc(rows, sizeof(float));
        }
        i = 0;
        while (i < rows)
        {
            j = 0;
            while (j < cols)
            {
                printf("\n Ingrese el valor de la posicion [%d][%d] de la primera matriz:   ", i, j);
                scanf("%f", &M1[i][j]);
                j++;
            }
            i++;
        }
        i = 0;
        j = 0;
        while (i < rows)
        {
            j = 0;
            while (j < cols)
            {
                printf("\n Ingrese el valor de la posicion [%d][%d] de la segunda matriz:   ", i, j);
                scanf("%f", &M2[i][j]);
                j++;
            }
            i++;
        }
        rowsPorProceso = rows / (hm_are_we - 1);
        restoProceso = rows % (hm_are_we - 1);
        /*  SE ENVIA LA INFORMACION A LOS PROCESOS */
        rowPos = 0;
        for (i = 1; i < hm_are_we; i++)
        {
            datos[0] = cols;           //tamannio de la columna por enviar
            datos[1] = rowsPorProceso; //cantidad de columnas por enviar
            datos[2] = rowPos;         //posición de la primera columna por enviar
            if (restoProceso == 0)
            {
                MPI_Send(&datos, 3, MPI_INT, i, METADATA, MPI_COMM_WORLD); //se envia la metadata
                for (j = 0; j < datos[1]; j++)
                { //se envia las columnas por sumar
                    MPI_Send(M1[rowPos], cols, MPI_FLOAT, i, TRANSFER, MPI_COMM_WORLD);
                    MPI_Send(M2[rowPos], cols, MPI_FLOAT, i, TRANSFER, MPI_COMM_WORLD);
                    rowPos++;
                }
            }
            else //si quedan columnas restantes de las columnas por proceso se agregan en esta seccion
            {
                datos[1] += 1;
                MPI_Send(&datos, 3, MPI_INT, i, METADATA, MPI_COMM_WORLD); //se envia la metadata
                for (j = 0; j < datos[1]; j++)
                { //se envian las columnas por sumar
                    MPI_Send(M1[rowPos], cols, MPI_FLOAT, i, TRANSFER, MPI_COMM_WORLD);
                    MPI_Send(M2[rowPos], cols, MPI_FLOAT, i, TRANSFER, MPI_COMM_WORLD);
                    rowPos++;
                }
                restoProceso--;
            }
            /*  RECEPCION DE DATOS  */
            resultado = calloc(rows, sizeof(float*));
            for(i = 0; i< rows; i++){
                resultado[i] = calloc(cols, sizeof(float));
            }
            arr = calloc(cols, sizeof(float));
            for (i = 1; i < hm_are_we; i++)
            {
                MPI_Recv(&datos, 3, MPI_INT, i, METADATA, MPI_COMM_WORLD, &status);
                rowPos = datos[2];
                for (j = 0; j < datos[1]; j++)
                {
                    MPI_Recv(arr, datos[0], MPI_FLOAT, i, RESULT, MPI_COMM_WORLD, &status);
                    for (k = 0; k < datos[0]; k++)
                    {
                        resultado[rowPos][k] = arr[k];
                    }
                    rowPos++;
                }
            }
            printMatrix(resultado, rows, cols);
        }
    }
    /*DEFINICION DEL FUNCIONAMIENTO DE PROCESOS SECUNDARIOS*/
    else
    {
        MPI_Recv(&datos, 3, MPI_INT, MASTER, METADATA, MPI_COMM_WORLD, &status);
        cols = datos[0];
        rowsPorProceso = datos[1];
        rowPos = datos[2];
        //se pide memoria para la suma
        sumando1 = calloc(rowsPorProceso, sizeof(float *));
        sumando2 = calloc(rowsPorProceso, sizeof(float *));
        for (i = 0; i < rowsPorProceso; i++)
        {
            sumando1[i] = calloc(cols, sizeof(float));
            sumando2[i] = calloc(cols, sizeof(float));
        }
        //recepcion de datos
        for (i = 0; i < rowsPorProceso; i++)
        {
            MPI_Recv(sumando1[i], cols, MPI_FLOAT, MASTER, TRANSFER, MPI_COMM_WORLD, &status);
            MPI_Recv(sumando2[i], cols, MPI_FLOAT, MASTER, TRANSFER, MPI_COMM_WORLD, &status);
        }
        //suma de datos
        for (i = 0; i < rowsPorProceso; i++)
        {
            for (j = 0; j < cols; j++)
            {
                sumando1[i][j] += sumando2[i][j];
            }
        }
        //se envia la suma de vuelta a MASTER
        for (i = 0; i < rowsPorProceso; i++)
        {
            MPI_Send(&datos, 3, MPI_INT, MASTER, METADATA, MPI_COMM_WORLD);
            MPI_Send(sumando1[i], cols, MPI_FLOAT, MASTER, RESULT, MPI_COMM_WORLD);
        }
    }
    MPI_Finalize();
}