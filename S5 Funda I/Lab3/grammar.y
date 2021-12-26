/*      GRAMMAR: ANALIZADOR SINTACTICO
Autor: Rodrigo Kobayashi

Analizador sintactico que genera un arbol de derivacion
para calcular sumas, restas, multiplicaciones y módulos 
entre números binarios.
*/

/* Librerías y , funciones y variables globales*/
%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "y.tab.h"
    #include "OpsBinarias.h"
    int yylex();
    int yywrap();
    void yyerror(char *s);
%}

%start program
/*prioridades de operaciones: Multiplicacion y módulo por sobre suma y resta*/
%token NUMERO
%left '+' '-'
%left '*' '%'

%%
    program:
        program expresion '\n'{
            printf("%d\n", $2);
        }
        |
        ;
    expresion:
        expresion '%' expresion{        /*se separa la expresion en dos expresiones y la accion de calcular el modulo */
            $$ = moduloBin($1 , $3);
        }
        |expresion '*' expresion{       /*se separa la expresion en dos expresiones y la accion de calcular la multiplicacion*/
            $$ = multBin($1, $3);
        }
        |expresion '+' expresion {      /* se separa la expresion en dos expresiones y la accion de calcular la suma*/
            $$ = sumaBin($1 , $3);
        }
        |expresion '-' expresion {      /* se separa la expresion en dos expresiones y la accion de calcular la resta*/
            $$ = restaBin($1 , $3);
        }
        | '(' expresion ')' {           /* se separa la expresion en una expresion y los parentesis que la rodean*/
            $$ = $2;
        }
        | NUMERO {                      /* Token */
            $$ = $1;
        }
        ;

%%

int main(){
    yyparse();
}

void yyerror(char *s){
    fprintf (stderr, "%s\n" , s);
}