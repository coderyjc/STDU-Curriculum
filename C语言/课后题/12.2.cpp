//#include<stdio.h>
//
//typedef struct clock
//{
//	int hour;
//	int minute;
//	int second;
//
//}CLOCK;
//
//void update(struct clock *pt)
//{
//	pt->second++;
//	if(pt->second == 60)
//	{
//		pt->minute++;
//		pt->second = 0;
//	}
//	if(pt->minute == 60)
//	{
//		pt->hour ++;
//		pt->minute = 0;
//	}
//	if(pt->hour == 24)
//		pt->hour = 0;
//}
//
//void display(struct clock *pt)
//{
//	printf("%d:%d:%d\n",pt->hour,pt->minute,pt->second);
//}
//
//void delay()
//{
//	for(int i = 0;i < 1000000;i++)
//	{}
//}
//
//int main ()
//{
//
//	CLOCK clock;
//	clock.hour = 0;
//	clock.minute = 0;
//	clock.second = 0;
//	for(int i = 0;i < 1000000;i++)
//	{
//		update(&clock);
//		display(&clock);
//		delay();
//	}
//}
//
