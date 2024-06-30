//#include<stdio.h>
//void Option1();
//void Option2();
//int monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
//int main ()
//{
//	int option ;
//	printf("1.year/month/day ==> yearDay\n");
//	printf("2.yearDay ==> year/month/day\n");
//	printf("3.Exit\n");
//	printf("Enter your option : ");
//	scanf("%d",&option);
//	switch(option)
//	{
//	case 1 : Option1() ; break ;
//	case 2 : Option2() ; break ;
//	case 3 : return 0 ;
//	default: puts("Enter wrong!") ;
//	}
//	return 0;
//}
//
//void Option1()
//{
//	int year, month, day;
//	int result = 0 ;
//	int i ;
//	printf("输入年月日（格式：XXXX.XX.XX）：");
//	scanf("%d.%d.%d",&year,&month,&day);
//	for(i = 0;i < month - 1;i ++)
//		result += monthday[i];
//	result += day ;
//	if((year%400==0||year%100!=0&&year%4==0)&&month>2)
//		result++;
//	printf("This is the %d day of that year !\n",result);
//	main();
//}
//
//void Option2()
//{
//	int year;
//	int yearDay;
//	int Month;
//	int Day;
//	int i;
//	puts("Enter this which day of which year ：");
//	printf("Year：");
//	scanf("%d",&year);
//	printf("day :");
//	scanf("%d",&yearDay);
//	if(year%400==0||year%100!=0&&year%4==0)	monthday[1]++;
//	for(i = 0;	;i ++)
//	{
//		yearDay -= monthday[i];
//		if(yearDay <= 0)
//		{
//			yearDay += monthday[i];
//			break;
//		}
//	}
//	printf("It is %d.%d.%d\n", year,i + 1, yearDay);
//	main();
//}