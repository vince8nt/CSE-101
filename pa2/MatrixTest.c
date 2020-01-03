// Vincent Titterton
// vtittert
// pa2
// MatrixTest.c

#include<stdio.h>
#include<stdlib.h>
#include "Matrix.h"

int main()
{
	Matrix A = newMatrix(3);
   	Matrix B = newMatrix(3);
  	Matrix C, D, E, F, G, H;

  	changeEntry(A, 1,1,1); changeEntry(B, 1,1,1);
	changeEntry(A, 1,2,2); changeEntry(B, 1,2,0);
	changeEntry(A, 1,3,3); changeEntry(B, 1,3,1);
	changeEntry(A, 2,1,4); changeEntry(B, 2,1,0);
	changeEntry(A, 2,2,5); changeEntry(B, 2,2,1);
	changeEntry(A, 2,3,6); changeEntry(B, 2,3,0);
	changeEntry(A, 3,1,7); changeEntry(B, 3,1,1);
	changeEntry(A, 3,2,8); changeEntry(B, 3,2,1);
	changeEntry(A, 3,3,9); changeEntry(B, 3,3,1);

	C = scalarMult(2, A);
	printMatrix(stdout, C);
   	printf("\n");
   	freeMatrix(C);
   	C = scalarMult(0, B);//check for 0
   	printMatrix(stdout, C);
   	printf("\n");

   	D = sum(A, B);
	printf("%d\n", NNZ(D));
	printMatrix(stdout, D);
	printf("\n");
	freeMatrix(D);
	D = sum(A, A); //check with same input
	printf("%d\n", NNZ(D));
	printMatrix(stdout, D);
	printf("\n");
	

	E = diff(A, A); //same input
	printf("%d\n", NNZ(E));
	printMatrix(stdout, E);
	printf("\n");
	freeMatrix(E);
	E = diff(A, B); 
	printf("%d\n", NNZ(E));
	printMatrix(stdout, E);
	printf("\n");

	F = transpose(B);
	printf("%d\n", NNZ(F));
	printMatrix(stdout, F);
	printf("\n");

	//check the sum with the opposite
	freeMatrix(D);
	D = sum(B, F); //should be empty
	printf("%d\n", NNZ(D));
	printMatrix(stdout, D);
	printf("\n");

	G = product(B, B);
	printf("%d\n", NNZ(G));
	printMatrix(stdout, G);
	printf("\n");
	freeMatrix(G);
	makeZero(D);
	G = product(D, B); //product with a 0 matrix, should be zero
	printf("%d\n", NNZ(G));
	printMatrix(stdout, G);
	printf("\n");

	H = copy(A);
	printf("%d\n", NNZ(H));
	printMatrix(stdout, H);
	printf("\n");

	printf("%s\n", equals(A, H)?"true":"false" );
	printf("%s\n", equals(A, B)?"true":"false" );
	printf("%s\n", equals(A, A)?"true":"false" );

	freeMatrix(&A);
	freeMatrix(&B);
	freeMatrix(&C);
	freeMatrix(&D);
	freeMatrix(&E);
	freeMatrix(&F);
	freeMatrix(&G);
	freeMatrix(&H);

	return EXIT_SUCCESS;
}