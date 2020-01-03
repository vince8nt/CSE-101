// Vincent Titterton
// vtittert
// pa4
// FindPath.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char* argv[])
{
	int n, s, d;
	List source, dest, path;
	Graph G;
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

	// add edges
	fscanf(in, " %d", &s);
	fscanf(in, " %d", &d);
	while(s != 0 && d != 0)
	{
		addEdge(G, s, d);
		fscanf(in, " %d", &s);
		fscanf(in, " %d", &d);
	}

	// fill source dest pairs
	source = newList();
	dest = newList();
	path = newList();
	fscanf(in, " %d", &s);
	fscanf(in, " %d", &d);
	while(s != 0 && d != 0)
	{
		append(source, s);
		append(dest, d);
		fscanf(in, " %d", &s);
		fscanf(in, " %d", &d);
	}

	// print Graph
	printGraph(out, G);
	
	// print BFS results
	while(length(source) != 0)
	{
		fprintf(out, "\n");
		s = front(source);
		deleteFront(source);
		d = front(dest);
		deleteFront(dest);
		BFS(G, s);
		clear(path);
		getPath(path, G, d);
		if(front(path) == NIL)
		{
			fprintf(out, "The distance from %d to %d is infinity\n", s, d);
			fprintf(out, "No %d-%d path exists\n", s, d);
		}
		else
		{
			fprintf(out, "The distance from %d to %d is %d\n", s, d, getDist(G, d));
			fprintf(out, "A shortest %d-%d path is: ", s, d);
			printList(out, path);
			fprintf(out, "\n");
		}
	}

	// free Graph and Lists
	freeGraph(&G);
	freeList(&source);
	freeList(&dest);
	freeList(&path);

	// close files
	fclose(in);
  	fclose(out);

	return(0);
}