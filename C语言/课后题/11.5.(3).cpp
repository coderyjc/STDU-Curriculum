//#include<stdio.h>
//#define N 10
//#define M 10
//
//void Transpose(int *a, int *at, int m, int n);
//
//int main ()
//{
//	int n, m;
//	int a[M][N];
//	int b[N][M];
//	printf("Enter the row(n*m): ");
//	scanf("%d%*c%d",&n,&m);
//	printf("Initialize the array(n*m): \n");
//	for(int i = 0;i < n;i++)
//		for(int j = 0;j < m;j++)
//			scanf("%d",&a[i][j]);
//	Transpose(*a,*b,n,m);
//	return 0;
//}
//
//void Transpose(int *a, int *at, int m, int n)
//{
//	for(int i = 0;i < N;i ++)
//		for(int j = 0;j < M;j++)
//			at[j*N+i] = a[i*N+j];
//
//	printf("After transfer : \n");
//
//	for(int i = 0;i < n;i++)
//	{
//		for(int j = 0;j < m;j++)
//			printf("%3d",at[i*N+j]);
//		printf("\n");
//	}
//}