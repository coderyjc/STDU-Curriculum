//#include<stdio.h>
//
//void main ()
//{
//	int a[10] = {1,2,3,4,5,6,7,8,9,10};
//	int i;
//	int t; 
//
//	for(i = 0;i < 10;i ++)
//		printf("%4d",a[i]);
//	printf("\n");
//
//	for(i = 0;i < 5;i ++)
//	{
//		t = a[i];
//		a[i] = a[9-i];
//		a[9-i] = t;
//	}
//
//	for(i = 0;i < 10;i ++)
//		printf("%4d",a[i]);
//		printf("\n");
//
//}