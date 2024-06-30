//#include<stdio.h>
//
//int hour , minute , second ;
//
//void Update ()
//{
//	second++ ;
//	if(second == 60)
//	{
//		second = 0 ;    //===========> 1
//		minute++ ;
//	}
//	if(minute == 60)		//===========> 2
//	{
//		minute = 0;
//		hour++;
//	}
//	if(hour == 24)
//		hour = 0;		//===========> 3
//	}
//
//void Display ()
//{
//	printf("%d.%d.%d\n",hour,minute,second);		//===========> 4
//}
//
//void Delay ()
//{
//	int t ;
//	for (t = 0;t < 100000000 ;t ++);
//}
//
//int main ()
//{
//	int i ;
//	printf("Êý×ÖÊ½Ê±ÖÓ£º\n");//==============> 5
//	for (i = 0;i < 1000000 ; i ++)
//	{
//		Update();
//		Display();
//		Delay();
//	}
//	return 0;
//}