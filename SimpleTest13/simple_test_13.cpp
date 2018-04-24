#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel
	{
#pragma omp for nowait
		for (int i = 0; i < 10; i++) {
			printf("1.%d\n", i);
		}
#pragma omp for
		for (int i = 0; i < 10; i++) {
			printf("2.%d\n", i);
		}
	}

#pragma omp parallel
	{
#pragma omp master
		{
			for (int i = 0; i < 10; i++) {
				printf("3.%d\n", i);
			}
		}

		printf("4\n");
	}

	return 0;
}