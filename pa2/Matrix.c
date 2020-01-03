// Vincent Titterton
// vtittert
// pa2
// Matrix.c

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Matrix.h"

// structs --------------------------------------------------------------------

// private EntryObj type
typedef struct EntryObj
{
   int column;
   double value;
}
EntryObj;

// private Entry type
typedef EntryObj* Entry;

// private MatrixObj type
typedef struct MatrixObj
{
   int size;
   int NNZ;
   List* body;
}
MatrixObj;

// Constructors-Destructors ---------------------------------------------------

// newEntryObj()
// Returns reference to new Entry object.
// Private.
Entry newEntry(int n, double d)
{
   Entry E = malloc(sizeof(EntryObj));
   E->column = n;
   E->value = d;
   return(E);
}

// freeEntry()
// Frees heap memory pointed to by *pE, sets *pE to NULL.
// Private.
void freeEntry(Entry* pE)
{
   if( pE!=NULL && *pE!=NULL )
   {
      free(*pE);
      *pE = NULL;
   }
}

// newMatrix()
// Returns reference to a new nXn Matrix object in the zero state.
Matrix newMatrix(int n)
{
	int i;
	Matrix M;
	M = malloc(sizeof(MatrixObj));
	M->size = n;
	M->NNZ = 0;
	M->body = malloc(sizeof(List) * n);
	for(i=0; i<n; i++)
	{
		M->body[i] = newList();
	}
	return(M);
}

// freeMatrix()
// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM)
{
	int i;
	if(pM!=NULL && *pM!=NULL)
	{
		makeZero(*pM);
		for(i=0; i<(*pM)->size; i++)
		{
			freeList(&(*pM)->body[i]);
			(*pM)->body[i] = NULL;
		}
		free((*pM)->body);
	}
	free(*pM);
   	*pM = NULL;
}

// Access functions -----------------------------------------------------------

// size()
// Return the size of square Matrix M.
int size(Matrix M)
{
	if( M==NULL )
	{
   	printf("Matrix Error: calling size() on NULL Matrix reference\n");
   	exit(1);
	}
	return(M->size);
}

// NNZ()
// Return the number of non-zero elements in M.
int NNZ(Matrix M)
{
	if( M==NULL )
	{
   	printf("Matrix Error: calling NNZ() on NULL Matrix reference\n");
   	exit(1);
	}
	return(M->NNZ);
}

// equals()
// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals(Matrix A, Matrix B)
{
	int i;
	if( A==NULL || B==NULL )
	{
   	printf("Matrix Error: calling equals() on NULL Matrix reference\n");
   	exit(1);
	}
   
	if(A->size != B->size)
		return(0);
	for(i=0; i<A->size; i++)
	{
		if(length(A->body[i]) != length(B->body[i]))
			return(0);
		moveFront(A->body[i]);
		moveFront(B->body[i]);
		while(index(A->body[i]) > -1)
		{
			if(((Entry)get(A->body[i]))->column != 
            ((Entry)get(B->body[i]))->column)
				return(0);
			if(((Entry)get(A->body[i]))->value != 
            ((Entry)get(B->body[i]))->value)
				return(0);
         moveNext(A->body[i]);
         moveNext(B->body[i]);
		}
	}
	return(1);
   
}

// Manipulation procedures
// makeZero()
// Re-sets M to the zero Matrix.
void makeZero(Matrix M)
{
   int i;
   List L;
   Entry E;
	if( M==NULL )
   {
      printf("Matrix Error: calling makeZero() on NULL Matrix reference\n");
      exit(1);
   }
   M->NNZ = 0;
   for(i=0; i<M->size; i++)
   {
      L = M->body[i];
      moveFront(L);
      while(index(L) > -1)
      {
         E = (Entry)get(L);
         freeEntry(&E);
         moveNext(L);
      }
      clear(L);
   }
}

// changeEntry()
// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x)
{
   List L;
   Entry E;
	if( M==NULL )
	{
   	printf("Matrix Error: calling changeEntry() on NULL Matrix reference\n");
   	exit(1);
	}
   L = M->body[i - 1];
   if(x == 0)
   {
      moveFront(L);
      while(index(L)>-1 && ((Entry)get(L))->column<j)
         moveNext(L);
      if(index(L) > -1)
      {
         E = (Entry)get(L);
         freeEntry(&E);
         delete(L);
         M->NNZ--;
      }
   }
   else
   {
      if(length(L) == 0)
      {
         prepend(L, newEntry(j, x));
         M->NNZ++;
      }
      else
      {
         moveFront(L);
         while(index(L)>-1 && ((Entry)get(L))->column<j)
            moveNext(L);
         if(index(L) == -1)
         {
            append(L, newEntry(j, x));
            M->NNZ++;
         }
         else if(((Entry)get(L))->column == j)
         {
            ((Entry)get(L))->value = x;
         }
         else
         {
            insertBefore(L, newEntry(j, x));
            M->NNZ++;
         }
      }
   }
}

// Matrix Arithmetic operations
// copy()
// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A)
{
   int i;
   Matrix M;
   List La;
   List Lm;
   Entry E;
	if( A==NULL )
	{
   	printf("Matrix Error: calling copy() on NULL Matrix reference\n");
   	exit(1);
	}
   M = newMatrix(A->size);
   for(i=0; i<A->size; i++)
   {
      Lm = M->body[i];
      La = A->body[i];
      moveFront(La);
      while(index(La) > -1)
      {
         E = (Entry)get(La);
         append(Lm, newEntry(E->column, E->value));
         moveNext(La);
      }
   }
   M->NNZ = A->NNZ;
	return(M);
}

