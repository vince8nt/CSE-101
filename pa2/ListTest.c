// Vincent Titterton
// vtittert
// pa2
// ListTest.c

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[])
{
	List A = newList();
	List B = newList();
	int X[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
	int i // , u=-1, v=-2, equal=0;

	// initialize Lists A and B
	for(i=1; i<=20; i++){
		append(A, &X[i]);
		append(A, &X[20-i]);
		prepend(B, &X[i]);
	}

	printf("%d\n", length(A));

	moveFront(A);
	printf("%d\n", index(A));

	moveBack(A);
	printf("%d\n", index(A));

	// gets work at front and back
	moveFront(A);
	moveFront(B);
	get(A);
	get(B);
	moveBack(A);
	moveBack(B);
	get(A);
	get(B);

	printf("%d\n", *(int*)front(A));
	printf("%d\n", *(int*)back(B));
	moveFront(A);
	for(i=0; i<8; i++)
	{
		moveNext(A);
	}
	printf("%d\n", *(int*)get(A));

	for(i=0; i<100; i++)
	{
		moveNext(A);
		movePrev(A);
	}
	printf("%d\n", *(int*)get(A));

	for(i=0; i<8; i++)
	{
		insertBefore(A, &X[i]);
		insertAfter(A, &X[i]);
	}

	for(i=0; i<8; i++)
	{
		deleteFront(A);
		deleteBack(A);
	}

	delete(A); //make sure that cursor still exists


	// check length of A, before and after clear()
	printf("%d\n", length(A));
	clear(A);
	printf("%d\n", length(A));

	freeList(&A);
	freeList(&B);

	return(0);
}