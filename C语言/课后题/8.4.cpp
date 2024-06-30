//#include<stdio.h>
//
//void Statistics(int score[],int n);
//
//void main ()
//{
//	int number ;
//	int score[40];
//
//	printf("请输入学生人数(最多不超过40人)：");
//	scanf("%d",&number);
//
//	while(number>40||number<=0)
//	{
//		printf("请输入限定范围内的数字！\n");
//		scanf("%d",&number);
//		if(number<40&&number>0)	break;
//	}
//
//	Statistics(score,number);
//
//}
//
//void Statistics(int s[],int n)
//{
//	int t ;
//	int un ;
//	printf("请输入学生成绩\n满分为100，及格分为60:\n");
//	for (t = 0,un = 0 ; t < n ; t++) 
//	{
//		printf("NO.%d  ",t+1);
//		scanf("%d",&s[t]);
//		if(s[t]<60) un++;
//		if(s[t]<0) break;
//			
//	}
//	printf("不及格人数为：%d\n",un);	
//
//
//
//}
//
