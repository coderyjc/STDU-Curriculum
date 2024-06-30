//#include<stdio.h>
//#define N 10
//void Transpose(int *a, int n);
//void Swap(int *x,int *y);
//
//int main ()
//{
//	int a[N][N];
//	int n;
//	int i, j;
//	printf("Enter the row : ");
//	scanf("%d",&n);
//	printf("Initialize the array : \n");
//	for(i = 0;i < n;i ++)
//		for(j = 0;j < n;j ++)
//			scanf("%d",&a[i][j]);
//
//	Transpose(&a[0][0],n);
//}
//
//void Transpose(int *p, int n)
//{
//	int t;
//	for(int i = 0;i < n;i++)
//		for(int j = i+1;j < n;j++)
//			Swap(&p[i*N+j] ,&p[j*N+i]);
//	printf("\n");
//	for(int i = 0;i < n;i++)
//	{
//		for(int j = 0;j < n;j++)
//			printf("%3d",*(p+i*N+j));
//		printf("\n");
//	}
//}
//
//void Swap(int *x,int *y)
//{
//	int t;
//	t = *x;
//	*x = *y;
//	*y = t;
//}