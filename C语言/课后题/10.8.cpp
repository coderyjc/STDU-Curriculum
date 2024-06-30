//#include<stdio.h>
//
//int main ()
//{
//	char a[999],b[99];
//	int i , j ;
//
//	printf("Initialize the first shuzu : \n");
//	for(i = 0;i < 999;i++)
//	{
//		scanf("%c",&a[i]);
//		if(a[i]=='\n')	break;
//	}
//
//	printf("Initialize the second shuzu : \n");
//	for(j = 0;j < 99;j++)
//	{
//		scanf("%c",&b[j]);
//		if(b[j]=='\n')	break;
//	}
//
//	for(j = 0;j < 999;j++,i++)
//	{
//		a[i]=b[j];
//		if(b[j]=='\n')	break;
//	}
//
//	printf("The result is :\n");
//	for(i = 0;i < 999;i++)
//	{
//		printf("%c",a[i]);
//		if(a[i]=='\n')	break;
//	}
//
//}