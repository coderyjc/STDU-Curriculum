//
//#include<stdio.h>
//#include<math.h>
//void Printf(int a);
//int IsPrime(int a);
//
//int main ()
//{
//	int a ;
//
//	printf("Please enter a number : ");
//	scanf("%d",&a);
//	if(IsPrime(a)) printf("No divesor ! %d is a prime number !\n",a);
//	else Printf(a);
//
//	return 0;
//}
//
//int IsPrime(int a)
//{
//	int i ,k=(int)sqrt((double)a);
//	for (i = 2 ; i <= k ;i++)
//	{
//		if (a%i==0)	return (0);
//	}		
//	return (1);
//}
//
//void Printf(int a)
//{
//	int i ,k=(int)sqrt((double)a) , c ;
//
//	for (i = 2 ; i <= k ;i++)
//	{
//		c = a % i;
//		if (c==0) 
//		{
//			if (a==i*i) printf("%4d",i);
//			else printf("%4d%4d\n",i,a/i);
//		}		
//	}
//
//}
