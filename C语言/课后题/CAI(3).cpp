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
//	for ( count = 1 , right = 0 ; count <= 10 ; count ++ )//��Ϊ�����10��������count�ӵ�10��������
//	{
//		srand(time(NULL));
//
//		a = rand() % 9 + 1 ;
//		b = rand() % 9 + 1 ;  // ���� a ��b ���������
//
//		printf(" %d * %d = ", a , b );
//
//		scanf("%d",&c);
//
//		if ( c == a * b )	   // �������ǶԵģ���ô�����right�����ѶԵĸ�����һ
//			{
//				printf("Right!\n");
//				right ++ ;
//				continue ;
//			}
//
//		if (c != a * b )	printf("Wrong!\n");	//����˾������wrong����
//
//	}		//ֻҪcountС��10�ͻ�һֱѭ��������
//
//	printf("Your score is %.0lf \nYour right rate is : %.1lf ", right , right / 10 );
//
//	return 0 ;
//}