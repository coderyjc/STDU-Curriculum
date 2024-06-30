//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct student
//{
//	long int number;
//	char name[30];
//	float score[3];
//	float average;
//}STU;
//
//int main ()
//{
//	int n;
//	printf("Enter the total number of student : ");
//	scanf("%d",&n);
//	STU* stu = (STU*)calloc(n,sizeof(STU));
//	printf("Enter student's info(number name and score*3 ):\n");
//	for(int i = 0;i < n;i ++)
//	{
//		scanf("%ld",&stu[i].number);
//		scanf("%s",stu[i].name);
//		scanf("%f%*c%f%*c%f",&stu[i].score[0],&stu[i].score[1],&stu[i].score[2]);
//	}
//
//	for(int i = 0;i < n;i ++)
//		stu[i].average = (stu[i].score[0]+stu[i].score[1]+stu[i].score[2])/3;
//
//	STU max = stu[0];
//	for(int i = 1;i < n;i ++)
//	{
//		if(max.average < stu[i].average)
//			max = stu[i];
//	}
//
//	printf("\nnumber : %ld\nname : %s\n score : %.1f %.1f %.1f \naverage : %.1f\n",
//		max.number,max.name,max.score[0],max.score[1],max.score[2],max.average);
//
//	free(stu);
//}