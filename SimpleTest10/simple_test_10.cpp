#include <Windows.h>
#include <time.h>
#include <process.h>
#include <omp.h>	
#include <stdio.h>

const int N = 10000000;

void TestAtomic()
{
	clock_t t1, t2;
	volatile LONG a = 0;

	t1 = clock();
	for (int i = 0; i < N; i++) {
		InterlockedIncrement(&a);
	}
	t2 = clock();
	printf("SingleThread, InterlockedIncrement 10000000: a = %ld, time = %ld\n",
		   a, t2 - t1);

	a = 0;
	t1 = clock();
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
//#pragma omp atomic
//		a++;
		InterlockedIncrement(&a);
	}
	t2 = clock();
	printf("MultiThread, InterlockedIncrement 10000000: a = %ld, time = %ld\n",
		   a, t2 - t1);
}

void TestOMPLock()
{
	clock_t t1, t2;
	volatile LONG a = 0;
	omp_lock_t mylock;

	omp_init_lock(&mylock); 
	t1 = clock();
	for (int i = 0; i < N; i++) {
		omp_set_lock(&mylock); 
		a += 1;
		omp_unset_lock(&mylock);
	}
	t2 = clock();
	printf("SingleThread,omp_lock 10000000:a = %ld, time = %ld\n", 
		   a, t2 - t1); t1 = clock();

	a = 0;
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		omp_set_lock(&mylock); 
		a += 1;
		omp_unset_lock(&mylock);
	}
	t2 = clock();
	printf("MultiThread,omp_lock 10000000:a = %ld, time = %ld\n", 
		   a, t2 - t1);

	omp_destroy_lock(&mylock);
}

void TestCriticalSection()
{
	clock_t t1, t2;
	volatile LONG a = 0; 
	CRITICAL_SECTION cs;

	InitializeCriticalSection(&cs);
	t1 = clock();
	for (int i = 0; i < N; i++) {
		EnterCriticalSection(&cs); 
		a += 1;
		LeaveCriticalSection(&cs);
	}
	t2 = clock();
	printf("SingleThread, Critical_Section 2,000,000:a = %ld, time = %ld\n", 
		   a, t2 - t1); t1 = clock();

	a = 0;
#pragma omp parallel for
	for (int i = 0; i < N; i++) {
		EnterCriticalSection(&cs); 
		a += 1;
		LeaveCriticalSection(&cs);
	}
	t2 = clock();

	printf("MultiThread, Critical_Section, 2,000,000:a = %ld, time = %ld\n", 
		   a, t2 - t1); DeleteCriticalSection(&cs);
}


int main()
{
	TestAtomic();

	TestOMPLock();

	TestCriticalSection();

	return 0;
}