//
//#include<stdio.h>
//#include<math.h>
//
//void Printf(int a);
//int IsPrime(int a);
//void Order(int a[]);
//
//int main ()
//{
//	int a ;
//
//	printf("质因数分解并由小到大排序：\n");
//	printf("Please enter a number : ");
//	scanf("%d",&a);
//
//	if(IsPrime(a)) printf(" %d is a prime number !\n",a);
//	else 
//	{
//		printf("%d=",a);
//		Printf(a);
//	}
//
//	return 0;
//}
//
//int IsPrime(int a)
//{
//	int i ,k=(int)sqrt((double)a);
//
//	for (i = 2 ; i <= k ;i++)
//	{
//		if (a%i==0)	return (0);
//	}	
//
//	return (1);
//}
//
//void Printf(int a)
//{
//	int i ,k=(int)sqrt((double)a) , c ;
//	int divisor[99];
//	int m = 0;
//
//	for (; a != 1 ;i++)
//	{	
//		i = 2 ;	
//B:	c = a % i ;
//
//		if (c==0) 
//		{
//			if (a==i*i) 
//			{
//				divisor[m] = divisor[m+1] = i ;
//				m+=2; 
//				a = a/(i*i) ;
//				if (a==1) 
//					goto A;
//			}
//
//			else 
//			{
//				divisor[m] = i ; 
//				m++;
//				a = a/i ;
//
//				if (a==1) 
//					goto A;
//			}
//		}	
//		else 
//		{
//			for(i = i+1 ; a!=1;i++)
//			{
//				if(IsPrime(i)) 
//					goto B;
//			}
//		}
//	}
//
//A:for ( ; m < 99 ; m++ )  
//	  divisor[m] = 0 ;
//
//  Order(divisor);
//
//}
//
//void Order(int d[])
//{
//	int a , b , c ;
//
//	for (a = 0 ; d[a]!=0 ;a++ )		
//		for (b = a+1 ; d[b] != 0 ; b ++)		
//			if(d[a]>d[b]) 
//			{
//				c=d[a];
//				d[a]=d[b];
//				d[b]=c;
//			}
//
//			printf("%d",d[0]);
//
//			for (a = 1 ; d[a]!=0 ; a++ )	
//				printf("*%d",d[a]);
//
//			printf("\n");
//}