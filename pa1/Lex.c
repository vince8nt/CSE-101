// Vincent Titterton
// vtittert
// pa1
// Lex.c

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "List.h"
#define MAX_LEN 63

int main(int argc, char* argv[])
{
	int lines;
	int i;
	char string[MAX_LEN];
	FILE* in; // file handle for input
 	FILE* out; // file handle for output
 	List stringList = newList();

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

	// sets lines to #of lines in FILE in
	lines = 0;
   	while( fgets(string, MAX_LEN, in) != NULL)
   	{
      	lines++;
  	}

  	// initializes stringArray
  	char stringArray[lines][MAX_LEN];

  	// reset in
  	fclose(in);
  	in = fopen(argv[1], "r");

  	// fills stringArray
	lines = 0;
   	while( fgets(string, MAX_LEN, in) != NULL)
   	{
   		for(i = 0; i < MAX_LEN; i++)
   		{
   			stringArray[lines][i] = string[i];
   		}
      	lines++;
  	}

	// modded insertion sort
	for (i = 0; i < lines; i++)
	{
		moveBack(stringList);
		while(index(stringList) > -1 && strcmp(stringArray[i], stringArray[get(stringList)]) < 0)
		{
			movePrev(stringList);
		}
		if(index(stringList) > -1)
			insertAfter(stringList, i);
		else
			prepend(stringList, i);
	}

	// print stringList to out
	moveFront(stringList);
	while (index(stringList) > -1)
	{
		fprintf(out, "%s", stringArray[get(stringList)]);
		moveNext(stringList);
	}

	// free list
	freeList(&stringList);
	stringList = NULL;

  	// close files
  	fclose(in);
  	fclose(out);

  	return(0);
}











