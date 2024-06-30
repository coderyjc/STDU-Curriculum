//#include<stdio.h>
//
//int main ()
//{
//	int Pascal[7][7]={{1},{1,1}} ;
//	int i , j ;
//	for(i = 2;i < 7;i++)
//	{
//		for(j = 1;j < 7;j++)
//		{
//			Pascal[i][0] = 1;
//			Pascal[i][j]=Pascal[i-1][j-1]+Pascal[i-1][j];
//			if(i==j) Pascal[i][j]=1;
//		}
//	}
//	for(i = 0;i < 7;i++)
//	{
//		for(j = 0;j < 7;j++)
//		{
//			printf("%d  ",Pascal[i][j]);
//			if(i==j) break;
//		}
//		printf("\n");
//	}
//}