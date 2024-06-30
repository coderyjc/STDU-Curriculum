//#include<stdio.h>
//void MonthDay(int year, int yearDay, int *pMonday, int *pDay);
//int main ()
//{
//	int year, yearDay, Month, Day;
//	puts("Enter this which day of which year(type XXXX.XXX) ：");
//	scanf("%d.%d",&year,&yearDay);
//	MonthDay(year, yearDay, &Month, &Day);
//	printf("It is %d.%d.%d\n", year, Month, Day);
//}
//
//void MonthDay(int year, int yearDay, int *pMonth, int *pDay)
//{
//	int i, monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//	if(year%400==0||year%100!=0&&year%4==0)	monthday[1]++; // 如果是闰年的话就让2月的天数+1
//	for(i = 0;	;i ++)
//	{
//		yearDay -= monthday[i];   //每循环一次，让总的天数减去这一月的天数
//		if(yearDay <= 0)			//如果小于0了，再加回来，然后退出循环
//		{
//			yearDay += monthday[i];
//			break;
//		}
//	}
//	*pMonth = i + 1 ;			//让地址中的值等于i+1,因为i是从0开始的
//	*pDay = yearDay ;			
//}