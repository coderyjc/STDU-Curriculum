#include<stdio.h>

typedef struct date
{
	int year;
	int month;
	int day;
}DATE;

typedef struct student
{
	long studentID;
	char studentname[10];
	char studentSex;
	DATE birthday;
	int score[4];
}STUDENT;

int main()
{
	STUDENT stu1 = {100310121,"Íõ¸Õ",'M',{1991,5,16},{78,98,55,65}};
	STUDENT stu2;
	printf("stu2:%10ld%8s%3c%6d/%02d/%02d%4d%4d%4d%4d\n",stu2);
	return 0;
}