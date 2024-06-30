//#include<stdio.h>
//#include<string>
//typedef struct date
//{
//	int year;
//	int month;
//	int day;
//}DATE;
//
//struct student
//{
//	long studentID;
//	char studentName[20];
//	char studentSex;
//	DATE birthday;
//	int score[4];
//}stu[4];
//
//int main ()
//{
//	FILE* fp;
//	fp = fopen("info.txt","r");
//	float sum[4];
//	for(int i = 0; i < 4; i ++)
//	{
//		fscanf(fp, "%ld  %s  %c  %d/%d/%d  %d  %d  %d  %d  %f\n",
//			&stu[i].studentID,
//			&stu[i].studentName,
//			&stu[i].studentSex,
//			&stu[i].birthday.year,
//			&stu[i].birthday.month,
//			&stu[i].birthday.day,
//			&stu[i].score[0],
//			&stu[i].score[1],
//			&stu[i].score[2],
//			&stu[i].score[3],
//			&sum[i]);
//	}
//	printf("Read Success!!!\n");
//	char name1[20];
//	printf("Enter the name you want to search : ");
//	scanf("%s",name1);
//	for(int i = 0; i < 4; i++)
//		if(strcmp(name1,stu[i].studentName) == 0)
//		{
//		printf("%ld  %s  %c  %d/%d/%d  %d  %d  %d  %d  %.1f\n",
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
//			sum[i]);
//		}
//	return 0;
//}