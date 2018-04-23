#include <stdio.h>
#include <omp.h>

#define COUNT 10

int A = 100;
#pragma omp threadprivate(A)

int main(int argc, char * argv[])
{
	/* First Test. */
	
	int sum = 0, i = 0;
#pragma omp parallel for shared(sum)
	for (i = 0; i < COUNT; i++) {
		sum = sum + i;
	}
	printf("sum: %d\n", sum);

	sum = 0, i = 0;
#pragma omp parallel for shared(sum, i)
	for (i = 0; i < COUNT; i++) {
		sum = sum + i;
	}
	printf("i: %d, sum: %d\n", i, sum);

	sum = 0, i = 0;
#pragma omp parallel shared(sum) private(i)
	for (i = 0; i < COUNT; i++) {
//#pragma omp atomic
		sum += i;
	}
	printf("i: %d, sum: %d\n", i, sum);
	
	/* First Test. */

	/* Second Test. */
#pragma omp parallel for
	for (int i = 0; i < 10; i++) {
		A++;
		printf("Thread id: %d, i: %d, A: %d\n",
			   omp_get_thread_num(), i, A);
	}

	printf("Global A: %d\n", A);

#pragma omp parallel for copyin(A)
	for (int i = 0; i < 10; i++) {
		A++;
		printf("Thread id: %d, i: %d, A: %d\n",
			   omp_get_thread_num(), i, A);
	}

	printf("Global A: %d\n", A);
	
	/* Second Test. */

	/* Third Test. */
#pragma omp parallel 
	{
		printf("Initial A = %d\n", A);
		A = omp_get_thread_num();
	}

	printf("Global A: %d\n", A);

#pragma omp parallel copyin(A)
	{
		printf("Initial A = %d\n", A);
		A = omp_get_thread_num();
	}

	printf("Global A: %d\n", A);

#pragma omp parallel 
	{
		printf("Initial A = %d\n", A);
		A = omp_get_thread_num();
	}

	printf("Global A: %d\n", A);

	/* Third Test. */

	/* 4th Test. */
	A = 100;
	int B = 100;
	int C = 1000;
#pragma omp parallel firstprivate(B) copyin(A)	// copyin(A) can be ignored!
	{
		printf("1. Thread id %d, A: %d\n", omp_get_thread_num(), A);
		printf("1. Thread id %d, B: %d\n", omp_get_thread_num(), B);
#pragma omp single copyprivate(A) copyprivate(B) // copyprivate(C)
		// C is shared, cannot use copyprivate!
		{
			A = 10;
			B = 20;
			printf("2. Thread id %d, A: %d\n", omp_get_thread_num(), A);
			printf("2. Thread id %d, B: %d\n", omp_get_thread_num(), B);
		}
		printf("3. Thread id %d, A: %d\n", omp_get_thread_num(), A);
		printf("3. Thread id %d, B: %d\n", omp_get_thread_num(), B);
	}

	printf("Global A = %d\n", A);
	printf("Global B = %d\n", B);


	return 0;
}