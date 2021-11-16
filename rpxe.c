#include "stack.h"
#include <math.h>
#include <string.h>

#define VERSION "1.0"

#define usage() (printf("usage: %s <expression>\n       %s [-h|--help]\n", argv[0], argv[0]))
#define version() (printf("%s-%s\n", argv[0], VERSION))
#define degtorad(x) (x / 180 * M_PI)


int main(int argc, const char *argv[])
{
	double a,b,num = 0;
	Stack stack = {-1};

	char *endptr = NULL;

	if (argc < 2) {
		usage();
		exit(1);
	}

	for (int i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "--help") || !strcmp(argv[i], "-h")) {
			usage();
			return(0);
		} else if (!strcmp(argv[i], "--version") || !strcmp(argv[i], "-v")) {
			version();
			return(0);
		} else if (!strcmp(argv[i], "+"))
			push(&stack, pop(&stack) + pop(&stack));
		else if (!strcmp(argv[i], "-")) {
			b = pop(&stack);
			a = pop(&stack);
			push(&stack, a - b);
		} else if (!strcmp(argv[i], "*")) {
			push(&stack, pop(&stack) * pop(&stack));
		} else if (!strcmp(argv[i], "/")) {
			b = pop(&stack);
			a = pop(&stack);
			push(&stack, a / b);
		} else if (!strcmp(argv[i], "^"))
			push(&stack, pow(pop(&stack), pop(&stack)));
		else if (!strcmp(argv[i], "root"))
			push(&stack, pow(pop(&stack), 1/pop(&stack)));
		else if (!strcmp(argv[i], "sin"))
			push(&stack, sin(degtorad(pop(&stack))));
		else if (!strcmp(argv[i], "cos"))
			push(&stack, cos(degtorad(pop(&stack))));
		else if (!strcmp(argv[i], "tan") || !strcmp(argv[i], "tg"))
			push(&stack, tan(degtorad(pop(&stack))));
		else {
				num = strtod(argv[i], &endptr);
				if (!strcmp(argv[i], endptr)) {
					fprintf(stderr, "Unknown value or operation: %s\n", argv[i]);
					usage();
					exit(2);
				} else {
					push(&stack, num); 
				}
		}
	}

	printf("%f\n", pop(&stack));

	return(0);
}
