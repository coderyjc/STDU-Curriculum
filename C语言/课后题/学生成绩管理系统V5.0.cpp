//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
// 
//void totalandaveragecourse(struct student *a);
//void totalandaveragestudent(struct student *a);
//void desendingscore(struct student *a);
//void aesendingscore(struct student *a);
//void aesendingnumber(struct student* a);
//void dictionary(struct student* a);
//void searchbynumber(struct student* a);
//void searchbyname(struct student* a);
//void statisticanaylysis(struct student* a);
//void listrecord(struct student* a);
//void trans(struct student* a, int i, int j);
//void print(struct student* a);
//
//
//typedef struct student
//{
//	long number;
//	char name[30];
//	float score[6];
//	float total;
//	float average;
//}STUDENT;
//
//int student;
//int score_m;
//float coursetaa[6][2];
//float subject[6][5];
//
//int main ()
//{
//	struct student* stu;
//	int option = 1;
//	while(option > 0)
//	{
//A:printf("***********student achievement management system v5.0*********\n");
//		printf("**************************************************************\n");
//		printf("* 1.input record.                                            *\n");
//		printf("* 2.caculate total and average score of every course.        *\n");
//		printf("* 3.caculate total and average score of every student.       *\n");
//		printf("* 4.sort in descending order by total score of every student.*\n");
//		printf("* 5.sort in ascending order by total score of every student. *\n");
//		printf("* 6.sort in ascending order by number.                       *\n");
//		printf("* 7.sort in dictionary order by name.                        *\n");
//		printf("* 8.search by number.                                        *\n");
//		printf("* 9.search by name.                                          *\n");
//		printf("* 10.statistic anaylysis for every course.                   *\n");
//		printf("* 11.list record.                                            *\n");
//		printf("* 0.exit.                                                    *\n");
//		printf("**************************************************************\n");
//		printf("please enter your option:");
//		scanf("%d",&option);
//
//		switch(option)
//		{
//		case 1 : break ;
//		case 2 : totalandaveragecourse(stu) ;	goto A;
//		case 3 : totalandaveragestudent(stu);	goto A;
//		case 4 : desendingscore(stu) ;			goto A;
//		case 5 : aesendingscore(stu) ;			goto A;
//		case 6 : aesendingnumber(stu) ;		goto A;
//		case 7 : dictionary(stu);				goto A;
//		case 8 : searchbynumber(stu) ;			goto A;
//		case 9 : searchbyname(stu);			goto A;
//		case 10: statisticanaylysis(stu);		goto A;
//		case 11: listrecord(stu);  			goto A;
//		case 0 : return 0 ;					goto A;
//		default : printf("Please enter a right number ! \n") ; goto A;
//		}
//
//		printf("Enter the number of student and subject : ");
//		scanf("%d%*c%d",&student,&score_m);
//		printf("Enter Success!!\n");
//		stu = (struct student *)calloc(student, sizeof(struct student));
//		printf("Please enter their nmber, name and each score.\n");
//		for(int i = 0;i < student;i ++)
//		{
//			scanf("%ld %s",&stu[i].number,stu[i].name);
//			for(int j = 0;j < score_m;j++)
//				scanf("%f",&stu[i].score[j]);
//		}
//		printf("Success!!\n");
//	}
//	return 0;
//}
//
//void totalandaveragecourse(struct student *a)
//{
//	for(int i = 0;i < score_m;i ++)
//	{
//		for(int j = 0;j < student;j ++)
//			coursetaa[i][0] += a[j].score[i];
//		coursetaa[i][1] = coursetaa[i][0]/score_m;
//	}
//	printf("Compute Success!!!\n");
//	printf("\n\ncourse   total   average\n------------------------\n");
//	for(int i = 0;i < score_m;i ++)
//		printf("%-9d%-8.1f%-7.1f\n",i+1,coursetaa[i][0],coursetaa[i][1]);
//	printf("\n\n");
//}
//
//void totalandaveragestudent(struct student *a)
//{
//	for(int i = 0;i < student;i ++)
//	{
//		for(int j = 0;j < score_m;j++)
//			a[i].total += a[i].score[j];
//		a[i].average = a[i].total/score_m;
//	}
//	printf("Compute Success!!!\n\n\n");
//	printf("student   total   average\n-------------------------\n");
//	for(int i = 0;i < student; i++)
//		printf("%-10s%-8.1f%-7.1f\n",a[i].name,a[i].total,a[i].average);
//	printf("\n\n");
//}
//
//void desendingscore(struct student *a)
//{
//	STUDENT temp;
//	for(int i = 0;i < student;i ++)
//		for(int j = i+1; j < student; j++)
//			if(a[i].total<a[j].total)
//				trans(a,i,j);
//	print(a);
//}
//
//void aesendingscore(struct student* a)
//{
//	STUDENT temp;
//	for(int i = 0;i < student;i ++)
//		for(int j = i+1; j < student; j++)
//			if(a[i].total>a[j].total)
//				trans(a,i,j);
//		print(a);
//}
//
//void aesendingnumber(struct student* a)
//{
//	for(int i = 0;i < student;i ++)
//		for(int j = i+1; j < student; j++)
//			if(a[i].number>a[j].number)
//				trans(a,i,j);
//		print(a);
//}
//
//void dictionary(struct student* a)
//{
//	for(int i = 0;i < student;i ++)
//		for(int j = i+1; j < student; j++)
//			if(strcmp(a[i].name,a[j].name) > 0)
//				trans(a,i,j);
//		print(a);
//}
//
//void searchbynumber(struct student* a)
//{
//	long search;
//	printf("Enter number ! \n");
//	scanf("%ld",&search);
//	for(int i = 0;i < student;i ++)
//	{
//		if(a[i].number == search)
//		{
//			printf("\nStudent information£º\nnumber:%ld\nname:%s\n",a[i].number,a[i].name);
//			for(int p = 0;p < score_m;p ++)
//				printf("score%d :%.2f\n",p + 1,a[i].score[p]);
//			printf("Total score :%.2f\nAverage score:%.2f\n\n",a[i].total,a[i].average);
//		}
//	}
//}
//
//void searchbyname(struct student* a)
//{
//	char name[30];
//	printf("Please enter hte name you want to search:");
//	scanf("%s",name);
//	for(int i = 0;i < student; i ++)
//		if(strcmp(name,a[i].name)==0)
//		{
//			printf("\nStudent information£º\nnumber:%ld\nname:%s\n",a[i].number,a[i].name);
//			for(int p = 0;p < score_m;p ++)
//				printf("score%d : %.2f\n",p + 1,a[i].score[p]);
//			printf("Total score :%.2f\nAverage score:%.2f\n\n",a[i].total,a[i].average);
//		}
//}
//
//void statisticanaylysis(struct student* a)
//{
//	for(int j = 0;j < score_m; j++)
//	{
//		for(int i = 0;i < student;i ++)
//		{
//			switch((int)a[i].score[j]/10)
//			{
//			case 0:subject[j][0]++ ;break;
//			case 1:subject[j][0]++ ;break;
//			case 2:subject[j][0]++ ;break;
//			case 3:subject[j][0]++ ;break;
//			case 4:subject[j][0]++ ;break;
//			case 5:subject[j][0]++ ;break;
//			case 6:subject[j][1]++ ;break;
//			case 7:subject[j][2]++ ;break;
//			case 8:subject[j][3]++ ;break;
//			case 9:subject[j][4]++ ;break;
//			}
//		}
//	}
//
//	printf("\nsubject  0~60  60~70  70~80  80~90  90~100\n");
//	printf("-------------------------------------------\n");
//	for(int i = 0;i < score_m;i ++)
//		printf("%-9d%-6.2f%-7.2f%-7.2f%-7.2f%-7.2f\n",i+1,subject[i][0]/student,subject[i][1]/student,subject[i][2]/student,subject[i][3]/student,subject[i][4]/student);
//	printf("\n");
//}
//
//void listrecord(struct student* a)
//{
//	printf("\nnumber   name   total   average\n");
//	printf("--------------------------------\n");
//	for(int i = 0;i < student;i ++)
//		printf("%-9ld%-7s%-8.1f%-7.1f\n",a[i].number,a[i].name,a[i].total,a[i].average);
//	printf("\n");
//}
//
//void trans(struct student* a,int i, int j)
//{
//	STUDENT temp;
//	temp = a[i];
//	a[i] = a[j];
//	a[j]= temp;
//}
//
//void print(struct student* a)
//{
//	printf("\nrank   number   name   totalscore\n---------------------------------\n");
//	for(int i = 0;i < student; i ++)
//		printf("%-7d%-9ld%-7s%-10.1f\n",i + 1,a[i].number,a[i].name,a[i].total);
//	printf("\n");
//}