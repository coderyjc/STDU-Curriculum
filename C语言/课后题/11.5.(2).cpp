//#include<stdio.h>
//#define N 10
//#define M 10
//
//void Transpose(int (*a)[N],int (*at)[M], int n, int m);
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
//	Transpose(a,b,n,m);
//	return 0;
//}
//
//void Transpose(int (*a)[N],int (*at)[M], int n, int m)
//{
//	int t;
//	for(int i = 0;i < m;i++)
//		for(int j = 0;j < n;j++)
//			*(at[i]+j) = *(a[j]+i);
//	printf("The result is : \n");
//		for(int i = 0;i < m;i++)
//		{
//			for(int j = 0;j < n;j++)
//				printf("%3d",*(at[i]+j));
//			printf("\n");
//		}
//
//
//}