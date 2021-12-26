#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*Funcion de expancion E*/
int Expansion[] ={32, 1 , 2 , 3 , 4 , 5 ,
                  4 , 5 , 6 , 7 , 8 , 9 ,
                  8 , 9 , 10, 11, 12, 13,
                  12, 13, 14, 15, 16, 17,
                  16, 17, 18, 19, 20, 21,
                  20, 21, 22, 23, 24, 25,
                  24, 25, 26, 27, 28, 29,
                  28, 29, 30, 31, 32, 1 };

/*S-Boxes:*/                    /* S_1 */
int S[8][4][16] ={{{14, 4 , 13, 1, 2 , 15, 11, 8 , 3 , 10, 6 , 12, 5 , 9 , 0, 7 },
                   {0 , 15, 7 , 4, 14, 2 , 13, 1 , 10, 6 , 12, 11, 9 , 5 , 3, 8 },
                   {4 , 1 , 14, 8, 13, 6 , 2 , 11, 15, 12, 9 , 7 , 3 , 10, 5, 0 },
                   {15, 12, 8 , 2, 4 , 9 , 1 , 7 , 5 , 11, 3 , 14, 10, 0 , 6, 13} },
                                /* S_2 */
                  {{15, 1 , 8 , 14, 6 , 11, 3 , 4 , 9 , 7, 2 , 13, 12, 0, 5 , 10},
                   {3 , 13, 4 , 7 , 15, 2 , 8 , 14, 12, 0, 1 , 10, 6 , 9, 11, 5 },
                   {0 , 14, 7 , 11, 10, 4 , 13, 1 , 5 , 8, 12, 6 , 9 , 3, 2 , 15},
                   {13, 8 , 10, 1 , 3 , 15, 4 , 2 , 11, 6, 7 , 12, 0 , 5, 14, 9 }},
                                /* S_3 */
                  {{10, 0 , 9 , 14, 6, 3 , 15, 5 , 1 , 13, 12, 7 , 11, 4 , 2 , 8 },
                   {13, 7 , 0 , 9 , 3, 4 , 6 , 10, 2 , 8 , 5 , 14, 12, 11, 15, 1 },
                   {13, 6 , 4 , 9 , 8, 15, 3 , 0 , 11, 1 , 2 , 12, 5 , 10, 14, 7 },
                   {1 , 10, 13, 0 , 6, 9 , 8 , 7 , 4 , 15, 14, 3 , 11, 5 , 2 , 12}},
                                /* S_4 */
                  {{7 , 13, 14, 3, 0 , 6 , 9 , 10, 1 , 2, 8, 5 , 11, 12, 4 , 15},
                   {13, 8 , 11, 5, 6 , 15, 0 , 3 , 4 , 7, 2, 12, 1 , 10, 14, 9 },
                   {10, 6 , 9 , 0, 12, 11, 7 , 13, 15, 1, 3, 14, 5 , 2 , 8 , 4 },
                   {3 , 15, 0 , 6, 10, 1 , 13, 8 , 9 , 4, 5, 11, 12, 7 , 2 , 14}},
                                /* S_5 */
                  {{2 , 12, 4 , 1 , 7 , 10, 11, 6 , 8 , 5 , 3 , 15, 13, 0, 14, 9 },
                   {14, 11, 2 , 12, 4 , 7 , 13, 1 , 5 , 0 , 15, 10, 3 , 9, 8 , 6 },
                   {4 , 2 , 1 , 11, 10, 13, 7 , 8 , 15, 9 , 12, 5 , 6 , 3, 0 , 14},
                   {11, 8 , 12, 7 , 1 , 14, 2 , 13, 6 , 15, 0 , 9 , 10, 4, 5 , 3 }},
                                /* S_6 */
                  {{12, 1 , 10, 15, 9, 2 , 6 , 8 , 0 , 13, 3 , 4 , 14, 7 , 5 , 11},
                   {10, 15, 4 , 2 , 7, 12, 9 , 5 , 6 , 1 , 13, 14, 0 , 11, 3 , 8 },
                   {9 , 14, 15, 5 , 2, 8 , 12, 3 , 7 , 0 , 4 , 10, 1 , 13, 11, 6 },
                   {4 , 3 , 2 , 12, 9, 5 , 15, 10, 11, 14, 1 , 7 , 6 , 0 , 8 , 13}},
                                /* S_7 */
                  {{4 , 11, 2 , 14, 15, 0, 8 , 13, 3 , 12, 9, 7 , 5 , 10, 6, 1 },
                   {13, 0 , 11, 7 , 4 , 9, 1 , 10, 14, 3 , 5, 12, 2 , 15, 8, 6 },
                   {1 , 4 , 11, 13, 12, 3, 7 , 14, 10, 15, 6, 8 , 0 , 5 , 9, 2 },
                   {6 , 11, 13, 8 , 1 , 4, 10, 7 , 9 , 5 , 0, 15, 14, 2 , 3, 12}},
                                /* S_8 */
                  {{13, 2 , 8 , 4, 6 , 15, 11, 1 , 10, 9 , 3 , 14, 5 , 0 , 12, 7 },
                   {1 , 15, 13, 8, 10, 3 , 7 , 4 , 12, 5 , 6 , 11, 0 , 14, 9 , 2 },
                   {7 , 11, 4 , 1, 9 , 12, 14, 2 , 0 , 6 , 10, 13, 15, 3 , 5 , 8 },
                   {2 , 1 , 14, 7, 4 , 10, 8 , 13, 15, 12, 9 , 0 , 3 , 5 , 6 , 11}}};

