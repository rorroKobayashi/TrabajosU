#include<stdio.h>

/*--------------METODO DE INTERPOLACION DE LAGRANGE-------------*/

/* Metodo para obtener un punto perteneciente a la curva de un  */
/*    polinomio que pasa por todos los puntos ingresados.       */


/*  Para un conjunto de n+1 puntos (xi, yi), el polinomio de 
    interpolacion de lagrange es un polinomio de grado menor
    o igual a n tal que pasa por todos los puntos (xi, yi). 
    
    Este polinomio esta dado por: 
        
        y = SUM( Li(x)yi , i = 0, n) , Donde
        
        Li = PROD((x-xj)/(xi-xj) , j=0, j!= i, n)               */

/*------------------------IMPLEMENTACION------------------------*/


/*Partimos definiendo Li, ya que necesitamos esta funcion para 
    ingresarla a la sumatoria que crea al polinomio:            */

float Li(int n, int i, float xi[n+1], float x)
{
    int j = 0;                  /*Se define j, para iterar sobre los valores de xi*/
    float product = 1;      /*Se define el producto que sera retornado como Li*/
    while (j<=n)
    {
        if(j != i)          /*para todo j != i*/
        {
            product = product*(x - xi[j])/(xi[i] - xi[j]);
            /*   Li = PROD((x-xj)/(xi-xj) , j=0, j!= i, n)   */
        }
        j = j+1;
    }
    return product;
}

/*Con Li definido, seguimos definiendo la funcion que evalua a la entrada x
    en el polinomio.                                                        */

float Pn(int n, float xi[n+1], float yi[n+1], float x)
{
    int i;              /*se define i, para iterar sobre los puntos*/
    float result = 0;       /*Se define result, que representa la evaluacion Pn(x)*/
    while (i <= n)
    {
        result = result + Li(n, i, xi, x)*yi[i];
        /*   y = SUM( Li(x)yi , i = 0, n)   */
        i = i+1;
    }
    return result;
}

int main(){
    int n = 9;
    float xi[] = {0, 1, 2, 4, 5, 6, 7, 8, 9, 10};
    float yi[] = {1, 2, 4, 16, 32, 64, 128, 256, 512, 1024};
    float x = 3;
    float y = Pn(n, xi, yi, x);
    printf("%f\n", y);
}