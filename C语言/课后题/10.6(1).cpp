//#include<stdio.h>
//#define T 99999
//
//int main ()
//{
//	int i = 0 ;
//	int a = 0 ;
//	int j = 0 ;
//	char k[T] = {};
//	printf("Please enter your string :\n");
//	for(i = 0;i < T;i++)
//	{
//		scanf("%c",&k[i]);
//		if(k[i]=='\n')	break;
//	}
//	i = 0;
//	a = i;
//	while(i < T)
//	{
//		if(k[i]=='\0'&&k[i+1]=='\0')
//			break;
//		else
//			for(j = T-1;j > i;j --)
//			{
//				k[j]=k[j-1];
//			}
//			k[i+1]='\0';
//			i = i + 2;
//	}
//
//	printf("The string that has been changed is :\n");
//
//	for(i = 0;i < T-1 ;i++)
//	{
//		printf("%c",k[i]);
//		if(k[i]=='\0'&&k[i+1]=='\0')	break;
//	}
//}
