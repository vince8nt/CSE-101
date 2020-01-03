// Vincent Titterton
// vtittert
// pa5
// Graph.c

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL -1
#define UNDEF -2


// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj
{
	List* adj;
	int length, order, size;
	int *parent, *discover, *finish;
}
GraphObj;


// Constructors-Destructors ---------------------------------------------------

// Returns a reference to a new Graph object with n vertices and 0 edges.
Graph newGraph(int n)
{
	int i;
	Graph G;
	G = malloc(sizeof(GraphObj));
	G->adj = malloc(sizeof(List) * n);
	G->parent = malloc(sizeof(int) * n);
	G->discover = malloc(sizeof(int) * n);
	G->finish = malloc(sizeof(int) * n);
	for(i = 0; i < n; ++i)
	{
		G->adj[i] = newList();
		G->parent[i] = NIL;
		G->discover[i] = G->finish[i] = UNDEF;
	}
	G->length = n;
	G->size = 0;
	G->order = NIL;
	return(G);
}

// Frees all heap memory associated with Graph *pG, and sets *pG to NULL
void freeGraph(Graph* pG)
{
	int i;
	if(pG != NULL && *pG != NULL)
	{ 
		for(i = 0; i < (*pG)->length; ++i)
		{
			freeList(&(*pG)->adj[i]);
		}
		free((*pG)->adj);
		free((*pG)->parent);
		free((*pG)->discover);
		free((*pG)->finish);
		free(*pG);
		*pG = NULL;
	}
}


// Access functions -----------------------------------------------------------

// returns the order of G or NIL if DFS hasn't been run yet
int getOrder(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getOrder called with NULL Graph reference");
		exit(1);
	}
	return(G->order);
}

// returns the number of edges in G
int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getSize called with NULL Graph reference");
		exit(1);
	}
	return(G->size);
}

// returns the parent of vertex u
int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getParent called with NULL Graph reference");
		exit(1);
	}
	if(G->parent[u - 1] == NIL)
		return(NIL);
	return(G->parent[u - 1] + 1);
}

// returns the discover time of vertex u
int getDiscover(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getDiscover called with NULL Graph reference");
		exit(1);
	}
	return(G->discover[u - 1]);
}

// returns the finish time of vertex u
int getFinish(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getFinish called with NULL Graph reference");
		exit(1);
	}
	return(G->finish[u - 1]);
}


// Manipulation procedures ----------------------------------------------------

// makes a directed edge from vertex u to vertex v
void addArc(Graph G, int u, int v)
{
	--u;
	--v;
	if(G == NULL)
	{
		printf("Graph Error: addArc called with NULL Graph reference");
		exit(1);
	}
	if(u < 0 || v < 0 || u >= G->length || v >= G->length)
	{
		printf("Graph Error: addArc called with invalid u/v");
		exit(1);
	}
	if(1)
	{
		moveFront(G->adj[u]);
		while(index(G->adj[u]) != -1 && get(G->adj[u]) < v)
		{
			moveNext(G->adj[u]);
		}
		if(index(G->adj[u]) == -1)
			append(G->adj[u], v);
		else
			insertBefore(G->adj[u], v);
		G->size++;
	}
}

// makes an undirected edge from vertex u to vertex v
void addEdge(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: addEdge called with NULL Graph reference");
		exit(1);
	}
	if(u < 1 || v < 1 || u > G->length || v > G->length)
	{
		printf("Graph Error: addEdge called with invalid u/v");
		exit(1);
	}
	if(u != v)
	{
		addArc(G, u, v);
		addArc(G, v, u);
		G->size--;
	}
}

void visit(Graph G, int x, int* time, List S)
{
	G->discover[x] = ++(*time);
	moveFront(G->adj[x]);
	while(index(G->adj[x]) != -1)
	{
		if(G->discover[get(G->adj[x])] == UNDEF)
		{
			G->parent[get(G->adj[x])] = x;
			visit(G, get(G->adj[x]), time, S);
		}
		moveNext(G->adj[x]);
	}
	G->finish[x] = ++(*time);
	prepend(S, x + 1);
}

// sets order, parent, discover, and finish
void DFS(Graph G, List S)
{
	int i;
	int* time;
	List L;
	if(G == NULL)
	{
		printf("Graph Error: DFS called with NULL Graph reference");
		exit(1);
	}
	if(G->length != length(S))
	{
		printf("Graph Error: DFS called with incorrectly sized S");
		exit(1);
	}
	for(i = 0; i < G->length; ++i)
	{
		G->parent[i] = NIL;
		G->discover[i] = UNDEF;
	}
	time = calloc(sizeof(int), 1);
	L = copyList(S);
	clear(S);
	moveFront(L);
	while(index(L) != -1)
	{
		if(G->discover[get(L) - 1] == UNDEF)
		{
			visit(G, get(L) - 1, time, S);
		}
		moveNext(L);
	}
	free(time);
	freeList(&L);
}


// Other operations ----------------------------------------------------

// returns a transpose of G
Graph transpose(Graph G)
{
	int i;
	Graph R;
	if(G == NULL)
	{
		printf("Graph Error: transpose called with NULL Graph reference");
		exit(1);
	}
	R = newGraph(G->length);
	for(i = 0; i < G->length; ++i)
	{
		moveFront(G->adj[i]);
		while(index(G->adj[i]) != -1)
		{
			addArc(R, get(G->adj[i]) + 1, i + 1);
			moveNext(G->adj[i]);
		}
	}
	R->size = G->size;
	return(R);
}

// returns a copy of G
Graph copyGraph(Graph G)
{
	int i;
	Graph R;
	if(G == NULL)
	{
		printf("Graph Error: copyGraph called with NULL Graph reference");
		exit(1);
	}
	R = newGraph(G->length);
	for(i = 0; i < G->length; ++i)
	{
		freeList(&R->adj[i]);
		R->adj[i] = copyList(G->adj[i]);
		R->parent[i] = G->parent[i];
		R->discover[i] = G->discover[i];
		R->finish[i] = G->finish[i];
	}
	R->size = G->size;
	R->order = G->order;
	return(R);
}

// prints a string representation of G to FILE* out
void printGraph(FILE* out, Graph G)
{
	int i;
	if(G == NULL)
	{
		printf("Graph Error: printGraph called with NULL Graph reference");
		exit(1);
	}
	for(i = 0; i < G->length; ++i)
	{
		fprintf(out, "%d:", i + 1);
		moveFront(G->adj[i]);
		while(index(G->adj[i]) != -1)
		{
			fprintf(out, " %d", get(G->adj[i]) + 1);
			moveNext(G->adj[i]);
		}
		fprintf(out, "\n");
	}
}




