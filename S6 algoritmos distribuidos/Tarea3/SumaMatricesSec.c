#include <stdio.h>
#include <stdlib.h>

int rows, cols;

void printMatrix(float m[rows][cols])
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

void SumaMatrices(float mat1[rows][cols], float mat2[rows][cols])
{
    int i = 0, j = 0;
    float total[rows][cols];
    while (i < rows)
    {
        j = 0;
        while (j < cols)
        {
            total[i][j] = mat1[i][j] + mat2[i][j];
            j++;
        }
        i++;
    }
    printMatrix(total);
}

int main()
{
    int i = 0, j = 0;
    printf("ingrese el numero de filas que tendran las matrices por sumar:  ");
    scanf("%d", &rows);
    printf("\ningrese el numero de columnas que tendran las matrices por sumar: ");
    scanf("%d", &cols);
    float M1[rows][cols], M2[rows][cols];
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
    SumaMatrices(M1, M2);
}
