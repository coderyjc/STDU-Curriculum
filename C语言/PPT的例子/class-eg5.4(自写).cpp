
	////yanjingcun 
	////2019.10.20
	////
	////#include<stdio.h>

	////int main ()

	////{
	////	double s = 1 , t , a = 0 , p , count ;

	////------------------------while---------------------
	////	while (s<=1000)
	////	{
	////		printf("input student's donation : ");
	////		scanf("%d",&p);
	////		a=a+p;
	////		s++;
	////		if (a>=100000) break;
	////	}
	////--------------------------------------------------

	////----------------------do  while-------------------
	////		s=0;
	////	do
	////	{
	////		printf("input student's donation : ");
	////		scanf("%d",&p);
	////		a=a+p;
	////		s++;
	////		if (a>=100000) break;
	////	}while (s<=1000);
	//////-------------------------------------------------


	////---------------------for---------------------------
	////	for(s=1 ,count = 1;s<=1000; count ++,s++)
	////	{
	////		printf("input student%.0lf's donation : ", count );
	////		scanf("%lf",&p);
	////		a=a+p;
	////		if (a>=100000) break;
	////	}
	////---------------------------------------------------

	////	printf("students total number is : %.1lf\naverage donation is : %.1lf\n",s,a/s);

	////	return 0;

	////}