#include "string.h"
#include <stdio.h>
#include <stdlib.h>

#define M 5
#define N 3
#define FALSE 0
#define TRUE 1

/*M 个进程对 N 类资源最大资源需求量*/
int MAX[M][N] = { {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };
/*系统可用资源数*/
int AVAILABLE[N] = { 10,5,7 };
/*M 个进程对 N 类资源最大资源需求量*/
int ALLOCATION[M][N] = { {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0} };
/*M 个进程已经得到 N 类资源的资源量 */
int NEED[M][N] = { {7,5,3},{3,2,2},{9,0,2},{2,2,2},{4,3,3} };
/*M 个进程还需要 N 类资源的资源量*/
int Request[N] = { 0,0,0 };//初始化需要申请的资源数目

/**
 * 展示当前的数据
 * - 系统可用的资源
 * - 各个进程还需要的资源量
 * - 各个进程已经得到的资源
 */
void showdata()
{
	int i, j;
	printf("系统可用的资源数为:\n ");
	for (j = 0; j < N; j++) {
		printf(" 资源%d : %d", j, AVAILABLE[j]);
	}
	printf("\n各进程还需要的资源量:\n");
	for (i = 0; i < M; i++)
	{
		printf(" 进程%d: ", i);
		for (j = 0; j < N; j++) {
			printf("资源 %d : %d ", j, NEED[i][j]);
		}
		printf("\n");
	}
	printf("各进程已经得到的资源量: \n");
	for (i = 0; i < M; i++)
	{
		printf(" 进程%d", i);
		for (j = 0; j < N; j++) {
			printf("资源%d : %d", j, ALLOCATION[i][j]);
		}
		printf("\n");
	}
}

/**
 * 
 */
void changdata(int k)
{
	int j;
	for (j = 0; j < N; j++)//修改数据结构的值
	{
		AVAILABLE[j] = AVAILABLE[j] - Request[j];
		ALLOCATION[k][j] = ALLOCATION[k][j] + Request[j];
		NEED[k][j] = NEED[k][j] - Request[j];
	}
};


void rstordata(int k)
{
	int j;
	for (j = 0; j < N; j++)//修改数据结构的值
	{
		AVAILABLE[j] = AVAILABLE[j] + Request[j];
		ALLOCATION[k][j] = ALLOCATION[k][j] - Request[j];
		NEED[k][j] = NEED[k][j] + Request[j];
	}
};


int chkerr(int s)
{
	int WORK, FINISH[M], temp[M];
	int i, j, k = 0;
	for (i = 0; i < M; i++)FINISH[i] = FALSE;
  //用安全性检查算法判断系统是否安全（即是否为 true）
	for (j = 0; j < N; j++)	{
		WORK = AVAILABLE[j];
		i = s;
		while (i < M) {
			if (FINISH[i] == FALSE && NEED[i][j] <= WORK) {
				WORK = WORK + ALLOCATION[i][j];
				FINISH[i] = TRUE;
				temp[k] = i;
				k++;
				i = 0;
			} else {
				i++;
			}
		}
		for (i = 0; i < M; i++)
			if (FINISH[i] == FALSE) {
				printf("\n");
				printf("系统不安全!!! 本次资源申请不成功!!!\n");
				printf("\n");
				return 1;
			}
	}
	printf("\n经安全性检查，系统安全，本次分配成功。\n\n 本次安全序列：");
	for (i = 0; i < M; i++) {
		printf("进程%d->", temp[i]);
	}
	printf("\n");
	return 0;
}


void main() {
	int i = 0, j = 0;
	char flag = 'Y';
	showdata();
	while (flag == 'Y' || flag == 'y')
	{
		i = -1;
		while (i < 0 || i >= M)
		{
			printf("请输入需申请资源的进程号（从 0 到 %d，否则重输入!）:", M - 1);
			scanf("%d", &i);
			if (i < 0 || i >= M) printf("输入的进程号不存在，重新输入!\n");
		}
		printf("请输入进程%d申请的资源数\n", i);
		for (j = 0; j < N; j++)
		{
			printf("资源%d: ", j);
			scanf("%d", &Request[j]);
			if (Request[j] > NEED[i][j])//第一步判断申请的资源数是否大于需要的资源数
			{
				printf("进程%d申请的资源数大于进程%d", i, i);
				printf("还需要%d类资源的资源量!申请不合理，出错!请重新选择!", j);
				flag = 'N';
				break;
			}
			else
			{
				if (Request[j] > AVAILABLE[j])//第二步判断申请的资源数是否大于可用资源数
				{
					printf("进程 %d 申请的资源数大于系统可用", i);
					printf("%d类资源的资源量!申请不合理，出错!请重新选择!\n", j);
					flag = 'N';
					break;
				}
			}
		}
		if (flag == 'Y' || flag == 'y')
		{
			changdata(i);
			if (chkerr(i))
			{
				rstordata(i);
				showdata();
			}
			else
				showdata();
		}
		else
			showdata();
		printf("\n");
		scanf("%c", &flag);
	}
}