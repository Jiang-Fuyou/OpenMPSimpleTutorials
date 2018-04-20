#include <stdio.h>
#include "omp.h"

int main()
{
	int k = 100;

	/*
#pragma omp parallel for private(k)
	for (k = 0; k < 4; k++) {
		printf("k = %d, thread id = %d\n", k, omp_get_thread_num());
	}
	*/

	/*
#pragma omp parallel for firstprivate(k)
	for (int i = 0; i < 4; i++) {
		k += i;
		printf("k = %d, thread id = %d\n", k, omp_get_thread_num());
	}
	*/

#pragma omp parallel for firstprivate(k) lastprivate(k)
	for (int i = 0; i < 4; i++) {
		k += i;
		printf("k = %d, thread id = %d\n", k, omp_get_thread_num());
	}

	printf("last k = %d\n", k);
}