/*Permutación P*/

int Permutation[] = {16, 7 , 20, 21, 29, 12, 28, 17,
                     1 , 15, 23, 26, 5 , 18, 31, 10,
                     2 , 8 , 24, 14, 32, 27, 3 , 9 ,
                     19, 13, 30, 6 , 22, 11, 4 , 25 };


/*Funcion f: 
la funcion f juega un papel fundamental para el algoritmo de 
encriptamiento DES, esta funcion consta de las siguientes partes:
recibe un array R_im1 de enteros (0 y 1) de largo 32 y una clave k_i de
48 bits para entregar un array de 32 bits listo para ser comparado
mediante un XOR con la otra mitad de la particion de 64 bits del mensaje
a encriptar.

El array es expandido mediante la función de expansion E, denotada
como un array unidimensional.

luego es comparado mediante un XOR con la clave k_i y particionado en
un vector compuesto de 8 particiones de 6 bits

cada particion es ingresada a su S-Box correspondiente, denotada
como un arreglo de arreglos bidimencionales, las particiones son 
transformadas mediante la representacion binaria de las posiciones 
de S_i, con los extremos de la particion de 6 bits representando las 
filas y el resto de los bits representando las columnas. luego de esto
el número que corresponde de la S-Box es escrito en representacion 
binaria de 4 bits. 
A concatenar estas particiones, se genera un array de 32 bits de largo
a la que se le aplica una permutacion final antes de retornarlo.

*/

int *f(int *R_im1, int *K_i){
    int R_im1Expandido[48], S_x, S_y, S_number, j=0;
    int temp[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int *C = (int*)calloc(32, sizeof(int));
/* Se expande R_im1 mediante la funcion de expansion */    
    for(int i = 0; i<48; i++){
        R_im1Expandido[i] = R_im1[Expansion[i]];
    }
/* Comparacion mediante XOR con K_i */    
    for (int i = 0; i<48; i++){
        R_im1Expandido[i] = R_im1Expandido[i] ^ K_i[i];
    }
/* ingreso a las S_Boxes */
    for (int i = 0; i<48; i = i+6){
        S_x = R_im1Expandido[i]*2 + R_im1Expandido[i+5];
        S_y = R_im1Expandido[i+1]*8 + R_im1Expandido[i+1]*4
            + R_im1Expandido[i+1]*2 +R_im1Expandido[i+1];
        S_number = S[i/6][S_x][S_y];
        if(S_number >= 8){
            temp[j] = 1;
            S_number -= 8;
        }
        j++;
        if(S_number >= 4){
            temp[j] = 1;
            S_number -=4;
        }
        j++;
        if(S_number >= 2){
            temp[j] = 1;
            S_number -= 2;
        }
        j++;
        if(S_number >= 1){
            temp[j] = 1;
        }
        j++;
    }
/* Permutacion Final */
    for (int i = 0; i<32 ; i++){
        C[i] = temp[Permutation[i]];
    }
    return C;
}


void printArray(int *arr){
    for (int i = 0; i<32; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}
int main(){
    clock_t start_t, end_t, total_t;
    int key[48] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int arr[32] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int *arrCodificado;
    double timeSum;
    double avg;
    for(int j = 0; j<100; j++){
        for (int i = 0; i<900000; i++){
            start_t = clock();
            arrCodificado = f(arr, key);
            end_t = clock(); 
            timeSum += (double)(end_t - start_t)/ CLOCKS_PER_SEC;
            free(arrCodificado);
        }
    }
    avg = timeSum/100;
    printf("%f\n", avg*1000);
}