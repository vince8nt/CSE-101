// Vincent Titterton
// vtittert
// pa1
// List.c

#include<stdio.h>
#include<stdlib.h>
#include "List.h"

// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj
{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev;
}
NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj
{
   Node front;
   Node back;
   Node cursor;
   int length;
   int index;
}
ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
// Private.
Node newNode(int data)
{
   Node N = malloc(sizeof(NodeObj));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN)
{
   if( pN!=NULL && *pN!=NULL )
   {
      free(*pN);
      *pN = NULL;
   }
}

// newList()
// Returns reference to new empty List object.
List newList(void)
{
   List L;
   L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->index = -1;
   L->length = 0;
   return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL
void freeList(List* pL)
{
   if(pL!=NULL && *pL!=NULL)
   { 
      while( !(length(*pL) == 0))
      { 
         deleteFront(*pL); 
      }
      free(*pL);
      *pL = NULL;
   }
}


// Access functions -----------------------------------------------------------

// length()
// Returns the number of elements in L.
int length(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling length() on NULL List reference\n");
      exit(1);
   }
   return(L->length);
}

// index()
// Returns index of cursor element if defined, -1 otherwise.
int index(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling index() on NULL List reference\n");
      exit(1);
   }
   return(L->index);
}

// front()
// Returns front element of L.
// Pre: length()>0
int front(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling front() on NULL List reference\n");
      exit(1);
   }
   if( L->length == 0 )
   {
      printf("List Error: calling front() on an empty List\n");
      exit(1);
   }
   return(L->front->data);
}

// back()
// Returns back element of L.
// Pre: length()>0
int back(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling back() on NULL List reference\n");
      exit(1);
   }
   if( L->length == 0 )
   {
      printf("List Error: calling back() on an empty List\n");
      exit(1);
   }
   return(L->back->data);
}

// get()
// Returns cursor element of L.
// Pre: length()>0, index()>=0
int get(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling get() on NULL List reference\n");
      exit(1);
   }
   if( L->cursor == NULL )
   {
      printf("List Error: calling get() with a NULL cursor\n");
      exit(1);
   }
   return(L->cursor->data);
}

// equals()
// Returns true (1) iff Lists A and B are in same
// state, and returns false (0) otherwise.
int equals(List A, List B)
{
   Node N = NULL;
   Node M = NULL;
   if( A==NULL || B==NULL)
   {
      printf("List Error: calling equals() on NULL List reference\n");
      exit(1);
   }
   if( A->length != B->length)
      return (0);
   N = A->front;
   M = B->front;
   while (N != NULL)
   {
      if(N->data != M->data)
         return (0);
      N = N->next;
      M = M->next;
   }
   return (1);
}


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state.
void clear(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling clear() on NULL List reference\n");
      exit(1);
   }
   while( length(L) != 0)
   { 
      deleteFront(L); 
   }
   L->cursor = NULL;
   L->index = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveFront() on NULL List reference\n");
      exit(1);
   }
   L->cursor = L->front;
   if(L->length !=0)
      L->index = 0;
}

// moveBack()
// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveBack() on NULL List reference\n");
      exit(1);
   }
   L->cursor = L->back;
   L->index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the
// front of L; if cursor is defined and at front, cursor becomes
// undefined; if cursor is undefined do nothing
void movePrev(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling movePrev() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL)
   {
      L->cursor = L->cursor->prev;
      L->index--;
   }
}

// moveNext()
// If cursor is defined and not at back, move cursor one step toward the
// back of L; if cursor is defined and at back, cursor becomes
// undefined; if cursor is undefined do nothing
void moveNext(List L)
{
   if( L==NULL )
   {
      printf("List Error: calling moveNext() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor != NULL)
   {
      L->cursor = L->cursor->next;
      if(L->cursor != NULL)
         L->index++;
      else
         L->index = -1;
   }
}

// prepend()
// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling prepend() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0)
   {
      L->front = L->back = N;
      L->length++;
   }
   else
   {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
      if(L->cursor != NULL)
         L->index++;
      L->length++;
   }
}

// append()
// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling append() on NULL List reference\n");
      exit(1);
   }
   if(L->length == 0)
   {
      L->front = L->back = N;
      L->length++;
   }
   else
   {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
      L->length++;
   }
}

