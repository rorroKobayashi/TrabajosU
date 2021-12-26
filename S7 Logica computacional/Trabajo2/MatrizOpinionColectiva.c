#include <stdio.h>
#include <stdlib.h>
/*--------------------MATRIZ DE OPINION COLECTIVA--------------------*/

/*
    Dado un numero natural n, es posible particionar un conjunto de n 
    numeros naturales {d1, d2, d3, ... , dn} en p particiones (2<=p <=n-1)
    y luego construir una matriz de opinion colectiva Y. El conjunto 
    {d1, d2, ... , dn} es una permutacion del conjunto {1, 2, 3, ..., n}.

    La matriz Y es una matriz de orden nxn que se construye del siguiente
    modo:

        Y[i][i] = 1, 1 <= i <= n
        Y[i][j] = 1, si i y j estan en la misma particion. En caso contrario
        Y[i][j] = 0

    Por ejuemplo, sea n= 5, p = 3, la particion 1,1,3 y la permutacion
    {4, 5, 1, 2, 3}. La particion y la permutacion generan:
    {4}, {5}. {1, 2, 3}
    La matriz de opinion colectiva es:

        |1 1 1 0 0|
        |1 1 1 0 0|
    Y = |1 1 1 0 0|
        |0 0 0 1 0|
        |0 0 0 0 1|
*/

/*----------------------------------IMPLEMENTACION----------------------------------*/

/*
    Primero definimos una funcion auxiliar para encontrar la posicion de cierto numero
    en un arreglo.
*/
int searchPos(int num, int n, int arr[n])
{
    int i = 0;
    while (i < n)
    {
        if (arr[i] == num)
        {
            return i;
        }
        i = i+1;
    }
}

/*
   Para obtener la matriz, necesitamos el conjunto de numeros naturales {d1,..., dn}, 
   la cardinalidad del conjunto (n), el numero de particiones (p) y la cardinalidad de 
   cada particion {P1, P2, ..., Pp}
*/

int *colOpMatrix(int n, int p, int D[n], int partitions[p], int **matrix)
{   /*Definicion de variables*/
    int pos1 = 0, pos2 = partitions[0], i=1, j=1, k=0, posi, posj;
    while (i <= n)
    {
        while (j <= n)
        {
            if (i == j)
            {
                matrix[i - 1][j - 1] = 1; /*si i=j, M_ij = 1*/
            }
            else
            {
                posi = searchPos(i, n, D); /*posiciones de las particiones*/
                posj = searchPos(j, n, D);
                while (k < p)
                {/*caso: la posicion de i esta por sobre el techo de la particion*/
                    if (pos2 < posi) 
                    {
                        pos1 = pos2;
                        pos2 = pos2 + partitions[k + 2];
                    }
                    else
                    {/*caso: la posicion de i esta dentro de la particion*/
                        if (pos1 < posi && posi <= pos2)
                        {/*caso: la posicion de j esta dentro de la particion*/
                            if (pos1 < posj && posj <= pos2)
                            {/*M_ij = 1*/
                                matrix[i - 1][j - 1] = 1;
                            }/*caso: posiciones no estan dentro de la misma particion*/
                            else
                            {/*M_ij = 0*/
                                matrix[i - 1][j - 1] = 0;
                            }
                        }
                    }
                    k = k + 1;
                }
                k = 0;
            }
            j = j + 1;
        }
        j = 1;
        i = i + 1;
    }
}

int main()
{
    int D[] = {4, 5, 1, 2, 3};
    int n = 5, p = 3;
    int partitions[] = {1, 1, 3};
    int *matrix[n];
    for (int x = 0; x < n; x++)
    {
        matrix[x] = calloc(n, sizeof(int));
    }
    colOpMatrix(n, p, D, partitions, matrix);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
    for (int x = 0; x < n; x++)
    {
        free(matrix[x]);
    }
}