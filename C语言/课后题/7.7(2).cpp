//#include<stdio.h>
//
//int Gcd (int x ,int y)
//{
//	int c = 1; 
//	for ( ;c != 0; )
//	{
//		c = x%y;
//		if( y > c )	{x = y;y = c ;}
//		else {y = x;x = c;}
//	}
//
//	return (x);
//}
//
//int main ()
//{
//	int a ,b ,c;
//	printf("Please enter two numbers : ");
//	scanf("%d%d",&a,&b);
//	c = a>b ? Gcd(a,b) : Gcd(b,a);
//	printf("Their greatest common dvisor is : %d\n",c);
//	return 0;
//}