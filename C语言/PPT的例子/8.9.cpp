//#include<stdio.h>
//
//void tran(int *p);
//
//int main ()
//{
//	int i;
//	int a[10] = {1,2,3,4,5,6,7,8,9,10};
//	int *p = a;
//
//	tran(p);
//
//	for(int i = 0;i < 10;i ++)
//	printf("%d ",a[i]);
//
//}
//void tran(int *p)
//{
//	int t;
//	int *i = p, *j = p + 9;
//	for(;i < j;i++,j--)
//	{
//		t = *i;
//		*i = *j;
//		*j = t;
//	}
//}