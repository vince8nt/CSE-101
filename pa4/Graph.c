// Vincent Titterton
// vtittert
// pa4
// Graph.c

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"
#define NIL -1
#define INF -2


// structs --------------------------------------------------------------------

// private GraphObj type
typedef struct GraphObj
{
	List* adj;
	int length;
	int source;
	int order;
	int size;
	int* parent;
	int* dist;
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
	G->dist = malloc(sizeof(int) * n);
	for(i = 0; i < n; ++i)
	{
		G->adj[i] = newList();
		G->parent[i] = G->dist[i] = -1;
	}
	G->length = n;
	G->size = 0;
	G->source = -1;
	G->order = -1;
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
		free((*pG)->dist);
		free(*pG);
		*pG = NULL;
	}
}


// Access functions -----------------------------------------------------------

// returns the order of G or NIL if BFS hasn't been run yet
int getOrder(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getOrder called with NULL Graph reference");
		exit(1);
	}
	return(G->order);
}

// returns number of vertices
int getSize(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getSize called with NULL Graph reference");
		exit(1);
	}
	return(G->size);
}

// returns the most recent source used in BFS or NIL if BFS hasn't been run
int getSource(Graph G)
{
	if(G == NULL)
	{
		printf("Graph Error: getSource called with NULL Graph reference");
		exit(1);
	}
	if(G->source == -1)
		return(NIL);
	return(G->source);
}

int getParent(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getParent called with NULL Graph reference");
		exit(1);
	}
	if(G->parent[u - 1] == -1)
		return(NIL);
	return(G->parent[u - 1] + 1);
}

int getDist(Graph G, int u)
{
	if(G == NULL)
	{
		printf("Graph Error: getDist called with NULL Graph reference");
		exit(1);
	}
	if(G->dist[u - 1] == -1)
		return(INF);
	return(G->dist[u - 1]);
}

// makes L list the path from the source to u
void getPath(List L, Graph G, int u)
{
	List Q;
	if(G == NULL)
	{
		printf("Graph Error: getPath called with NULL Graph reference");
		exit(1);
	}
	if(L == NULL)
	{
		printf("Graph Error: getDist called with NULL List reference");
		exit(1);
	}
	if(u > G->length)
	{
		printf("Graph Error: getPath called with invalid u");
		exit(1);
	}
	Q = newList();
	--u;
	while(u != G->source - 1)
	{
		if(u < 0)
		{
			clear(Q);
			break;
		}
		prepend(Q, u + 1);
		u = G->parent[u];
	}
	if(u >= 0)
	{
		prepend(Q, u + 1);
		while(length(Q) != 0)
		{
			append(L, front(Q));
			deleteFront(Q);
		}
	}
	else
		append(L, NIL);
	
	freeList(&Q);
}


// Manipulation procedures ----------------------------------------------------

// removes all edges from Graph G
void makeNull(Graph G)
{
	int i;
	if(G == NULL)
	{
		printf("Graph Error: makeNull called with NULL Graph reference");
		exit(1);
	}
	for(i = 0; i < G->length; ++i)
	{
		clear(G->adj[i]);
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

// makes a directed edge from vertex u to vertex v
void addArc(Graph G, int u, int v)
{
	if(G == NULL)
	{
		printf("Graph Error: addArc called with NULL Graph reference");
		exit(1);
	}
	if(u < 1 || v < 1 || u > G->length || v > G->length)
	{
		printf("Graph Error: addArc called with invalid u/v");
		exit(1);
	}
	if(u != v)
	{
		moveFront(G->adj[u - 1]);
		while(index(G->adj[u - 1]) != -1 && get(G->adj[u - 1]) < v - 1)
		{
			moveNext(G->adj[u - 1]);
		}
		if(index(G->adj[u - 1]) == -1)
			append(G->adj[u - 1], v - 1);
		else
			insertBefore(G->adj[u - 1], v - 1);
		G->size++;
	}
}

// sets source, order, parent*, and dist*
void BFS(Graph G, int s)
{
	int i, x, y;
	List Q;
	if(G == NULL)
	{
		printf("Graph Error: BFS called with NULL Graph reference");
		exit(1);
	}
	if(s < 1 || G->length < s)
	{
		printf("Graph Error: BFS called with invalid s");
		exit(1);
	}
	G->source = s;
	--s;
	for(i = 0; i < G->length; ++i)
	{
		G->parent[i] = G->dist[i] = -1;
	}
	G->order = 1;
	G->dist[s] = 0;
	Q = newList();
	append(Q, s);
	while(length(Q) != 0)
	{
		x = front(Q);
		deleteFront(Q);
		moveFront(G->adj[x]);
		while(index(G->adj[x]) != -1)
		{
			y = get(G->adj[x]);
			if(G->dist[y] == -1)
			{
				G->dist[y] = G->dist[x] + 1;
				G->parent[y] = x;
				append(Q, y);
				if(G->dist[y] > G->order + 1)
					G->order = G->dist[y] + 1;
			}
			moveNext(G->adj[x]);
		}
	}
	freeList(&Q);
}


// Other operations ----------------------------------------------------

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







