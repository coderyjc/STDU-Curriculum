//#include<stdio.h>
//
//void Order(int *x);
//
//int main ()
//{
//	int a[10];
//	int *p = a;
//	printf("Enter 10 numbers : ");
//	for(int i = 0;i < 10;i++)
//		scanf("%d",&a[i]);
//
//	Order(p);
//
//	for(int i = 0;i < 10;i ++)
//		printf("%d ",*(p+i));
//
//	return 0;
//}
//
//void Order(int* x)
//{
//	int i, j;
//	int t;
//	for(i = 0;i < 10;i ++)
//		for(j = i + 1;j < 10;j ++)
//		{
//			if(*(x + i) < *(x + j))
//			{
//				t = *(x + i) ;
//				*(x + i) = *(x + j) ;
//				*(x + j) = t ;
//			}
//		}
//}
