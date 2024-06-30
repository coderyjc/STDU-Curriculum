//#include<stdio.h>
//
//#define S 9999
//
//char a[S]={};
//
//int main ()
//{
//	int i = 0;
//	int j;
//	char x;
//	printf("Enter the string : \n");
//	gets(a);
//	printf("Enter the character you want to delete : ");
//	scanf("%c",&x);
//
//	for(;i < S;i ++)
//	{
//		if(a[i]==x)
//		{
//			for(j = i;j < S;j ++)
//			{
//				a[j]=a[j+1];
//			}
//		}
//	}
//
//	for( i = 0;i < S;i++)
//	{
//		printf("%c",a[i]);
//		if(a[i]=='\0'&&a[i+1]=='\0')
//			break;
//	}
//
//	return 0;
//}