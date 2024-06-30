//#include<stdio.h>
//
//int Fact(int x)  //括号里的x就接收了 main 里的i值，所以此时 x=i
//{
//	int sum = 1, i;
//	for (i = 1;i <= x;i ++)		//i每次都乘到和x一样的值，再返回最后的结果
//	{
//	sum = sum * i ;
//	}
//	return (sum);
//}
//
//int main ()
//{
//	int a ,i ;
//
//	printf("Please enter a number : ");
//	scanf("%d",&a);
//	
//	for(i = 1;i <= a; i++)
//	{
//		printf("%d!=%d\n",i,Fact(i)); // Fact(i)  就把main里的（i）传递给了fact
//	}
//
//	return 0;
//}