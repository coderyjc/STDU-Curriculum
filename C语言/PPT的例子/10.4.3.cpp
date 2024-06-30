//#include<stdio.h>
//#include<stdlib.h>
//#define SIZE 10
//struct student_type
//{
//	char name[10];
//	int num;
//	int age;
//	char addr[15];
//}stdu[SIZE];
//
//
//void load()
//{
//	FILE* fp;
//	int i;
//	fp = fopen("stu.dat","rb");
//	if(fp == NULL)
//	{
//		printf("Open wrong !!!!!\n");
//		return;
//	}
//	for(i = 0;i < SIZE;i ++)
//	{
//		if(fread(&stdu[i],sizeof(struct student_type),1,fp) != 1)
//		{
//			if(feof(fp))
//			{
//				fclose(fp);
//				return;
//			}
//			printf("read error!!\n");
//		}
//	}
//	fclose(fp);
//}
//
//void save()
//{
//	FILE* fp;
//	int i;
//	fp = fopen("stu.dat","w");
//	if(fp == NULL)
//	{
//		printf("Can't open ths file!!!\n");
//		return;
//	}
//
//	for(i = 0;i < SIZE;i ++)
//	{
//		if(fwrite(&stdu[i],sizeof(struct student_type),1,fp) != 1)
//		printf("file write error !!! \n");
//	}
//	
//	fclose(fp);
//}
//
//int main ()
//{
//	load();
//	save();
//	printf("Success!!!\n");
//	return 0;
//}
//