// transpose()
// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A)
{
   int i;
   Matrix M;
   List La;
   List Lm;
   Entry E;
	if( A==NULL )
	{
   	printf("Matrix Error: calling transpose() on NULL Matrix reference\n");
   	exit(1);
	}
	M = newMatrix(A->size);
   for(i=0; i<A->size; i++)
   {
      La = A->body[i];
      moveFront(La);
      while(index(La) > -1)
      {
         E = (Entry)get(La);
         Lm = M->body[E->column - 1];
         append(Lm, newEntry(i + 1, E->value));
         moveNext(La);
      }
   }
   M->NNZ = A->NNZ;
   return(M);
}

// scalarMult()
// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A)
{
   int i;
   Matrix M;
   List L;
	if( A==NULL )
	{
   	printf("Matrix Error: calling scalarMult() on NULL Matrix reference\n");
   	exit(1);
	}
   M = copy(A);
   if(x != 0)
   {
      for(i=0; i<M->size; i++)
      {
         L = M->body[i];
         moveFront(L);
         while(index(L) > -1)
         {
            ((Entry)get(L))->value *= x;
            moveNext(L);
         }
      }
   }
   else
   {
      makeZero(M);
   }
	return(M);
}

// sum()
// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B)
{
   int i;
   Matrix M;
   List La;
   List Lb;
   List Lm;
   Entry Ea;
   Entry Eb;
	if( A==NULL || B==NULL )
	{
   	printf("Matrix Error: calling sum() on NULL Matrix reference\n");
   	exit(1);
	}
   if(A->size != B->size)
   {
      printf("Matrix Error: calling sum() on matrices of different sizes\n");
      exit(1);
   }
   if(A == B)
   {
      return(scalarMult(2, A));
   }
   M = newMatrix(A->size);
   for(i=0; i<M->size; i++)
   {
      La = A->body[i];
      Lb = B->body[i];
      Lm = M->body[i];
      moveFront(La);
      moveFront(Lb);
      while(index(La)>-1 && index(Lb)>-1)
      {
         Ea = (Entry)get(La);
         Eb = (Entry)get(Lb);
         if(Ea->column < Eb->column)
         {
            append(Lm, newEntry(Ea->column, Ea->value));
            M->NNZ++;
            moveNext(La);
         }
         else if((Eb->column < Ea->column))
         {
            append(Lm, newEntry(Eb->column, Eb->value));
            M->NNZ++;
            moveNext(Lb);
         }
         else
         {
            if(Ea->value + Eb->value != 0)
            {
               append(Lm, newEntry(Ea->column, Ea->value + Eb->value));
               M->NNZ++;
            }
            moveNext(La);
            moveNext(Lb);
         }
      }
      while(index(La) > -1)
      {
         Ea = (Entry)get(La);
         append(Lm, newEntry(Ea->column, Ea->value));
         M->NNZ++;
         moveNext(La);
      }
      while(index(Lb) > -1)
      {
         Eb = (Entry)get(Lb);
         append(Lm, newEntry(Eb->column, Eb->value));
         M->NNZ++;
         moveNext(Lb);
      }
   }
	return(M);
}

// diff()
// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B)
{
   Matrix T1, T2, T3;
	if( A==NULL || B==NULL )
	{
   	printf("Matrix Error: calling diff() on NULL Matrix reference\n");
   	exit(1);
	}
   if(A->size != B->size)
   {
      printf("Matrix Error: calling diff() on matrices of different sizes\n");
      exit(1);
   }
   T1 = copy(B);
   T2 = scalarMult(-1, T1);
   T3 = sum(A, T2);
   freeMatrix(&T1);
   freeMatrix(&T2);
   return(T3);
}

// product()
// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B)
{
   int i;
   int j;
   double value;
   Matrix M;
   List La;
   List Lb;
   List Lm;
   Entry Ea;
   Entry Eb;
	if( A==NULL || B==NULL )
	{
   	printf("Matrix Error: calling product() on NULL Matrix reference\n");
   	exit(1);
	}
   if(A->size != B->size)
   {
      printf("Matrix Error: calling product() on matrices of different sizes\n");
      exit(1);
   }
   B = transpose(B);
   M = newMatrix(A->size);
   for(i=0; i<M->size; i++)
   {
      Lm = M->body[i];
      La = A->body[i];
      if(length(La) != 0)
      {
         for(j=0; j<M->size; j++)
         {
            Lb = B->body[j];
            value = 0;
            moveFront(La);
            moveFront(Lb);
            while(index(La)>-1 && index(Lb)>-1)
            {
               Ea = (Entry)get(La);
               Eb = (Entry)get(Lb);
               if(Ea->column < Eb->column)
                  moveNext(La);
               else if(Eb->column < Ea->column)
                  moveNext(Lb);
               else
               {
                  value+= Ea->value * Eb->value;
                  moveNext(La);
                  moveNext(Lb);
               }
            }
            if(value != 0)
            {
               append(Lm, newEntry(j + 1, value));
               M->NNZ++;
            }
         }
      }
   }
   freeMatrix(&B);
	return(M);
}

// printMatrix()
// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M)
{
   int i;
   List L;
	if( M==NULL )
	{
   	printf("Matrix Error: calling printMatrix() on NULL Matrix reference\n");
   	exit(1);
	}
   for(i=0; i<M->size; i++)
   {
      if (length(M->body[i]) > 0)
      {
         fprintf(out, "%d:", i + 1);
         L = M->body[i];
         moveFront(L);
         while(index(L) > -1)
         {
            fprintf(out, " (%d, %0.1f)",
               ((Entry)get(L))->column, ((Entry)get(L))->value);
            moveNext(L);
         }
         fprintf(out, "\n");
      }
   }
}









