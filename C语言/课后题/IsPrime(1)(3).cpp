//
//#include<stdio.h>
//
//void IsPrime(int a)
//{
//	int i ;
//	for (i = 2 ; i <= a-1 ;i++)
//	{
//		if (a%i==0)	goto A;
//		if (i==a-1)	goto B;
//	}
//A : {printf("%d is not a prime number !\n",a);return;}
//B : {printf("%d is a prime number !\n",a);return;}
//}
//
//void main ()
//{
//	int a ;
//
//	printf("Please enter a number : ");
//	scanf("%d",&a);
//	IsPrime(a);
//}