//#include<stdio.h>
//#define N 10
//
//void Transpose(int a[N][N], int n);
//
//int main ()
//{
//	int n;
//	int a[N][N];
//	printf("Enter the row : ");
//	scanf("%d",&n);
//	printf("Initialize the array(n*n): \n");
//	for(int i = 0;i < n;i++)
//		for(int j = 0;j < n;j++)
//			scanf("%d",&a[i][j]);
//	Transpose(a,n);
//	return 0;
//}
//void Transpose(int a[N][N], int n)
//{
//	int t;
//	for(int i = 0;i < n;i++)
//		for(int j = i+1;j < n;j++)
//		{
//			t = a[i][j];
//			a[i][j] = a[j][i];
//			a[j][i] = t;
//		}
//		for(int i = 0;i < n;i++)
//		{
//			for(int j = 0;j < n;j++)
//				printf("%3d",a[i][j]);
//			printf("\n");
//		}
//
//}
