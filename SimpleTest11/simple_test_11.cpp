#include <stdio.h>
#include <omp.h>

//��ȡִ�к˵�����
const int g_ncore = omp_get_num_procs(); 

/** ����ѭ��������Ҫ���߳�����
	����ѭ������������CPU ������һ���߳�������Ҫ��ѭ�������������������Ҫ���߳����������������
		���߳�����������CPU ����
	@param    int n - ѭ����������
	@param    int min_n - �����߳���Ҫ�����ٵ�������
	@return int - �߳�����
*/
int dtn(int n, int min_n)
{
	int max_tn = n / min_n;
	int tn = max_tn > g_ncore ? g_ncore : max_tn; //tn ��ʾҪ���õ��߳����� 
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