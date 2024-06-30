//
//#include<stdio.h>
//
//int IsPrime(int a)
//{
//	int i , sum = 0 ;
//
//	for (  ; a>1 ; a--)
//	{
//		for (i = 2; i <= a-1 ; i++ )
//		{
//			if (a==2) sum=2;
//			if (a%i==0) break;
//			if (i==a-1) sum=sum+a;
//		}
//	}		
//	return (sum);
//}
//
//int main ()
//{
//	int a ;
//	printf("Please enter a number : ");
//	scanf("%d",&a);
//	if(a==1) printf("Please enter a number greater than 1 !\n");
//	printf("Sum of these prime number from 1 to n is : %d\n" , IsPrime(a));
//	return 0;
//}