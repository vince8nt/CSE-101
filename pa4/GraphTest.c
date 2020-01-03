// Vincent Titterton
// vtittert
// pa4
// GraphTest.c

#include<stdio.h>
#include<stdlib.h>
#include"Graph.h"
#include"List.h"

int main(int argc, char* argv[])
{
	Graph D = newGraph(10);
	Graph U = newGraph(10);
	List path = newList();
	int i, j;

	for(i = 1; i < 11; i+=2)
	{
		for(j = 4; j < 8; ++j)
		{
			addEdge(U, i, j);
			addArc(D, i, j);
		}
	}

	BFS(D, 5);
	BFS(U, 3);

	printf("%d\n", getOrder(D));
	printf("%d\n", getOrder(U));

	printf("%d\n", getSize(D));
	printf("%d\n", getSize(U));

	printf("%d\n", getSource(D));
	printf("%d\n", getSource(U));

	printf("%d\n", getParent(D, 3));
	printf("%d\n", getParent(U, 8));

	getPath(path, D, 4);
	getPath(path, U, 5);

	printList(stdout, path);

	printGraph(stdout, D);
	printGraph(stdout, U);

	makeNull(D);
	printGraph(stdout, D);

	freeGraph(&D);
	freeGraph(&U);
	freeList(&path);
	return(0);
}
