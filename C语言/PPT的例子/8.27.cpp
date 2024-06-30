//#include<stdio.h>
//#include<string.h>
//
//void Order(char *p[]);
//
//int main ()
//{
//	char *p[4] = {"Chinese","American","Koera","India"};
//	printf("Before exchange.\n");
//	for(int i = 0;i < 4;i++)
//		printf("%s ",p[i]);
//	printf("\n");
//
//	Order(p);
//	printf("After exchange.\n");
//	for(int i = 0;i < 4;i ++)
//		printf("%s ",p[i]);
//	printf("\n");
//}
//
//void Order(char *p[])
//{
//	char *temp = NULL;
//	for(int i = 0;i < 4;i++)
//		for(int j = i+1;j < 4;j++)
//			if(strcmp(p[i],p[j]) > 0)
//			{
//				temp = p[i];
//				p[i] = p[j];
//				p[j] = temp;
//			}				
//}