//#include<stdio.h>
//
//int main ()
//{
//	FILE* fp;
//	char name[10];
//	printf("Enter the name : ");
//	scanf("%s",name);
//	fp = fopen(name,"w");
//	if ( fp == NULL )
//		printf("cannot open this file ! ! \n");
//	else 
//		printf("Success!\n");
//	char ch ;
//
//	ch = getchar();
//	
//	while (ch != '#')
//	{
//		fputc(ch,fp);
//		putchar(ch);
//		ch = getchar();
//	}
//	fclose(fp);
//	putchar(10);
//
//	return 0;
//}