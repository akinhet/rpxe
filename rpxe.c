#include "stack.h"
#include <math.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define VERSION "2.1"

#define PROMPT "> "

#define HELP_STRING \
"Constants\n\
	e	pi\n\
\n\
Functions\n\
	root	sin	cos	tan\n\
	ln	log	ceil	floor\n\
	round	exp	exp2	sqrt\n\
\n\
Operators\n\
	+ - * / ^ %\n"

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
		else if (!strcmp(token, "sqrt"))
			push(&stack, sqrt(pop(&stack)));
		else if (!strcmp(token, "sin"))
			push(&stack, sin(degtorad(pop(&stack))));
		else if (!strcmp(token, "cos"))
			push(&stack, cos(degtorad(pop(&stack))));
		else if (!strcmp(token, "tan") || !strcmp(token, "tg"))
			push(&stack, tan(degtorad(pop(&stack))));
		else if (!strcmp(token, "ln"))
			push(&stack, log(pop(&stack)));
		else if (!strcmp(token, "log"))
			push(&stack, log(pop(&stack))/log(pop(&stack)));
		else if (!strcmp(token, "ceil"))
			push(&stack, ceil(pop(&stack)));
		else if (!strcmp(token, "floor"))
			push(&stack, floor(pop(&stack)));
		else if (!strcmp(token, "round"))
			push(&stack, round(pop(&stack)));
		else if (!strcmp(token, "exp"))
			push(&stack, exp(pop(&stack)));
		else if (!strcmp(token, "exp2"))
			push(&stack, exp2(pop(&stack)));
		else if (!strcmp(token, "e"))
			push(&stack, M_E);
		else if (!strcmp(token, "pi"))
			push(&stack, M_PI);
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

	using_history();

	while(1) {
		line = readline(PROMPT);
		if (line == NULL) {
			free(line);
			return;
		} else if (strlen(line) == 0)
			continue;
		else if (!strcmp(line, "?") || !strcmp(line, "help"))
			printf("%s", HELP_STRING);
		else {
			add_history(line);
			evaluate(line);
		}
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
	} else {
		char input[1024];
		for (int i = 1; i < argc; i++) {
			strcpy(input, strcat(input, argv[i]));
			strcpy(input, strcat(input, " "));
		}

		evaluate(input);
	}

	return(0);
}
