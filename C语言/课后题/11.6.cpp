//#include<stdio.h>
//#define N 10
//
//void InputArray(int* p, int m, int n);
//void FindMax(int* p, int m, int n, int *pRow, int *pCol);
//
//int main ()
//{
//	int a[N][N]={};
//	int m, n;
//	int pRow = 0,pCol = 0;
//	printf("Enter Row and Col(m*n):");
//	scanf("%d%*c%d",&m,&n);
//	InputArray(*a, m, n);
//	FindMax(*a, m, n, &pRow, &pCol);
//	printf("Row : %d\nCol : %d\nvalue : %d\n",pRow,pCol,a[pRow][pCol]);
//}
//
//void InputArray(int* p, int m, int n)
//{
//	int i, j;
//	for(i = 0;i < m;i++)
//		for(j = 0;j < n;j++)
//			scanf("%d",&p[i*N+j]);
//}
//
//void FindMax(int* p, int m, int n, int *pRow, int *pCol)
//{
//	int k = p[0];
//	for(int i = 0;i < N;i ++)
//		for(int j = 0;j < N;j ++)
//			if(k < p[i*N+j])
//			{
//				k = p[i*N+j];
//				*pRow = i;
//				*pCol = j;
//			}
//}
