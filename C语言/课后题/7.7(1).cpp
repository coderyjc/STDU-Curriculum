//#include<stdio.h>
//
//int Gcd (int x,int y)
//{
//	int i , t , gcd;
//
//	if (x>y)
//	{
//		for (i = y ; i >= 1 ; i--)
//			if(x%i==0&&y%i==0)
//			{
//				gcd = i;
//				break;
//			}
//	}
//	else 	
//	{		
//		for (i = x ; i >= 1 ; i--)
//			if(x%i==0&&y%i==0) 
//			{
//				gcd = i;
//				break;
//			}
//	}
//	return (gcd);
//}
//
//int main ()
//{
//	int a ,b ;
//	printf("Please enter two numbers : ");
//	scanf("%d%d",&a,&b);
//	printf("Their greatest common dvisor is : %d\n",Gcd(a,b));
//	return 0;
//}