#include <stdio.h>
#include <omp.h>

int counter = 0;
#pragma omp threadprivate(counter)

int increament_counter()
{
	counter++;
	return counter;
}

int main()
{
	int i;

#pragma omp parallel for
	for (int i = 0; i < 2; i++) {
		counter++;
		printf("Thread id: %d, i: %d, counter: %d\n", 
			   omp_get_thread_num(), i, counter);
	}

#pragma omp parallel sections copyin(counter)
	{
#pragma omp section
	{
		int count1;
		for (int i = 0; i < 10; i++) {
			count1 = increament_counter();
		}
		printf("Count1: %d\n", count1);
	}
#pragma omp section
	{
		int count2;
		for (int i = 0; i < 20; i++) {
			count2 = increament_counter();
		}
		printf("Count2: %d\n", count2);
	}
	}

	return 0;
}