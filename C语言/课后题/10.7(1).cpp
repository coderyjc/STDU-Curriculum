//#include<stdio.h>
//#define N 999
//
//int main()
//{
//	char random[N]={};
//	char temp ;
//	int i , j;
//	int n ;
//	printf("Enter you string : \n");
//	for(i = 0;i < N;i++)
//	{
//	scanf("%c",&random[i]);
//	if(random[i]=='\n')	break;
//	}
//	n = i;
//	for (i = 0,j = n-1;i < n/2;i++,j--)
//	{
//		temp = random[i];
//		random[i] = random[j];
//		random[j] = temp;
//	}
//	printf("The final string:\n");
//	for(i = 0;i < n;i ++)
//	{
//		printf("%c",random[i]);
//	}
//	printf("\n");
//}