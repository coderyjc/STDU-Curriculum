//#include<stdio.h>
//void Carry(int x[],int n);
//void LevelUp(int a[]);
//
//int main ()
//{
//	int a[50];
//	int i ;
//	for(i = 0;i < 50;i++)
//		a[i] = 0;
//	a[49] = 1;
//	Carry(a,i);
//}
//
//void Carry(int x[50],int n)//x is array that is used to save the big data;
//{						 //n is the step
//	int i , j;
//	int t = 1;
//	for(t = 1;t<=40;t++)
//	{
//		for(i = 0;i < 50;i++)
//		x[i] = 0;
//
//		x[49] = 1;
//
//		printf("%d ! = ",t);
//
//		for(i = 1;i<=t;i++)
//		{
//			for(j = 0;j < 50;j ++)
//			{
//				x[j] *= i;
//				LevelUp(x);
//			}
//		}
//
//		for(i = 0;i < 50;i++)
//		{
//			if(x[i]!=0)	
//			{
//				for(;i<50;i++)
//					printf("%d",x[i]);
//			}
//			else continue;
//		}
//		printf("\n");
//	}
//}
//
//void LevelUp(int a[])
//{
//	int i;
//	for(i = 49;i > 0;i --)
//	{
//		while(a[i] >= 10)
//		{
//			a[i] -= 10;
//			a[i-1]++;
//		}
//	}
//
//}
