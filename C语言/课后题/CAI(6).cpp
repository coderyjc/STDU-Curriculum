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
//	int a , b , c , count , j , k ;
//	double right ;
//	char sign ; 
//
//	A:for ( count = 1 , right = 0 ; count <= 10 ; count ++ )
//
//	{
//		srand(time(NULL));
//
//		a = rand() % 9 + 1 ;
//		b = rand() % 9 + 1 ;
//		j = rand() % 4 + 1 ;
//		k = rand() % 4 + 1 ;
//
//		switch (j)
//		{
//
//		case 1 : 
//			{
//				printf("NO.%d  %d + %d = ", count , a , b );
//				scanf("%d",&c);
//
//			if ( c == a + b  )	
//				{
//				switch ( k )
//				{
//				case 1 : printf("Very good ! \n"); break ;
//				case 2 : printf("Excellent ! \n"); break ;
//				case 3 : printf("Nice work ! \n"); break ;
//				case 4 : printf("Keep up the good work ! \n"); break ;
//				}
//					right ++ ;
//					goto B ;
//				}
//			if (c != a + b )	
//				switch ( k )
//				{
//				case 1 : printf("No.Please try again ! \n"); goto B ;
//				case 2 : printf("Wrong. Try once more ! \n"); goto B ;
//				case 3 : printf("Don't give up ! \n"); goto B ;
//				case 4 : printf("Not correct . Keep trying ! \n"); goto B ;
//				}
//
//			}
//
//		case 2 : 
//			{
//				printf("NO.%d  %d - %d = ", count , a , b );
//				scanf("%d",&c);
//
//			if ( c == a - b  )	
//				{
//				switch ( k )
//				{
//				case 1 : printf("Very good ! \n"); break ;
//				case 2 : printf("Excellent ! \n"); break ;
//				case 3 : printf("Nice work ! \n"); break ;
//				case 4 : printf("Keep up the good work ! \n"); break ;
//				}
//
//					right ++ ;
//					goto B ;
//				}
//			if (c != a - b )	
//				switch ( k )
//				{
//				case 1 : printf("No.Please try again ! \n"); goto B ;
//				case 2 : printf("Wrong. Try once more ! \n"); goto B ;
//				case 3 : printf("Don't give up ! \n"); goto B ;
//				case 4 : printf("Not correct . Keep trying ! \n"); goto B ;
//				}
//
//			}
//
//		case 3 : 
//			{
//				printf("NO.%d  %d * %d = ", count , a , b );
//				scanf("%d",&c);
//
//			if ( c == a * b  )	
//				{
//				switch ( k )
//				{
//				case 1 : printf("Very good ! \n"); break ;
//				case 2 : printf("Excellent ! \n"); break ;
//				case 3 : printf("Nice work ! \n"); break ;
//				case 4 : printf("Keep up the good work ! \n"); break ;
//				}
//
//					right ++ ;
//					goto B ;
//				}
//			if (c != a * b )	
//				switch ( k )
//				{
//				case 1 : printf("No.Please try again ! \n"); goto B ;
//				case 2 : printf("Wrong. Try once more ! \n"); goto B ;
//				case 3 : printf("Don't give up ! \n"); goto B ;
//				case 4 : printf("Not correct . Keep trying ! \n"); goto B ;
//				}
//
//			}
//		case 4 : 
//			{
//				printf("NO.%d  %d / %d = ", count , a , b );
//				scanf("%d",&c);
//
//			if ( c == a / b  )	
//				{
//				switch ( k )
//				{
//				case 1 : printf("Very good ! \n"); break ;
//				case 2 : printf("Excellent ! \n"); break ;
//				case 3 : printf("Nice work ! \n"); break ;
//				case 4 : printf("Keep up the good work ! \n"); break ;
//				}
//
//					right ++ ;
//					goto B ;
//				}
//			if (c != a / b )	
//				switch ( k )
//				{
//				case 1 : printf("No.Please try again ! \n"); goto B ;
//				case 2 : printf("Wrong. Try once more ! \n"); goto B ;
//				case 3 : printf("Don't give up ! \n"); goto B ;
//				case 4 : printf("Not correct . Keep trying ! \n"); goto B ;
//				}
//			}
//		}
//
//		B:   ;
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
