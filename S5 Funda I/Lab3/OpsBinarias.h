
#ifndef OpsBinarias_h
#define OpsBinarias_h


/* FUNCIONES MATEMATICAS BINARIAS*/
/*
Autor: Rodrigo Kobayashi Araya

*/


/*
    Potencia:
funcion que toma dos numeros enteros y retorna el primer 
numero elevado al segundo

Esta funcion se usa para el manejo de digitos en las 
funciones de suma y resta binaria.
*/
int potencia(int a, int b)
{
    int resultado = 1;
    for (int i = 0; i < b; i++)
    {
        resultado = resultado * a;
    }
    return resultado;
}



/*      Suma Binaria:
Funcion que toma dos enteros binarios y retorna
la suma de ambos.
*/
int sumaBin(int a, int b)
{
    int resultado = 0, acarreo = 0, suma = 0, i = 0;

    while (a != 0 || b != 0)
    {

        if (a % 10 == 0 && b % 10 == 0 && acarreo == 0)
        {
            suma = 0;
            acarreo = 0;
        }
        else if (a % 10 == 1 && b % 10 == 0 && acarreo == 0)
        {
            suma = 1;
            acarreo = 0;
        }
        else if (a % 10 == 0 && b % 10 == 1 && acarreo == 0)
        {
            suma = 1;
            acarreo = 0;
        }
        else if (a % 10 == 1 && b % 10 == 1 && acarreo == 0)
        {
            suma = 0;
            acarreo = 1;
        }
        else if (a % 10 == 0 && b % 10 == 0 && acarreo == 1)
        {
            suma = 1;
            acarreo = 0;
        }
        else if (a % 10 == 1 && b % 10 == 0 && acarreo == 1)
        {
            suma = 0;
            acarreo = 1;
        }
        else if (a % 10 == 0 && b % 10 == 1 && acarreo == 1)
        {
            suma = 0;
            acarreo = 1;
        }
        else if (a % 10 == 1 && b % 10 == 1 && acarreo == 1)
        {
            suma = 1;
            acarreo = 1;
        }
        resultado += suma * potencia(10, i);
        i++;
        a = a / 10;
        b = b / 10;
    }
    if (acarreo == 1)
        resultado += potencia(10, i);
    return resultado;
}


/*      Resta Binaria
Funcion que toma dos enteros binarios y retorna 
el primer numero menos el segundo.
*/
int restaBin(int a, int b)
{

    int resultado = 0, resta = 0, i = 0;
    while (a != 0 || b != 0)
    {
        if (a % 10 == 0 && b % 10 == 0)
        {
            resta = 0;
        }
        else if (a % 10 == 1 && b % 10 == 0)
        {
            resta = 1;
        }
        else if (a % 10 == 1 && b % 10 == 1)
        {
            resta = 0;
        }
        else if (a % 10 == 0 && b % 10 == 1)
        {
            resta = 1;
            a = restaBin(a, 10);
        }
        resultado += resta * potencia(10, i);
        a = a / 10;
        b = b / 10;
        i++;
    }
    return resultado;
}


/*      Modulo Binario
Funcion que toma dos numeros enteros en binario
y retorna el resto de la division entre el primer
y el segundo numero.
*/
int moduloBin(int a, int b)
{
    int resto = a;
    while (resto >= b)
    {
        resto = restaBin(resto, b);
    }
    return resto;
}


/*      Multiplicacion Binaria
Funcion que toma dos numeros enteros en binario
y retorna la multiplicacion de estos.
*/
int multBin(int a, int b)
{
    int resultado = 0, aux = b;
    while(aux!= 0){
        resultado = sumaBin(resultado, a);
        aux = restaBin(aux, 1);
    }
    return resultado;
}

#endif