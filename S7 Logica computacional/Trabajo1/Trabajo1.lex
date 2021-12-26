%{
#define MAXSIZE 100
#define NEG -1
#define AND -2
#define OR -3
#define IMPLICATON -4
#define LEFTP -5
#define RIGHTP -6
int stack[MAXSIZE], list[MAXSIZE], posStack = 0, posList = 0;

%}
leftParentheses \(
rightParentheses \)
wedge \\wedge
rightarrow \\rightarrow
vee   \\vee   
neg   \\neg
variable v"_"\{([1-9]|[12][0-9]|3[012])\}    
%%
{wedge}           add(AND);     
{rightarrow}            add(IMPLICATON);           
{vee}          add(OR);     
{neg}          add(NEG);     
{variable}           add(textToInt(yytext));      
{leftParentheses}          add(LEFTP);
{rightParentheses}            add(RIGHTP);
.           ;
%%
/*añade la variable u operacion a la lista de forma que quede como reverse polish notation*/
void add(int flag){

/*caso: variable, se agrega directamente a la lista*/
   if(flag > 0){      
      list[posList] = flag;
      posList ++;
   }
   else{

/*caso: parentesis izquierdo, se agrega directamente al stack*/
      if (flag == LEFTP){     
         stack[posStack] = flag;
         posStack ++;
      }

/*caso: parentesis derecho, se agregan elementos de la pila a la lista hasta que se encuentra un parentesis izquierdo*/
      else if(flag == RIGHTP){   
         while( stack[posStack-1] != LEFTP && posStack != 1){
            list[posList] = stack[posStack-1];
            posList ++;
            posStack --;
         }
         posStack --;
      }
/*caso: operadores*/
      /*stack vacio o prioridad mayor que el primer elemento del stack, se agrega el operador al stack*/
      else if(posStack == 0 || flag >= stack[posStack-1]){
         stack[posStack] = flag;
         posStack ++;
      }
      /*prioridad del elemento menor a la del operador en el primer lugar del stack, se agrega el primer elemento del stack a la lista
        y se compara nuevamente hasta que se encuentre un operador con prioridad menor o se vacíe la lista.*/
      else{
         while(posStack != 1 && stack[posStack-1] > flag){
            list[posList] = stack[posStack-1];
            posStack --;
            posList ++;
         }
         stack[posStack] = flag;
         posStack ++;
      }
   }
}                     


/*funcion para extraer el numero de la variable leida*/
int textToInt(char *text){
   char str[yyleng], letter;
   int number;
   memcpy(str, text, yyleng);
   if(yyleng == 5){
      letter =str[3];
      number = (int)letter-48;
   }
   else{
      letter = str[3];
      number = 10*((int)letter-48);
      letter = str[4];
      number += (int)letter-48;
   }
  return number;
}

/*Funcion para elevar una base a un exponente*/
int pow(base,exponent){
   int result = 1;
   for (int i = 0; i<exponent; i++){
      result *= base;
   }
   return result;
}


/*funcion para resolver una fila de la tabla de verdad mediante la lista de operaciones extraida del texto*/
int resolverFila(int *fila,int nVariables){
   int posFila = nVariables;                 /*Definicion de variables*/
   int stackr[MAXSIZE], posStackr = 0;
   for(int k = 0; k < posList; k ++){
/*Caso: list[k] es una variable, el valor de la variable segun la matriz se ingresa al stack*/
      if(list[k] > 0){                          
         stackr[posStackr] = fila[list[k]-1];
         posStackr++;
      }
/*Caso: list[k] es una negacion, se le aplica la negacion al primer elemento del stack*/
      else if(list[k] == NEG){
         stackr[posStackr-1] = !stackr[posStackr-1];
         fila[posFila] = stackr[posStackr-1];
         posFila++;
      }
/*Caso: list[k] es una conjuncion, se genera la conjuncion a los primeros dos elementos del stack, sacandolos, y se guarda el resultado en el stack*/
      else if(list[k] == AND){
         stackr[posStackr-1] = stackr[posStackr-1] && stackr[posStackr];
         posStackr --;
         fila[posFila] = stackr[posStackr];
         posFila ++;
      } 
/*Caso: list[k] es una disyuncion, se  genera la disyuncion de los dos primeros elementos del stack, sacandolos, y se guarda el resultado en el stack*/
      else if(list[k] == OR){
         stackr[posStackr-1] = stackr[posStackr-1] || stackr[posStackr];
         posStackr --;
         fila[posFila] = stackr[posStackr];
         posFila ++;
      } 
/*Caso: list[k] es una implicacion, se genera la implicacion desde el segundo valor al primero del stack, sacandolos, y se guarda el resultado en el stack*/
      else if(list[k] == IMPLICATON){
         stackr[posStackr-1] = !stackr[posStackr-2] || stackr[posStackr-1];
         posStackr --;
         fila[posFila] = stackr[posStackr];
         posFila ++;
      }
   }
   return posFila;
}


int main(int argc, char* argv[]) {
/*Declaracion de variables*/  
   int nVariables = 0, matrizY, interval, x, y, flag = 0, matrizX, result = 1;
/*Se corre el analizador lexico*/
   yylex();
/*Se agrega todo elemento que pudo haber quedado en el stack a la lista*/
   while(posStack != 0){
      list[posList] = stack[posStack-1];
      posList ++;
      posStack --;
   }

/*se cuenta el numero de variables de la lista*/
   for (int i = 0; i<posList; i++){
      if (list[i] >nVariables){
         nVariables = list[i];
      }
   }

/*creacion de la matriz que representa la tabla de verdad*/
   matrizY = pow(2, nVariables);
   interval = matrizY/2;
   int *matriz[MAXSIZE];   
   for (int i = 0; i<MAXSIZE; i++){
      matriz[i] = malloc(matrizY*sizeof(int));
   }
   for (x = 0; x < nVariables; x++){  
      for (y = 0; y<matrizY; y++){
         matriz[y][x] = flag;
         if ((y+1)% interval == 0){
            flag = !flag;
         }
      }
      interval = interval / 2;
   }


/*Se resuelve la tabla de verdad, fila por fila */
   for(int l = 0; l<matrizY; l++){
      matrizX = resolverFila(matriz[l], nVariables);
   }


/*Se muestra la tabla de verdad, si el modo verboso esta activado*/
   if(argc >= 2){
      if(strcmp(argv[1], "-V") == 0){
         for (int i = 0; i< matrizY; i++){
            for (int j = 0; j< matrizX; j++ ){
               printf("%d ", matriz[i][j]);
            }
            printf("\n");
         }
      }
   }


/*Se comprueba el valor de la expresion logica*/
   for (int i = 0 ; i< matrizY; i++){
      if(matriz[i][matrizX-1] != matriz[0][matrizX-1]){
         result = 0;
      }
   }

/*Se muestra el valor de la expresion logica*/
   if(result == 1 && matriz[0][matrizX-1] == 1){
      printf("Tautologia\n");
   } 
   else if(result == 1 && matriz[0][matrizX-1] == 0){
      printf("Contradiccion\n");
   }
   else{
      printf("contingencia\n");
   }

}  
