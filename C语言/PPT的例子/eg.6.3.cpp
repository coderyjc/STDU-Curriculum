//
//// 2019.11.04
//
//#include<stdio.h>
//
//int main ()
//
//{
//	int s[10] , t , i , j ;
//
//	printf("Please enter ten square : \n");
//
//	for ( t = 0 ; t <= 9 ; t ++)
//	{
//		printf("NO.%2d: " , t+1);
//		scanf("%d",&s[t]);
//		printf("\n");
//	}
//
//	for (t = 0 ; t<=9 ; t++)
//	{
//		for (i = t+1 ; i <= 9 ; i++)
//		{
//			if(s[t]<s[i])
//			{
//				j = s [t];
//				s[t] = s[i];
//				s[i] = j ;
//			}
//		}
//	}
//
//	for ( t = 0 ; t <= 9 ; t++ )	printf("%4d",s[t]);
//
//	return 0;
//
//}