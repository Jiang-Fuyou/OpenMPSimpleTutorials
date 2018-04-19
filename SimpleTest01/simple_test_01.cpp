#include <stdio.h>

int main()
{
#pragma omp parallel for
	for (int i = 0; i < 10; i++) {
		printf("i = %d\n", i);
	}

	return 0;
}