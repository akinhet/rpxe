#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 256

typedef struct {
	long top;
	double data[MAXSIZE];
} Stack;

double isempty(Stack *stack);
double isfull(Stack *stack);
double pop(Stack *stack);
void push(Stack *stack, double value);
