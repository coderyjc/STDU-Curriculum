//#include<stdio.h>
//int DayofYear(int year,int month,int day);
//int main ()
//{
//	int year, month, day;
//	printf("输入年月日（格式：XXXX.XX.XX）：");
//	scanf("%d.%d.%d",&year,&month,&day);
//	printf("This is the %d day of that year !\n",DayofYear(year,month,day));
//}
//
//int DayofYear(int year,int month,int day)
//{
//	int result = 0 ;
//	int monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//	int i ;
//
//	for(i = 0;i < month - 1;i ++)
//		result += monthday[i];
//	result += day ;
//	if((year%400==0||year%100!=0&&year%4==0)&&month>2)
//		result++;
//	return result ;
//}