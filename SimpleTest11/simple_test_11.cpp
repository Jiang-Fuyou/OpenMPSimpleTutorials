#include <stdio.h>
#include <omp.h>

//获取执行核的数量
const int g_ncore = omp_get_num_procs(); 

/** 计算循环迭代需要的线程数量
	根据循环迭代次数和CPU 核数及一个线程最少需要的循环迭代次数来计算出需要的线程数量，计算出的最
		大线程数量不超过CPU 核数
	@param    int n - 循环迭代次数
	@param    int min_n - 单个线程需要的最少迭代次数
	@return int - 线程数量
*/
int dtn(int n, int min_n)
{
	int max_tn = n / min_n;
	int tn = max_tn > g_ncore ? g_ncore : max_tn; //tn 表示要设置的线程数量 
	if (tn < 1) {
		tn = 1;
	}
	return tn;
}


int main()
{
	const int n = 128;
	const int MIN_ITERATOR_NUM = 4;
	int ncore = omp_get_num_procs();
	int max_tn = n / MIN_ITERATOR_NUM;
	int tn = max_tn > 2 * ncore ? 2 * ncore : max_tn;

	printf("n: %d\n", n);
	printf("MIN_ITERATOR_NUM: %d\n", MIN_ITERATOR_NUM);
	printf("ncore: %d\n", ncore);
	printf("max_tn: %d\n", max_tn);
	printf("tn: %d\n", tn);

//#pragma omp parallel for if(tn > 1) num_threads(tn)
#pragma omp parallel for num_threads(dtn(n, MIN_ITERATOR_NUM))
	for (int i = 0; i < n; i++) {
		//printf("Thread id: %d\n", omp_get_thread_num());
	}

	return 0;
}