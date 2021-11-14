#include "stack.h"

double isempty(Stack *stack)
{
	return stack->top < 0 ? 1 : 0;
}


double isfull(Stack *stack)
{
	return stack->top > MAXSIZE - 2 ? 1 : 0;
}


double pop(Stack *stack)
{
	if (!isempty(stack))
		return stack->data[stack->top--];
	else {
		fprintf(stderr, "Stack is empty! Cannot pop. Exiting...\n");
		exit(-1);		
	}
}


void push(Stack *stack, double value)
{
	if (!isfull(stack))
		stack->data[++stack->top] = value;
	else {
		fprintf(stderr, "Stack is full! Cannot push. Exiting...\n");
		exit(-1);
	}
}
