//#include<stdio.h>
//
//int main ()
//{
//	char name[20];
//	printf("Please enter the command : \n");
//	scanf("type %s",name);
//
//	FILE* fp;
//	fp = fopen(name,"rb");
//	if(fp == NULL)
//	{
//		printf("Open error !\n");
//		return 0;
//	}
//	char ch;
//	while(!feof(fp))
//	{
//		ch = fgetc(fp);
//		printf("%c",ch);
//	}
//	return 0;
//
//}