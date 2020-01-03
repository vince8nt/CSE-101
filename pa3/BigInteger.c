// Vincent Titterton
// vtittert
// pa3
// BigInteger.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "BigInteger.h"
#include "List.h"
# define BASE 1000000000
# define POWER 9

// structs --------------------------------------------------------------------

// private BigInteger
typedef struct BigIntegerObj
{
   	int sign;
   	List body;
}
BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------

BigInteger newBigInteger()
{
	BigInteger N;
	N = malloc(sizeof(BigIntegerObj));
	N->sign = 0;
	N->body = newList();
	return(N);
}

void freeBigInteger(BigInteger* pN)
{
	if(pN!=NULL && *pN!=NULL)
   { 
      freeList(&(*pN)->body);
      free(*pN);
      *pN = NULL;
   }
}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero
// state.
int sign(BigInteger N)
{
	if(N == NULL)
	{
		printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
		exit(1);
	}
	return(N->sign);
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B.
int compare(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling compare() on NULL BigInteger reference\n");
		exit(1);
	}
	if(A==B)
		return(0);
	if(A->sign < B->sign)
		return(-1);
	if(A->sign > B->sign)
		return(1);
	if(length(A->body) < length(B->body))
		return(-1 * A->sign);
	if(length(A->body) > length(B->body))
		return(1 * A->sign);
	moveBack(A->body);
	moveBack(B->body);
	while(index(A->body) != -1)
	{
		if(get(A->body) < get(B->body))
			return(-1 * A->sign);
		if(get(A->body) > get(B->body))
			return(1 * A->sign);
		moveNext(A->body);
		moveNext(B->body);
	}
	return(0);
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise.
int equals(BigInteger A, BigInteger B)
{
	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
		exit(1);
	}
	if(compare(A, B) == 0)
		return(1);
	return(0);
}

// Manipulation procedures ----------------------------------------------------

// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N)
{
	if(N == NULL)
	{
		printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
		exit(1);
	}
	N->sign = 0;
	clear(N->body);
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the
// zero state.
void negate(BigInteger N)
{
	if(N == NULL)
	{
		printf("BigInteger Error: calling negate() on NULL BigInteger reference\n");
		exit(1);
	}
	N->sign*= -1;
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s.
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix.
BigInteger stringToBigInteger(char* s)
{
	int i;
    int mult;
    long digit;
    BigInteger N;
    List L;
    i = 0;
    N = newBigInteger();
    if(s == NULL)
    {
	    printf("BigInteger Error: calling stringToBigInteger() on NULL char* reference\n");
	    exit(1);
    }
    if(s[0] == '\0')
    {
        printf("BigInteger Error: empty string\n");
        exit(1);
    }
    if(s[0] == '-')
    {
        ++i;
        N->sign = -1;
    }
    else
    {
        N->sign = 1;
        if(s[0] == '+')
            ++i;
    }
    if(s[i] == '\0')
    {
        printf("BigInteger Error: string with only +/-\n");
        exit(1);
    }
    L = newList();
	while(s[i] != '\0') // fill list
    {
        if(47 < s[i] && s[i] < 58)
        {
            append(L, s[i] - 48);
        }
        else
        {
            printf("BigInteger Error: invalid char in string\n");
            exit(1);
        }
        ++i;
    }
    moveFront(L);
    while(index(L) != -1 && get(L) == 0) // remove all 0's from the front of L
    {
    	delete(L);
    	moveFront(L);
    }
    if(index(L) != -1)
    {
	    moveBack(L);
	    mult = 1;
	    digit = 0;
	    while(index(L) != -1) // make list in N
	    {
	        digit += mult * get(L);
	        movePrev(L);
	        // so yeah it only works for powers of 10, but whatever
	        if(mult * 10 >= BASE || index(L) == -1)
	        {
	            append(N->body, digit);
	            digit = 0;
	            mult = 1;
	   	 	}
	        else
	            mult*= 10;
	    }
	}
	else
		N->sign = 0;
    freeList(&L);
    return(N);
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N)
{
	BigInteger A;
	if(N == NULL)
	{
		printf("BigInteger Error: calling copy() on NULL BigInteger reference\n");
		exit(1);
	}
	A = newBigInteger();
	// have to manually copy the List because of conflicting name Copy
	A->sign = N->sign;
	moveFront(N->body);
	while(index(N->body) != -1)
	{
		append(A->body, get(N->body));
		moveNext(N->body);
	}
	return(A);
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B)
{
	BigInteger N;
	if(S == NULL || A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
		exit(1);
	}
	N = sum(A, B);
	clear(S->body);
	S->sign = N->sign;
	moveFront(N->body);
	while(index(N->body) != -1)
	{
		append(S->body, get(N->body));
		moveNext(N->body);
	}
	freeBigInteger(&N);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B.
BigInteger sum(BigInteger A, BigInteger B)
{
	long digit;
	long carryover;
	BigInteger N;
	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling sum() on NULL BigInteger reference\n");
		exit(1);
	}
	if(A->sign == 0)
	{
		N = copy(B);
		return(N);
	}
	if(B->sign == 0)
	{
		N = copy(A);
		return(N);
	}
	if(A->sign == -1 && B->sign == 1)
	{
		A->sign = 1;
		N = diff(B, A);
		A->sign = -1;
		return(N);
	}
	if(A->sign == 1 && B->sign == -1)
	{
		B->sign = 1;
		N = diff(A, B);
		B->sign = -1;
		return(N);
	}
	N = newBigInteger();
	N->sign = A->sign;

	moveFront(A->body);
	moveFront(B->body);
	carryover = 0;
	while(index(A->body) != -1 && index(B->body) != -1)
	{
		digit = get(A->body) + get(B->body) + carryover;
		carryover = floor(digit / BASE);
		digit = digit % BASE;
		append(N->body, digit);
		moveNext(A->body);
		moveNext(B->body);
	}
	while(index(A->body) != -1)
	{
		digit = get(A->body) + carryover;
		carryover = floor(digit / BASE);
		digit = digit % BASE;
		append(N->body, digit);
		moveNext(A->body);
	}
	while(index(B->body) != -1)
	{
		digit = get(B->body) + carryover;
		carryover = floor(digit / BASE);
		digit = digit % BASE;
		append(N->body, digit);
		moveNext(B->body);
	}
	if(carryover != 0)
		append(N->body, carryover);
	return(N);
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting
// its current state: D = A - B
void subtract(BigInteger D, BigInteger A, BigInteger B)
{
	BigInteger N;
	if(D == NULL || A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
		exit(1);
	}
	N = diff(A, B);
	clear(D->body);
	D->sign = N->sign;
	moveFront(N->body);
	while(index(N->body) != -1)
	{
		append(D->body, get(N->body));
		moveNext(N->body);
	}
	freeBigInteger(&N);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B.
BigInteger diff(BigInteger A, BigInteger B)
{
	long digit;
	long carryover;
	BigInteger N;
	BigInteger top, bottom;
	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
		exit(1);
	}
	if(A->sign == 0)
	{
		N = copy(B);
		return(N);
	}
	if(B->sign == 0)
	{
		N = copy(A);
		negate(N);
		return(N);
	}
	if(A->sign == -1 && B->sign == 1)
	{
		B->sign = -1;
		N = sum(A, B);
		B->sign = 1;
		return(N);
	}
	if(A->sign == 1 && B->sign == -1)
	{
		B->sign = 1;
		N = sum(A, B);
		B->sign = -1;
		return(N);
	}
	if(equals(A, B) == 1)
		return(newBigInteger());

	N = newBigInteger();
	if((compare(A, B)==1 && A->sign==1) || (compare(A, B)==-1 && A->sign==-1))
	{
		top = A;
		bottom = B;
		N->sign = A->sign;
	}
	else
	{
		top = B;
		bottom = A;
		N->sign = A->sign * -1;
	}
	moveFront(top->body);
	moveFront(bottom->body);
	carryover = 0;

	while(index(top->body) != -1 && index(bottom->body) != -1)
	{
		digit = get(top->body) - get(bottom->body) + carryover;
		if(digit < 0)
		{
			digit+= BASE;
			carryover = -1;
		}
		else
			carryover = 0;
		append(N->body, digit);
		moveNext(top->body);
		moveNext(bottom->body);
	}
	while(index(top->body) != -1)
	{
		digit = get(top->body) + carryover;
		if(digit < 0)
		{
			digit+= BASE;
			carryover = -1;
		}
		else
			carryover = 0;
		append(N->body, digit);
		moveNext(top->body);
	}
	
	return(N);
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting
// its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B)
{
	BigInteger N;
	if(P == NULL || A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
		exit(1);
	}
	N = prod(A, B);
	clear(P->body);
	P->sign = N->sign;
	moveFront(N->body);
	while(index(N->body) != -1)
	{
		append(P->body, get(N->body));
		moveNext(N->body);
	}
	freeBigInteger(&N);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B
BigInteger prod(BigInteger A, BigInteger B)
{
	int Ac, Bc, size, i;
	long carryover, digit;
	long* Array;
	BigInteger N;
	if(A == NULL || B == NULL)
	{
		printf("BigInteger Error: calling prod() on NULL BigInteger reference\n");
		exit(1);
	}
	N = newBigInteger();
	
	if(A->sign == 0 || B->sign == 0)
		return(N);
	if(A->sign == B->sign)
		N->sign = 1;
	else
		N->sign = -1;

	Ac = 0;
	size = -1 + length(A->body) + length(B->body);
	Array = calloc(sizeof(long), size);
	moveFront(A->body);
	while(index(A->body) != -1)
	{
		moveFront(B->body);
		Bc = 0;
		while(index(B->body) != -1)
		{
			Array[Ac + Bc]+= get(A->body) * get(B->body);
			moveNext(B->body);
			++Bc;
		}
		moveNext(A->body);
		++Ac;
	}
	carryover = 0;
	for(i = 0; i<size; ++i)
	{
		digit = Array[i] + carryover;
		carryover = floor(digit / BASE);
		digit = digit % BASE;
		append(N->body, digit);
	}
	
	while(carryover != 0)
	{
		append(N->body, carryover % BASE);
		carryover = floor(carryover / BASE);
	}
	free(Array);
	return(N);
}

// Other operations -----------------------------------------------------------

// printBigInteger()
// Prints a base 10 string representation of N to filestream out.
void printBigInteger(FILE* out, BigInteger N)
{
	int i;
	if(N == NULL)
	{
		printf("BigInteger Error: calling printBigInteger() on NULL BigInteger reference\n");
		exit(1);
	}
	if(N->sign == 0)
		fprintf(out, "0\n");
	else
	{
		if(N->sign == -1)
			fprintf(out, "-");
		moveBack(N->body);
		fprintf(out, "%ld", get(N->body));
		movePrev(N->body);
		while(index(N->body) != -1)
		{
			if(get(N->body) < 0)
			{
				printf("BigInteger Error: overflow occurred: \n");
				exit(1);
			}
			if(get(N->body) == 0)
			{
				for(i=0; i<POWER - 1; i++)
				{
					fprintf(out, "0");
				}
			}
			else
			{
				// prints 0's infront for formatting 
				for(i=10; BASE > get(N->body) * i; i*= 10)
				{
					fprintf(out, "0");
				}
			}
			fprintf(out, "%ld", get(N->body));
			movePrev(N->body);
		}
		fprintf(out, "\n");
	}
}











