//
//
//#include<stdio.h>
//#include<math.h>
//void Perfect(int a);
//int IsPrime(int a);
//
//int main ()
//{
//	int a ;
//
//	printf("Please enter a number : ");
//	scanf("%d",&a);
//	if(IsPrime(a)) printf("No divesor ! %d is a prime number !\n",a);
//	else Perfect(a);
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
//void Perfect(int a)
//{
//	int i ,k=(int)sqrt((double)a) , c , sum = 1;
//
//	for (i = 2 ; i <= k ;i++)
//	{
//		c = a % i;
//		if (c==0) 
//		{
//			if (a==i*i) sum += i;
//			else sum += i + (a/i);
//		}		
//	}
//
//	if(sum == a)  printf("%d is a perfect number ! \n",a);
//	if(sum != a)  printf("%d is not a perfect number ! \n",a);
//}
