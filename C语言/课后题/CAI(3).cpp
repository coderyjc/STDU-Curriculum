//#include<stdio.h>
//
//#include<stdlib.h>
//
//#include<time.h>
//
//int main ()
//
//{
//	int a , b , c , count  ;
//	double right ;
//
//	for ( count = 1 , right = 0 ; count <= 10 ; count ++ )//因为最多做10道题所以count加到10就跳出来
//	{
//		srand(time(NULL));
//
//		a = rand() % 9 + 1 ;
//		b = rand() % 9 + 1 ;  // 生成 a ，b 两个随机数
//
//		printf(" %d * %d = ", a , b );
//
//		scanf("%d",&c);
//
//		if ( c == a * b )	   // 如果结果是对的，那么输出“right”并把对的个数加一
//			{
//				printf("Right!\n");
//				right ++ ;
//				continue ;
//			}
//
//		if (c != a * b )	printf("Wrong!\n");	//算错了就输出“wrong”呗
//
//	}		//只要count小于10就会一直循环。。。
//
//	printf("Your score is %.0lf \nYour right rate is : %.1lf ", right , right / 10 );
//
//	return 0 ;
//}