#include "omp.h"
#include <stdio.h>
#include <time.h>

int counter = 0;

#pragma omp threadprivate(counter) 
int increment_counter()
{
	counter++;
	return counter;
}

int increment_counter2()
{
	static int counter = 0;
#pragma omp threadprivate(counter) 
	counter++;

	return counter;
}

int main()
{
	printf("sizeof int: %d\n", sizeof(int));
	printf("sizeof long: %d\n", sizeof(long));
	printf("sizeof long int: %d\n", sizeof(long int));
	printf("sizeof long long: %d\n", sizeof(long long));

	/*
	int c1 = counter;
	printf("counter is %d\n", c1);

#pragma omp parallel for num_threads(4)
	for (int i = 0; i < 10; i++) {
		int c2 = increment_counter();
		int c3 = increment_counter2();

		printf("counter is %d, thread id is %d\n", c2, omp_get_thread_num());
		printf("counter is %d, thread id is %d\n", c3, omp_get_thread_num());
	}
	*/

	/*
	int m = 0;
#pragma omp parallel for num_threads(4)
	for (int i = 0; i < 4; i++) {
		printf("m = %d, thread id %d.\n", m, omp_get_thread_num());
	}
	*/

	/*
	//int m;
#pragma omp parallel default(none) shared(m) num_threads(4)
	{
#pragma omp for
		for (int i = 0; i < 4; i++) {
			printf("m = %d, thread id %d.\n", m, omp_get_thread_num());
		}
	}
	*/


	long long sum1 = 0, sum2 = 0;
	clock_t ts, te;
	ts = clock();
#pragma omp parallel for reduction(+: sum1, sum2) num_threads(4)
	for (int i = 0; i < 10000000; i++) {
		sum1 += i;
		sum2 += i - 1;
	}
	te = clock();

	printf("1. Duration: %lf s, sum is %I64d\n", 
		   (double)(te - ts) / CLOCKS_PER_SEC, sum1);

	sum1 = 0, sum2 = 0;
	ts = clock();
#pragma omp parallel for num_threads(4)
	for (int i = 0; i < 10000000; i++) {
#pragma omp atomic
		sum1 += i;
#pragma omp atomic
		sum2 += i - 1;
	}
	te = clock();

	printf("1. Duration: %lf s, sum is %I64d\n", 
		   (double)(te - ts) / CLOCKS_PER_SEC, sum1);

	int prod = 1;
#pragma omp parallel for reduction(*: prod) num_threads(10)
	for (int i = 1; i <= 10; i++) {
		prod *= i;
	}

	printf("Production: %d\n", prod);

	return 0;
}