// insertBefore()
// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling insertBefore() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor == NULL)
   {
      printf("List Error: calling insertBefore() with a NULL cursor\n");
      exit(1);
   }
   if(L->cursor == L->front)
   {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
      L->index++;
      L->length++;
   }
   else
   {
      N->prev = L->cursor->prev;
      N->next = L->cursor;
      L->cursor->prev->next = N;
      L->cursor->prev = N;
      L->index++;
      L->length++;
   }
}

// insertAfter()
// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, int data)
{
   Node N = newNode(data);
   if( L==NULL )
   {
      printf("List Error: calling insertAfter() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor == NULL)
   {
      printf("List Error: calling insertAfter() with a NULL cursor\n");
      exit(1);
   }
   if(L->cursor == L->back)
   {
      N->prev = L->back;
      L->back->next = N;
      L->back = N;
      L->length++;
   }
   else
   {
      N->next = L->cursor->next;
      N->prev = L->cursor;
      L->cursor->next->prev = N;
      L->cursor->next = N;
      L->length++;
   }
}

// deleteFront()
// Delete the front element. Pre: length()>0
void deleteFront(List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling deleteFront() on NULL List reference\n");
      exit(1);
   }
   if(L->front == NULL)
   {
      printf("List Error: calling deleteFront() with an empty List\n");
      exit(1);
   }
   if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   else
   {
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->prev = NULL;
      if(L->index == 0)
         L->cursor = NULL;
      L->index--;
      L->length--;
   }
}

// deleteBack()
// Delete the back element. Pre: length()>0
void deleteBack(List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling deleteBack() on NULL List reference\n");
      exit(1);
   }
   if(L->back == NULL)
   {
      printf("List Error: calling deleteBack() with an empty List\n");
      exit(1);
   }
   if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = L->cursor = NULL;
      L->index = -1;
      L->length = 0;
   }
   else
   {
      N = L->back;
      if(L->cursor == N)
      {
         L->cursor = NULL;
         L->index = -1;
      }
      L->back = L->back->prev;
      freeNode(&N);
      L->back->next = NULL;
      L->length--;
   }
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling delete() on NULL List reference\n");
      exit(1);
   }
   if(L->cursor == NULL)
   {
      printf("List Error: calling delete() with a NULL cursor\n");
      exit(1);
   }
   N = L->cursor;
   L->cursor = NULL;
   if(L->length == 1)
   {
      freeNode(&L->front);
      L->front = L->back = NULL;
   }
   else if(L->front == N)
   {
      N = L->front;
      L->front = L->front->next;
      freeNode(&N);
      L->front->prev = NULL;
   }
   else if(L->back == N)
   {
      N = L->back;
      L->back = L->back->prev;
      freeNode(&N);
      L->back->next = NULL;
   }
   else
   {
      N->prev->next = N->next;
      N->next->prev = N->prev;
      freeNode(&N);
   }
   L->length--;
   L->index = -1;
}

// Other Functions ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L
// consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L)
{
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next)
   {
      fprintf(out, "%d ", N->data);
   }
}

// copyList()
// Returns a new List representing the same integer sequence as L.
// The cursor in the new list is undefined, regardless of the state of
// the cursor in L. The state of L is unchanged.
List copyList(List L)
{
   List Copy = newList();
   Node N = NULL;
   if( L==NULL )
   {
      printf("List Error: calling copyList() on NULL List reference\n");
      exit(1);
   }
   N = L->front;
   while(N != NULL)
   {
      append(Copy, N->data);
      N = N->next;
   }
   return(Copy);
}









