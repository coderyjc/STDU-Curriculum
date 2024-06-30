//#include<stdio.h>
//
//void save(struct student a[]);
//
//typedef struct date
//{
//	int year;
//	int month;
//	int day;
//}DATE;
//
//typedef struct student
//{
//	long studentID;
//	char studentName[20];
//	char studentSex;
//	DATE birthday;
//	int score[4];
//}STUDENT;
//
//int main()
//{
//	int i, j, sum[30];
//	STUDENT stu[30] = {
//		{100310121,"wanggang",'M',{1991,5,19},{72,65,98,75}},
//		{100310122,"lixiaoming",'M',{1991,5,20},{72,85,98,75}},
//		{100310123,"wanglihong",'F',{1991,5,4},{72,65,48,75}},
//		{100310124,"chanlili",'F',{1991,5,12},{42,65,98,35}}
//	} ;
//	for(i = 0; i < 4; i++)
//	{
//		sum[i] = 0;
//		for(j = 0; j < 4; j++)
//			sum[i] = sum[i] + stu[i].score[j];
//		printf("%10ld%15s%3c%6d/%02d/%02d%4d%4d%4d%4d%6.1f\n",
//			stu[i].studentID,
//			stu[i].studentName,
//			stu[i].studentSex,
//			stu[i].birthday.year,
//			stu[i].birthday.month,
//			stu[i].birthday.day,
//			stu[i].score[0],
//			stu[i].score[1],
//			stu[i].score[2],
//			stu[i].score[3],
//			sum[i]/4.0);
//	}
//
//	save(stu);
//
//	return 0;
//}
//
//void save(struct student a[])
//{
//	FILE* fp;
//	fp = fopen("info.txt", "wb+");
//	if(fp == NULL)
//	{
//		printf("Open failed!\n");
//		return ;
//	}
//	float sum[4];
//	for(int i = 0; i < 4; i ++)
//	{
//		sum[i] = (a[i].score[0] + a[i].score[1] + a[i].score[2] + a[i].score[3])/4; 
//		fprintf(fp, "%10ld%15s%3c%6d/%02d/%02d%4d%4d%4d%4d%6.1f\n",
//			a[i].studentID,
//			a[i].studentName,
//			a[i].studentSex,
//			a[i].birthday.year,
//			a[i].birthday.month,
//			a[i].birthday.day,
//			a[i].score[0],
//			a[i].score[1],
//			a[i].score[2],
//			a[i].score[3],
//			sum[i]/4.0);
//	}
//	printf("Success!!!\n");
//
//	fclose(fp);
//	return ;
//}
