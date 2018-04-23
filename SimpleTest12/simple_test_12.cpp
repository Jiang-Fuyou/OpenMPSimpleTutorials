#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

const int g_ncore = omp_get_num_procs(); 
//获取执行核的数量

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
	if ( tn < 1 )
	{
		tn = 1;
	}
	return tn;
}



/** 矩阵串行乘法函数
	@param    int *a - 指向要相乘的第个矩阵的指针
	@param    int row_a - 矩阵a 的行数
	@param    int col_a - 矩阵a 的列数
	@param    int *b - 指向要相乘的第个矩阵的指针
	@param    int row_b - 矩阵b 的行数
	@param    int col_b - 矩阵 b 的列数
	@param    int *c - 计算结果的矩阵的指针
	@param    int c_size - 矩阵c 的空间大小（总元素个数）
	@return    void - 无
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