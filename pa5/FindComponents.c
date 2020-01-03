// Vincent Titterton
// vtittert
// pa5
// FindComponents.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
	int n, s, d, i, j, k;
	List L;
	Graph G, T;
	FILE* in; // file handle for input
 	FILE* out; // file handle for output

 	// check command line for correct number of arguments
	if( argc != 3 )
	{
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	// open input file for reading
	in = fopen(argv[1], "r");
	if( in==NULL )
	{
		printf("Unable to read from file %s\n", argv[1]);
		exit(1);
	}

	// open output file for writing
	out = fopen(argv[2], "w");
	if( out==NULL )
	{
		printf("Unable to write to file %s\n", argv[2]);
		exit(1);
	}

	// scan Graph size
	fscanf(in, " %d", &n);

	// initalize new Graph
	G = newGraph(n);

	// add directed edges
	fscanf(in, " %d", &s);
	fscanf(in, " %d", &d);
	while(s != 0 && d != 0)
	{
		addArc(G, s, d);
		fscanf(in, " %d", &s);
		fscanf(in, " %d", &d);
	}

	// print Graph
	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	// initalize List
	L = newList();
	for(i = 0; i < n; ++i)
		append(L, i + 1);
	
	// first run of DFS
	DFS(G, L);

	// second run of DFS
	T = transpose(G);
	DFS(T, L);

	// get number of components
	i = 0;
	moveFront(L);
	while(index(L) != -1)
	{
		if(getParent(T, get(L)) == NIL)
			++i;
		moveNext(L);
	}

	// print num of scc
	fprintf(out, "\nG contains %d strongly connected components:", i);

	// print the scc
	i = 0;
	moveBack(L);
	while(index(L) != -1)
	{
		++i;
		fprintf(out, "\nComponent %d:", i);

		j = 0;
		while(1)
		{
			++j;
			if(getParent(T, get(L)) == NIL)
			{
				break;
			}
			movePrev(L);
			if(index(L) == -1)
			{
				moveFront(L);
				break;
			}
		}

		fprintf(out, " %d", get(L));
		for(k = 0; k < j - 1; ++k)
		{
			moveNext(L);
			fprintf(out, " %d", get(L));
		}

		for(k = 0; k < j; ++k)
		{
			movePrev(L);
		}
	}
	fprintf(out, "\n");

	// free Graph and Lists
	freeGraph(&G);
	freeGraph(&T);
	freeList(&L);

	// close files
	fclose(in);
  	fclose(out);

	return(0);
}





