//#include<stdio.h>
//#include<stdlib.h>
//
//void Orderandput(struct student a[],int n);
//void Output(struct student a[],int n);
//
//
//typedef struct student
//{
//	long int number;
//	char name[50];
//	int score;
//}STUD;
//
//int main ()
//{
//	int n;
//	printf("Enter the total number of students : ");
//	scanf("%d",&n);
//	struct student* stu = (struct student*)calloc(n,sizeof(struct student));
//	printf("Enter the student's information: number,name and score (enter 'enter' to devide different info) :\n");
//	for(int i = 0; i < n; i ++)
//	{
//		scanf("%ld",&stu[i].number);
//		scanf("%s",stu[i].name);
//		scanf("%d",&stu[i].score);
//	}
//	Orderandput(stu,n);
//	Output(stu,n);
//	free(stu);
//}
//
//void Orderandput(struct student a[],int n)
//{
//	STUD temp;
//	for(int i = 0; i < n; i++)
//		for(int j = i + 1; j < n;j ++)
//			if(a[i].score < a[j].score)
//			{
//				temp = a[i];
//				a[i] = a[j];
//				a[j] = temp;
//			}
//}
//
//void Output(struct student a[],int n)
//{
//	printf("number    name    score \n");
//	printf("----------------------------\n");
//
//	for(int i = 0; i < n; i ++)
//		printf("%-10ld%-8s%-d\n",
//		a[i].number,
//		a[i].name,
//		a[i].score);
//}
//
