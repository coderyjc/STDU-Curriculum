//#include<stdio.h>
//int Prime(int a);
//int Isprime(int x);
//int main()
//{
//	int x ;
//	printf("enter a number : ");
//	scanf("%d",&x);
//	printf("%d = ",x);
//	int i ;
//	for(i = 1;x != 1;i++)
//		x = Prime(x);
//}
//
//int Prime(int a)
//{
//	int i ;
//	static int count = 1;
//	for(i = 2;;i++)
//	{
//		if(!Isprime(i))	continue;
//		if(a%i==0) 
//		{
//			if(count == 1) 
//			{
//				printf("%d",i);
//				count++;
//			}
//			else printf(" * %d",i);
//			return (a/i);
//		}
//		else continue;
//	}
//}
//int Isprime(int x)
//{
//	int i ;
//	for(i = 2;i < x; i++)
//	{
//		if(x%i==0) return 0;
//		if(i==x-1) return 1;
//	}
//}