//#include<stdio.h>
//
//int Gcd (int x,int y)
//{
//	int gcd = 1;
//	if (x%y==0) gcd = 0;
//	return (gcd);
//}
//
//
//
//int main ()
//{
//	int a ,b ,gcd = 1;
//
//	printf("Please enter two numbers : ");
//	scanf("%d%d",&a,&b);
//
//	for ( ;gcd != 0; )
//	{
//		if (a > b) 
//		{a = a-b ; gcd = Gcd (a,b);}
//		if (a < b) 
//		{b = b-a ; gcd = Gcd (a,b);}
//	}
//	if (a = b) gcd = a ;
//
//	printf("Their greatest common dvisor is : %d\n",gcd);
//
//	return 0;
//}