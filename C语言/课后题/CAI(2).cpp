//#include<stdio.h>
//
//#include<math.h>
//
//#include<stdlib.h>
//
//#include<time.h>
//
//int main ()
//
//{
//	int a , b , c , count ;
//
//	srand(time(NULL));
//
//	a = rand() % 9 + 1 ;
//	b = rand() % 9 + 1 ;
//
//	printf(" %d + %d = ", a , b );
//
//	for ( count = 0 ; ; )
//	{
//		scanf("%d",&c);
//
//		if ( c == a + b )	
//			{
//				printf("Right!\n");
//				break ;
//			}
//		if (c != a + b )
//			{
//				printf("Wrong!Please try again !\n");
//				count ++ ;
//			}
//		if (count == 3)	
//			{
//				printf("Wrong ! You have tried three times !");
//				break ;
//			}
//
//	}
//
//	return 0 ;
//}