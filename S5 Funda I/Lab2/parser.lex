/**

Laboratorio 2: PARSEADOR DE LEX

Autor: Rodrigo Kobayashi
Profesor: Rodrigo Abarzúa
Fecha de entrega: Miércoles 12 de Agosto

Descripción: 
    Programa desarrollado en Lex/Flex tal que:
    -Elimina espacios y tabuladores redundantes (reemplaza mas de dos espacios o tabuladores por solo uno).
    -Cuenta las ocurrencias de una palabra dada en un fichero de texto.
    -Borra comentarios en un fichero de texto dado (los comentarios son de una sola linea y empiezan con un "#").
    -Imprime el texto tal y como está en el archivo de entrada, pero cada vez que detecta un ";" imprime el texto 
     en una nueva linea.
    -Cada vez que aparece una "ñ", la sustituye por una "n"
    -Indique la cantidad de veces que aparecen número enteros en un fichero de texto.
    -Imprima el texto de salida con los cambios mencionados anteriormente, además de codificar el texto utilizando la tabla 
     de sustitucion dada:
     a | b | c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
     C | I | S | Q | V | N | F | O | W | A | X | M | T | G | U | H | P | B | K | L | R | E | Y | D | Z | J | 5 | 4 | 7 | 2 | 9 | 1 | 3 | 0 | 6 | 8 |

**/

%{
#include<stdio.h> 
 /**variables globales**/
int ocurrenciaPalabra=0, ocurrenciaInt=0;
%} 

%%
    /** Reduccion de espacios/eliminacion de caracteres: **/

[ ]+ 	fprintf(yyout," ");     /**espacios**/	
[\t]+ 	fprintf(yyout,"\t");	/**tabulaciones**/
\ñ	{fprintf(yyout,"n");};     /**reemplazo de "ñ" **/


    /** Eliminacion de comentarios **/

\#(.*) {};

    /**reemplazo de ";" por saltos de linea **/

\;	fprintf(yyout,"\n");




    /** Reemplazo de letras y numeros**/

a	fprintf(yyout,"C"); 
b	fprintf(yyout,"I"); 
c	fprintf(yyout,"S"); 
d	fprintf(yyout,"Q"); 
e	fprintf(yyout,"V"); 
f	fprintf(yyout,"N"); 
g	fprintf(yyout,"F"); 
h	fprintf(yyout,"O"); 
i	fprintf(yyout,"W"); 
j	fprintf(yyout,"A"); 
k	fprintf(yyout,"X"); 
l	fprintf(yyout,"M"); 
m	fprintf(yyout,"T"); 
n	fprintf(yyout,"G"); 
o	fprintf(yyout,"U"); 
p	fprintf(yyout,"H"); 
q	fprintf(yyout,"P"); 
r	fprintf(yyout,"B"); 
s	fprintf(yyout,"K"); 
t	fprintf(yyout,"L"); 
u	fprintf(yyout,"R"); 
v	fprintf(yyout,"E"); 
w	fprintf(yyout,"Y"); 
x	fprintf(yyout,"D"); 
y	fprintf(yyout,"Z"); 
z	fprintf(yyout,"J"); 
[0]	fprintf(yyout,"5"); 
[1]	fprintf(yyout,"4"); 
[2]	fprintf(yyout,"7"); 
[3]	fprintf(yyout,"2"); 
[4]	fprintf(yyout,"9"); 
[5]	fprintf(yyout,"1"); 
[6]	fprintf(yyout,"3"); 
[7]	fprintf(yyout,"0"); 
[8]	fprintf(yyout,"6"); 
[9]	fprintf(yyout,"8"); 

    /** Contador de enteros **/

[0-9]+ ocurrenciaInt++;


%%

int yywrap(){
	return 1;
} 

int main()
{
    FILE *arch;
    char nArch[30];
    printf("ingrese el nombre del archivo a leer: \n");
    scanf("%s", nArch);
    arch = fopen(nArch, "r");
    yyin = arch;
    yyout = fopen("salida", "w");
    yylex();
    printf ("numero de enteros encontrados: %d \n", ocurrenciaInt);

    return 0;

}