// Vincent Titterton
// vtittert
// pa3
// ListTest.c

#include<stdio.h>
#include<stdlib.h>
#include "List.h" 
int main(int argc, char* argv[]){
   
   List A = newList();
   List B = newList();
   List C = NULL;
   long i;

   for(i=1; i<=20; i++){
      append(A,i);
      prepend(A, i);
      prepend(B,i);
      append(B,i);
   }

   printList(stdout,B); 
   printf("\n");
   printList(stdout,A); 
   printf("\n");
   

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", get(B));
   }
   printf("\n");

   moveFront(A);
   for(i=0; i<5; i++) moveNext(A); 
   insertAfter(A, -2);
   for(i=0; i<5; i++) movePrev(A); 
   insertBefore(A, -1);            
   for(i=0; i<9; i++) moveNext(A); 
   
   delete(A);
   printList(stdout,A);
   printf("\n");
   printf("%d\n", length(A));
   clear(A);
   printf("%d\n", length(A));

   freeList(&A);
   freeList(&B);
   freeList(&C);

   return(0);
}