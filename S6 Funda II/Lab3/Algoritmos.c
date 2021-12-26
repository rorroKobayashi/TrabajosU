#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*

	Fibonaxi Recursivo inicio

*/

unsigned long long int FibonaxiRecursivo(int n){
	
	if(n < 2){

		return 1;

	}

	return FibonaxiRecursivo(n - 1) + FibonaxiRecursivo(n - 2);

}

/*

	Fibonaxi Recursivo fin

*/



/*

	Fibonaxi interativo inicio

*/

unsigned long long int FibonaxiIterativo(int n){
	
	unsigned long long int d = 0, e = 0, f = 1;

	for(d = 0; d < n; d++){

		e = f + e;
		f = e - f;

	}

	return e;
}


/*

	Fibonaxi interativo fin

*/

/*

	Fibonaxi matrix exponentation inicio

*/

void showMatrix(unsigned long long int **matrix){

	unsigned int d = 0, e = 0;

	printf("\n");

	for(d = 0; d < 2; d++){

		for(e = 0; e < 2; e++){

			printf("%lld\t", matrix[d][e]);

		}

		printf("\n");

	}

	printf("\n");

}


unsigned long long int **setMatrix(unsigned long long int **m, int tam){

	unsigned int d = 0, e = 0;

	for(d = 0; d < tam; d++){

		for(e = 0; e < tam; e++){

			m[d][e] = 0;

		}

	}

	return m;
}


unsigned long long int **initMatrix(unsigned long long int **m, int tam){

	unsigned int d = 0;

	m = malloc(tam * sizeof(unsigned long long int *));

	for(d = 0; d < tam; d++){

		m[d] = malloc(tam * sizeof(unsigned long long int));
		
	}

	return m;
}


unsigned long long int **BTMultiplication(unsigned long long int **m1, unsigned long long int **m2, unsigned long long **m3){

	unsigned int d = 0, e = 0, f = 0;

	for(d = 0; d < 2; d++){

		for(e = 0; e < 2; e++){

			for(f = 0; f < 2; f++){

				m3[d][e] = m3[d][e] + (m1[d][f] * m2[e][f]);

			}

		}

	}

	return m3;

}



unsigned long long int **exponentation(int n, unsigned long long int **mt, unsigned long long int **mresult, unsigned long long int **zero){

	unsigned int d = 0;

	for(d = 0; d < n - 1; d++){
		
		if(d > 0){ //Si d > 0 entonces, multiplicar resultado por la matrix mt

			zero = BTMultiplication(mresult, mt, zero);

		}else{ //Sino, entonces es el primer paso, por tanto se multiplica la matrix mt por si misma

			zero = BTMultiplication(mt, mt, zero);

		}

		//Se copia la matrix zero en mresult

		mresult[0][0] = zero[0][0];
		mresult[0][1] = zero[0][1];
		mresult[1][0] = zero[1][0];
		mresult[1][1] = zero[1][1];

		//Se setea la matrix zero en cero matrix

		zero = setMatrix(zero, 2);

	}

	return mresult;
}

unsigned long long int **binaryExponentation(int n, unsigned long long int **mt, unsigned long long int **mresult, unsigned long long int **zero){

	char flag = '0';

	while(n > 0){

		if(n % 2 == 1){

			//Si es la primera vez que se entra en este condicional
			//mt se copia en mresult, pues mresult es identidad

			zero = BTMultiplication(mresult, mt, zero);
			
			mresult[0][0] = zero[0][0];
			mresult[0][1] = zero[0][1];
			mresult[1][0] = zero[1][0];
			mresult[1][1] = zero[1][1];

			zero = setMatrix(zero, 2);

			flag = '1';

		}

		zero = BTMultiplication(mt, mt, zero);

		mt[0][0] = zero[0][0];
		mt[0][1] = zero[0][1];
		mt[1][0] = zero[1][0];
		mt[1][1] = zero[1][1];

		zero = setMatrix(zero, 2);

		n = n / 2;

	}

	//Los numeros que son iguales 2^k nunca entran en el condicional
	//Por lo que es necesario marcar cuando se entra y cuando no
	
	if(flag == '1'){
		return mresult;
	}

	return mt;


}

unsigned long long int binaryFibonaxi(int n){

	unsigned long long int **mt, **mresult, **zero;

	if(n < 2){ //Caso base

		return 1; 

	}else{ //Caso general

		/*

			Inicializacion de matrices

		*/

		mt = initMatrix(mt, 2);
		mresult = initMatrix(mresult, 2);
		zero = initMatrix(zero, 2);

		mt = setMatrix(mt, 2);
		mresult = setMatrix(mresult, 2);
		zero = setMatrix(zero, 2);

		mt[0][1] = 1;
		mt[1][0] = 1;
		mt[1][1] = 1;

		//Se define mresult como identidad 2x2

		mresult[0][0] = 1;
		mresult[1][1] = 1;

		mresult = binaryExponentation(n, mt, mresult, zero); //Computo de power matrix

		return mresult[1][0];
	}

}

unsigned long long int linearFibonaxi(int n){

	unsigned long long int **mt, **mresult, **zero;

	if(n < 2){ //Caso base

		return 1; 

	}else{ //Caso general

		/*

			Inicializacion de matrices

		*/

		mt = initMatrix(mt, 2);
		mresult = initMatrix(mresult, 2);
		zero = initMatrix(zero, 2);

		mt = setMatrix(mt, 2);
		mresult = setMatrix(mresult, 2);
		zero = setMatrix(zero, 2);

		mt[0][1] = 1;
		mt[1][0] = 1;
		mt[1][1] = 1;

		mresult = exponentation(n, mt, mresult, zero); //Computo de power matrix

		return mresult[1][0];
	}


}

/*

	Fibonaxi matrix exponentation fin

*/




int main(int argc, char *argv[]){

	int n = 0;
	unsigned long long int r1 = 0, r2 = 0, r3 = 0, r4 = 0;
	double recursiveT = 0, iterativeT = 0, matrixT = 0, binaryT = 0;
	clock_t initR, initI, initM, finR, finI, finM, initB, finB;
	
	n = atoi(argv[1]);

	initR = clock();
	r1 = FibonaxiRecursivo(n - 1);
	finR = clock();

	initI = clock();
	r2 = FibonaxiIterativo(n);
	finI = clock();

	initM = clock();
	r3 = linearFibonaxi(n);
	finM = clock();

	initB = clock();
	r4 = binaryFibonaxi(n);
	finB = clock();

	matrixT = ((double) finM - initM) / CLOCKS_PER_SEC;
	binaryT = ((double) finB - initB) / CLOCKS_PER_SEC;
	recursiveT = ((double) finR - initR) / CLOCKS_PER_SEC;
	iterativeT = ((double) finI - initI) / CLOCKS_PER_SEC;

	printf("Posicion: %d", n);

	printf("\n\nAlgortimo\t\tRESULTADO\t\tTIEMPO\n\n");
	printf("Recursivo\t\t%llu\t\t\t%f\n\n", r1, recursiveT);
	printf("Iterativo\t\t%llu\t\t\t%f\n\n", r2, iterativeT);
	printf("Power_Matrix\t\t%llu\t\t\t%f\n\n", r3, matrixT);
	printf("B_Power_Matrix\t\t%llu\t\t\t%f\n\n\n", r4, binaryT);


	return 0;
}

