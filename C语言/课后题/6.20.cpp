//#include<stdio.h>
//
//#include<math.h>
//
//int main ()
//
//{
//	int qian , bai , shi , ge ;
//	int i , j , k ;
//
//	for ( i = 1000 ; i < 9999 ; i++ )
//	{
//		qian = i / 1000 ;
//		bai = ( i - 1000 * qian ) / 100 ;
//		shi = ( i - 1000 * qian - 100 * bai ) / 10 ;
//		ge = i % 10 ;
//
//		if ( qian == bai && shi == ge && bai != shi )
//		{
//			for ( k = sqrt(1000.0) ; k <= sqrt(9999.0)  ; k++ )
//			{
//				if ( k * k == i ) printf("%d\n",i);
//				else continue ;
//			}
//		}
//		
//	}
//
//
//	return 0 ;
//
//
//}