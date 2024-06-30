//#include<stdio.h>
//#include<string.h>
//
//int main ()
//{
//	char ch[5][50] , temp[50];
//	printf("Enter 5 strings : \n");
//	for(int i = 0;i < 5;i ++)
//		scanf("%s",ch[i]);
//
//	for(int i = 0;i < 5;i++)
//		for(int j = i; j < 5;j ++)
//			if(strcmp(ch[i],ch[j]) > 0)
//			{
//				strcpy(temp,ch[i]);
//				strcpy(ch[i],ch[j]);
//				strcpy(ch[j],temp);
//			}
//
//			FILE* fp = fopen("b.txt","w");
//			if(fp == NULL)
//				printf("Wrrrrrrrrrrrrong!!!");
//
//			for(int i = 0;i < 5;i ++)
//			{
//				fputs(ch[i],fp);
//				fputs("\n",fp);
//			}
//			printf("Success!!");
//
//			return 0;
//}