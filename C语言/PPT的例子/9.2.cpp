//#include<stdio.h>
//
//void Input(struct student a[]);
//void Output(struct student a);
//
//struct student
//{
//	long int number;
//	char name[20];
//	double score;
//}student[2];
//
//int main ()
//{
//	Input(student);
//	student[0].score > student[1].score ? Output(student[0]) : Output(student[1]) ;
//}
//
//void Input(struct student a[])
//{
//	for(int i = 0;i < 2;i ++)
//	{
//		printf("Enter student%d number : ",i+1);
//		scanf("%ld",&student[i].number);
//		printf("Enter student%d name : ",i+1);
//		getchar();
//		gets(student[i].name);
//		printf("Enter student%d score : ",i+1);
//		scanf("%lf",&student[i].score);
//	}
//}
//
//void Output(struct student a)
//{
//	printf("Number : %ld\nName : %s\n Score : %.1lf\n",
//		a.number,
//		a.name,
//		a.score);
//}
