#include <stdio.h>
#include <omp.h>

int main()
{
#pragma omp parallel for schedule(static, 2) //num_threads(2)
	for (int i = 0; i < 16; i++) {
		printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
	}

	printf("\n");

#pragma omp parallel for schedule(dynamic) //num_threads(2)
	for (int i = 0; i < 16; i++) {
		printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
	}

	printf("\n");

#pragma omp parallel for schedule(guided) //num_threads(2)
	for (int i = 0; i < 16; i++) {
		printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
	}

	return 0;
}