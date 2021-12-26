gcc --version
gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0

Compilación:

lex parser.lex
gcc lex.yy.c
./a.out

El programa debe estar en la misma carpeta que el fichero de texto
de prueba, los resultados estarán ubicados en la misma carpeta bajo el nombre
de "salida"
