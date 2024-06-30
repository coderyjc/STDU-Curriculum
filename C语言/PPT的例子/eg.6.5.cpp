//
////yanjingcun
////2019.11.05
//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//int main ()
//
//{
//	int a[3][4] ;
//	int i , j , c , b ;
//	int max ;
//
//	srand(time(NULL)) ;
//
//	for(i = 0 ; i < 3 ; i++)
//		for(j = 0 ; j < 4 ; j++)
//		{	
//			a[i][j]=rand()%100 + 1 ;
//		}
//
//		printf("The number is : \n");
//		for(i = 0 ; i < 3 ; i++)
//		{
//			for(j = 0 ; j < 4 ; j++)
//			{
//				printf("%4d",a[i][j]);
//			}
//			printf("\n");
//		}
//		max = a[0][0];
//
//		for(i = 0 ; i < 3 ; i++)
//			for(j = 0 ; j < 4 ; j++)
//			{
//				if(max <= a[i][j+1])
//				{
//					max = a[i][j+1];
//					c = i + 1;
//					b = j + 2;
//				}
//			}
//
//
//			printf("max = %d\n",max);
//			printf("Location is %d , %d \n",c,b);
//
//			return 0; 
//}