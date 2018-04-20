#include <omp.h>
#include <stdio.h>

int main()
{

#pragma omp parallel
	{
		printf("1. Hello, world!\n");
	}

	printf("\n");

#pragma omp parallel num_threads(4)
	{
		printf("2. Hello, world!\n");
	}

	printf("\n");

#pragma omp for 
	for (int i = 0; i < 4; i++) {
		printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
	}

	printf("\n");

#pragma omp parallel for 
	for (int i = 0; i < 4; i++) {
		printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
	}

#pragma omp parallel 
	{
#pragma omp for
		for (int i = 0; i < 4; i++) {
			printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
		}
#pragma omp for
		for (int i = 0; i < 8; i++) {
			printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
		}
#pragma omp for
		for (int i = 0; i < 12; i++) {
			printf("i = %d, thread id = %d\n", i, omp_get_thread_num());
		}
	}

	printf("\n");

#pragma omp parallel sections
	{
#pragma omp section
		printf("3 + 2 = %d, thread id = %d\n", 3 + 2, omp_get_thread_num());
#pragma omp section
		printf("3 - 2 = %d, thread id = %d\n", 3 - 2, omp_get_thread_num());
#pragma omp section
		printf("3 * 2 = %d, thread id = %d\n", 3 * 2, omp_get_thread_num());
#pragma omp section
		printf("3 / 2 = %d, thread id = %d\n", 3 / 2, omp_get_thread_num());
	}

#pragma omp parallel
	{
#pragma omp sections
	{
#pragma omp section
		printf("3 + 2 = %d, thread id = %d\n", 3 + 2, omp_get_thread_num());
#pragma omp section
		printf("3 - 2 = %d, thread id = %d\n", 3 - 2, omp_get_thread_num());
	}
#pragma omp sections
	{
#pragma omp section
		printf("3 * 2 = %d, thread id = %d\n", 3 * 2, omp_get_thread_num());
#pragma omp section
		printf("3 / 2 = %d, thread id = %d\n", 3 / 2, omp_get_thread_num());
	}
	}

	return 0;
}