 /* LEXER: parser de símbolos y números */
/*      Autor: Rodrigo Kobayashi      */
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    extern int yylval;
%}

%%
[01]+ {                          
    yylval = atoi(yytext);      /* en caso de encontrar un string de ceros y unos, estos se convierten a enteros*/
    return NUMERO;
}
[-%*+()]   {return *yytext;}   /* en caso de encontrar símbolos de suma, resta, multiplicación, módulo y paréntesis, se retornan como string*/
[\r?\n] {return *yytext;}       /* se ignoran espacios y saltos de línea*/
.       {ECHO;}                 /* el resto se imprime para saber en que parte del string está el error */

%%