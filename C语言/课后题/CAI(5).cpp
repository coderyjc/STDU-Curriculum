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
//	int a , b , c , count , j  ;
//	double right ;
//	char sign ; 
//
//	A:for ( count = 1 , right = 0 ; count <= 10 ; count ++ )
//	{
//		srand(time(NULL));
//
//		a = rand() % 9 + 1 ;
//		b = rand() % 9 + 1 ;
//		j = rand() % 4 + 1 ;
//
//		switch (j)
//		{
//
//		case 1 : 
//			{
//				printf(" %d + %d = ", a , b );
//				scanf("%d",&c);
//
//			if ( c == a + b  )	
//				{
//					printf("Right!\n");
//					right ++ ;
//					continue ;
//				}
//			if (c != a + b )	
//				printf("Wrong!\n");break ;
//			}
//
//		case 2 : 
//			{
//				printf(" %d - %d = ", a , b );
//				scanf("%d",&c);
//
//			if ( c == a - b  )	
//				{
//					printf("Right!\n");
//					right ++ ;
//					continue ;
//				}
//			if (c != a - b )	
//				printf("Wrong!\n");break ;
//			}
//
//		case 3 : 
//			{
//				printf(" %d * %d = ", a , b );
//				scanf("%d",&c);
//
//			if ( c == a * b  )	
//				{
//					printf("Right!\n");
//					right ++ ;
//					continue ;
//				}
//			if (c != a * b )	
//				printf("Wrong!\n");break ;
//			}
//		case 4 : 
//			{
//				printf(" %d / %d = ", a , b );
//				scanf("%d",&c);
//
//			if ( c == a / b  )	
//				{
//					printf("Right!\n");
//					right ++ ;
//					continue ;
//				}
//			if (c != a / b )	
//				printf("Wrong!\n");break ;
//			}
//
//		}
//
//
//	}
//
//	printf("Your score is %.0lf \nYour right rate is : %.1lf\n", right , right / 10 );
//
//	if ( right <= 7.5 )  
//		{
//			printf("Your right rate is less than 0.75 \nPlease do a test again ! \n");
//			goto A ;
//		}
//
//	return 0 ;
//
//}