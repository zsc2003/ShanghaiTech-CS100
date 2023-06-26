#include "memcheck.h"

// Some code that may have memory problems:
int main(void) {
	int **p = malloc(sizeof(int *) * 5);
	for (int i = 0; i != 5; ++i)
	p[i] = malloc(sizeof(int) * 3);
	// do something
	// ...
	// ...
	free(p[2] + 3);
	free(p);
	return 0;
}
