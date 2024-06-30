//#include<stdio.h>
//#include<stdlib.h>
//#define SIZE 10
//
//struct student_type
//{
//	char name[10];
//	int num;
//	int age;
//	char addr[15];
//}stdu[SIZE];
//
//void save()
//{
//	FILE* fp;
//	int i;
//	fp = fopen("stu.dat","wb");
//	if(fp == NULL)
//	{
//		printf("Can't open ths file!!!\n");
//		return ;
//	}
//
//	for(i = 0;i < SIZE;i ++)
//	{
//		if(fwrite(&stdu[i],sizeof(struct student_type),1,fp) != 1)
//			printf("file write error !!! \n");
//	}
//
//	fclose(fp);
//}
//
//int main()
//{
//	int i;
//	printf("Enter information of 10 student (including name, number, age and address):\n");
//	for(i = 0;i < SIZE;i ++)
//	{
//		scanf("%s%d%d%s",stdu[i].name,&stdu[i].num, &stdu[i].age, stdu[i].addr);
//	}
//	save();
//	return 0;
//}