//
//
//#include < stdio.h >
//
//int main ()
//
//{
//	int a , b , t , m ;
//
//
//	printf("����ĳ��ĳ�� �� ");
//	scanf("%d��%d��",&a,&b );
//
//	
//	(0==a%100&&0==a%400||0!=a%100&&0==a%4) ? t=1 : t=0;
//
//	switch (b)
//
//	{
//	case 1 : m=31 ; break ;
//	case 2 :
//		switch (t)
//		{
//			case 1 : m=29 ; break ;
//			case 0 : m=28 ; break ;
//			default : printf("����\n");
//		}	
//		break;
//	case 3 : m=31 ; break ;
//	case 4 : m=30 ; break ;
//	case 5 : m=31 ; break ;
//	case 6 : m=30 ; break ;
//	case 7 : m=31 ; break ;
//	case 8 : m=31 ; break ;
//	case 9 : m=30 ; break ;
//	case 10 : m=31 ; break ;
//	case 11 : m=30 ; break ;
//	case 12 : m=31 ; break ;
//	default : printf("����\n");
//	}
//
//	printf("%d��%d����%d��\n",a,b,m);
//
//	return 0 ;
//}