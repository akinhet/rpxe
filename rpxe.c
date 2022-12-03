#include "stack.h"
#include <math.h>
#include <string.h>
#include <readline/readline.h>

#define VERSION "2.0"

#define PROMPT "> "

#define usage() (printf("usage: %s <expression>\n       %s [-h|--help]\n", argv[0], argv[0]))
#define version() (printf("%s-%s\n", argv[0], VERSION))
#define degtorad(x) (x / 180 * M_PI)


void evaluate(char *v)
{
	double a,b,num = 0;
	Stack stack = {-1};

	char *endptr = NULL,
		 *token = NULL;

	token = strtok(v, " ");

	do {
		if (!strcmp(token, "+"))
			push(&stack, pop(&stack) + pop(&stack));
		else if (!strcmp(token, "-")) {
			b = pop(&stack);
			a = pop(&stack);
			push(&stack, a - b);
		} else if (!strcmp(token, "*")) {
			push(&stack, pop(&stack) * pop(&stack));
		} else if (!strcmp(token, "/")) {
			b = pop(&stack);
			a = pop(&stack);
			push(&stack, a / b);
		} else if (!strcmp(token, "^"))
			push(&stack, pow(pop(&stack), pop(&stack)));
		else if (!strcmp(token, "%"))
			push(&stack, fmod(pop(&stack), pop(&stack)));
		else if (!strcmp(token, "root"))
			push(&stack, pow(pop(&stack), 1/pop(&stack)));
		else if (!strcmp(token, "sin"))
			push(&stack, sin(degtorad(pop(&stack))));
		else if (!strcmp(token, "cos"))
			push(&stack, cos(degtorad(pop(&stack))));
		else if (!strcmp(token, "tan") || !strcmp(token, "tg"))
			push(&stack, tan(degtorad(pop(&stack))));
		else {
				num = strtod(token, &endptr);
				if (!strcmp(token, endptr)) {
					fprintf(stderr, "Unknown value or operation: %s\n", token);
					return;
				} else {
					push(&stack, num); 
				}
		}
	} while ((token = strtok(NULL, " ")) != NULL);

	printf("%g\n", pop(&stack));
}


void interactive()
{
	char *line = NULL;

	while(1) {
		line = readline(PROMPT);
		if (line == NULL) {
			free(line);
			return;
		} else if (strlen(line) == 0)
			continue;
		else
			evaluate(line);
	}
}


int main(int argc, const char *argv[])
{
	if (argc == 1) {
		interactive();
		return(0);
	}

	if (!strcmp(argv[1], "--help") || !strcmp(argv[1], "-h")) {
		usage();
		return(0);
	} else if (!strcmp(argv[1], "--version") || !strcmp(argv[1], "-v")) {
		version();
		return(0);
	} else if (!strcmp(argv[1], "--interactive") || !strcmp(argv[1], "-i")){
		interactive();
	}

	return(0);
}
