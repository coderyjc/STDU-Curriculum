#include<stdio.h>

// 进程数量
#define M 5
// 资源数量
#define N 3

// 系统可用的资源数
int AVAILABLE[N] = {18, 6, 22};
// M 个进程对 N 类资源最大资源需求量
int MAX[M][N] = { {5, 5, 10},{5, 3, 6},{4,0,11},{4,2,5},{4,2,4} };
// M 个进程已经得到 N 类资源的资源量
int ALLOCATION[M][N] ={ {3,2,3},{4,0,3},{4,0,5},{2,0,4},{3,1,4} };
// M 个进程还需要 N 类资源的资源量
int NEED[M][N] = {};




int main(){


  return 0;
}