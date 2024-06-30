//
//// 2019.11.04
//
//
//#include<stdio.h>
//
//int main (void)
//
//{
//	double f[20]={1,1} ;
//	int i ;
//	int count = 1 ;
//
//	for ( i = 2 ; i <=19 ; i++ )	f[i] = f[i-1] + f[i-2];
//
//	for ( i = 0 ; i <=19 ; i++ )
//	{
//		printf("f[%.0d]=%4.0lf    " , i+1,f[i]  );
//
//		count ++;
//
//		if (count % 5 == 0 )	
//		{
//			printf("\n");
//			count = 1 ;
//		}
//	}
//	return 0 ;
//}
//
