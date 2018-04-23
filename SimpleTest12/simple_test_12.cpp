#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

const int g_ncore = omp_get_num_procs(); 
//��ȡִ�к˵�����

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
	if ( tn < 1 )
	{
		tn = 1;
	}
	return tn;
}



/** �����г˷�����
	@param    int *a - ָ��Ҫ��˵ĵڸ������ָ��
	@param    int row_a - ����a ������
	@param    int col_a - ����a ������
	@param    int *b - ָ��Ҫ��˵ĵڸ������ָ��
	@param    int row_b - ����b ������
	@param    int col_b - ���� b ������
	@param    int *c - �������ľ����ָ��
	@param    int c_size - ����c �Ŀռ��С����Ԫ�ظ�����
	@return    void - ��
*/
void Matrix_Multiply(int *a, int row_a, int col_a,
					 int *b, int row_b, int col_b, 
					 int *c, int c_size)
{
	if (col_a != row_b || c_size < row_a * col_b) {
		return;
	}

	int i, j, k;
	//#pragma omp for private(i, j, k) 
	for ( i = 0; i < row_a; i++ )
	{
		int row_i = i * col_a; 
		int row_c = i * col_b;
		for (j = 0; j < col_b; j++) {
			c[row_c + j] = 0;
			for (k = 0; k < row_b; k++) {
				c[row_c + j] += a[row_i + k] * b[k * col_b + j];
			}
		}
	}
}


void Parallel_Matrix_Multiply(int *a, int row_a, int col_a, 
							  int *b, int row_b, int col_b, 
							  int *c, int c_size)
{
	if (col_a != row_b) {
		return;
	}

	int i, j, k; 
	int index;
	int border = row_a * col_b;
	i = 0;
	j = 0;
#pragma omp parallel private(i,j,k) num_threads(dtn(border, 1)) 
	for (index = 0; index < border; index++) {
		i = index / col_b;
		j = index % col_b;

		int row_i = i * col_a; int row_c = i * col_b;
		c[row_c + j] = 0;
		for (k = 0; k < row_b; k++) {
			c[row_c + j] += a[row_i + k] * b[k*col_b + j];
		}
	}
}


int main()
{
	return 0;
}