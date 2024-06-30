//
//#include<stdio.h>
//
//int Magic(int x)
//{
//	int a , b , c;
//	int i ;
//
//	for (i = 100 ; i<=999 ; i++  )
//	{
//	a = i / 100;
//	b = (i - 100*a)/10;
//	c = i % 10;
//	if (100*(a+2*b+2*c)+10*(2*a+2*c+b)+2*a+2*b+c==x)
//		break;
//	}
//return i;
//}
//
//int main ()
//{
//	int total;
//	printf("Please enter the total number : ");
//	scanf("%d",&total);
//	printf("Them number number you imaged is %d \n: ",Magic(total));
//	return 0;
//}