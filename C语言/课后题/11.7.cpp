//#include<stdio.h>
//#include<stdlib.h>
//
//void InputAttay(int *p, int m, int n);
//void Findmax(int *p, int m, int n,int *pRow, int *pCol);
//
//int main ()
//{
//	int m , n ;
//	printf("Class :");
//	scanf("%d",&m);
//	printf("Student :");
//	scanf("%d",&n);
//	int *p = NULL;
//	p = (int*)calloc(m*n,sizeof(int));
//	if(p == NULL)
//	{
//		printf("No enough memory!\n");
//		return 0;
//	}
//	InputAttay(p,m,n);
//	int Col = 0,Row = 0;
//	int *pCol = &Col, *pRow = &Row;
//	Findmax(p,m,n,pRow,pCol);
//	printf("The highest score is %d\nHis class:%d\nHis number:%d\n",*(p+(*pRow)*n+*pCol),*pRow+1,*pCol+1);
//	return 0;
//}
//
//void InputAttay(int *p, int m, int n)
//{
//	for(int i = 0;i < m;i++)
//		for(int j = 0;j < n;j++)
//			scanf("%d",&*(p+i*n+j));
//}
//
//void Findmax(int *p, int m, int n, int *pRow, int *pCol)
//{
//	int max = *p;
//	for(int i = 0;i < m;i++)
//		for(int j = 0;j < n;j++)
//			if(max < *(p+i*n+j))
//			{
//				max = *(p+i*n+j);
//				*pRow = i;
//				*pCol = j;
//			}
//}