#include <stdio.h>
#include <omp.h>

int counter = 0;
#pragma omp threadprivate(counter)

int increment_counter()
{
	return ++counter;
}

int main()
{
#pragma omp parallel
{
	int count;
	printf("Thread id: %d, counter: %d\n", omp_get_thread_num(), counter);
#pragma omp barrier
	counter = 50;
	/*
#pragma omp single copyprivate(counter)
	{
		counter = 50;
	}
	*/
	count = increment_counter();
	printf("Thread id: %d, count: %d\n", omp_get_thread_num(), count);
#pragma omp barrier
	printf("Thread id: %d, counter: %d\n", omp_get_thread_num(), counter);
}
	

return 0;
}