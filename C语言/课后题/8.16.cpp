//#include<stdio.h>
//#include<time.h>
//#include<stdlib.h>
//
//
//void Sort(int a[],int n);
//
//int main ()
//{
//	int a[11]={};
//	int i ;
//	srand(time(NULL));
//	for(i = 0;i < 10;i++)
//		a[i]=rand()%100+1;
//	Sort(a,10);
//	printf("The 10 random number is \n");
//	for(i = 0;i < 10;i++)
//		printf("%4d",a[i]);
//
//	printf("\nEnter a number : ");
//	scanf("%d",&a[10]);
//	Sort(a,11);
//		printf("The 10 ordered number is \n");
//	for(i = 0;i < 11;i++)
//		printf("%4d",a[i]);
//	printf("\n");
//}
//
//void Sort(int a[],int n)
//{
//	int i , j;
//	int temp;
//	for(j = 1;j <= n - 1; j ++)
//	for(i = 0;i < n - j;i ++)
//	{
//			if(a[i]>a[i+1])
//			{
//				temp = a[i];
//				a[i] = a[i+1];
//				a[i+1] = temp;
//			}
//	}
//}