//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//#define SUM 6000
//
//void Print(int x,int y);
//
//int main ()
//{
//	int n ;
//	int random ;
//	int dice[6]={};
//	int count;
//	srand(time(NULL));
//	for(n=1;n<=SUM;n++)
//	{
//		random = rand()%6+1;
//		switch(random)
//		{
//		case 1 : dice[0]++ ; break ;
//		case 2 : dice[1]++ ; break ;
//		case 3 : dice[2]++ ; break ;
//		case 4 : dice[3]++ ; break ;
//		case 5 : dice[4]++ ; break ;
//		case 6 : dice[5]++ ; break ;
//		}
//	}
//	for(count = 0;count<6;count++)
//	Print(count+1,dice[count]);
//}
//
//void Print(int x,int y)
//{
//	printf("point %d rate is %5.3f\n",x,(float)y/SUM);
//}