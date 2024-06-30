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
//}stud[SIZE];
//
//int main()
//{
//	int i;
//	FILE* fp;
//	fp = fopen("stu.dat","r");
//	if(fp == NULL)
//	{
//		printf("File open error !!\n");
//		exit(0);
//	}
//	for(i = 0;i < SIZE;i ++)
//	{
//		fscanf(fp, "%s%d%d%s", &stud[i].name, &stud[i].num, &stud[i].age, &stud[i].addr);
//		printf("%s %d %d %s\n",stud[i].name,stud[i].num, stud[i].age, stud[i].addr);
//	}
//	fclose(fp);
//	return 0 ;
//}
