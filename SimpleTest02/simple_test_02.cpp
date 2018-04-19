#include <stdio.h>
#include <time.h>

void test()
{
	int a = 0;
	clock_t t1 = clock();
	for (int i = 0; i < 100000000; i++) {
		a = i + 1;
	}
	clock_t t2 = clock();

	printf("Time is %d\n", t2 - t1);
}

int main()
{
	clock_t t1 = clock();
#pragma omp parallel for
	for (int i = 0; i < 2; i++) {
		test();
	}
	clock_t t2 = clock();

	printf("Total time is %d\n", t2 - t1);

	test();

	return 0;
}