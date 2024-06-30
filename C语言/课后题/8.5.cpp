//#include<stdio.h>
//
//void Statistics(float score[]);
//
//
//void main ()
//{
//	int number;
//	float score[40];
//	Statistics(score);
//}
//
//void Statistics(float s[])
//{
//	int t , p , sum = 0 , o;
//	float average = 0;
//
//	printf("请输入学生成绩:\n");
//
//	for (t = 0 ; t <= 40 ; t++) 
//	{
//		printf("NO.%d  ",t+1);
//		scanf("%f",&s[t]);
//		sum += s[t] ;
//		if(s[t] < 0) break;	
//	}
//
//	average = sum / (t+1) ;
//	o=t;
//	for (t = 0 , p = 0; t <= o ; t++)
//	{
//		if(s[t]>=average) p++ ;
//	}
//
//	printf("达到平均分的人数为：%d 人\n",p);
//}
//
