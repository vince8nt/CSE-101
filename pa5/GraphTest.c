// Vincent Titterton
// vtittert
// pa5
// GraphTest.h

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[])
{
	Graph D = newGraph(10);
	Graph U = newGraph(10);
	List L = newList();
	int i, j;

	for(i = 1; i < 11; ++i)
	{
		append(L, i);
	}

	for(i = 1; i < 11; i+=2)
	{
		for(j = 4; j < 8; ++j)
		{
			addEdge(U, i, j);
			addArc(D, i, j);
		}
	}

	DFS(D, L);
	DFS(U, L);

	printf("%d\n", getOrder(D));
	printf("%d\n", getOrder(U));

	printf("%d\n", getSize(D));
	printf("%d\n", getSize(U));

	printf("%d\n", getParent(D, 3));
	printf("%d\n", getParent(U, 8));

	printf("%d\n", getDiscover(D, 3));
	printf("%d\n", getDiscover(U, 8));

	printf("%d\n", getFinish(D, 3));
	printf("%d\n", getFinish(U, 8));

	printGraph(stdout, D);
	printGraph(stdout, U);

	freeGraph(&D);
	freeGraph(&U);
	freeList(&L);
	return(0);
}
