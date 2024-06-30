//#include<time.h>
//#include<stdlib.h>
//#include<stdio.h>
//void Print(int k);
//void Print2(int k);
//int main()
//{
//	int a,b,right,count,k;
//	double c;
//	char j;
//A:for(count=1,right=0;count<=10;count++)
//  {
//	  srand(time(NULL));
//	  a=rand()%10+1;
//	  b=rand()%10+1;
//	  j=rand()%4+1;
//	  k=rand()%4+1;
//	  switch(j)
//	  {
//	  case 1:
//		  {
//			  printf("%d+%d=",a,b);
//			  scanf("%lf",&c);
//			  if(c==a+b)
//			  {Print(k);right++;continue;}
//			  if(c!=a+b)
//			  {Print2(k);continue;}
//		  }
//	  case 2:
//		  {
//			  printf("%d-%d=",a,b);
//			  scanf("%lf",&c);
//			  if(c==a-b)
//			  {Print(k);right++;continue;}
//			  if(c!=a-b)
//			  {Print2(k);continue;}
//		  }
//	  case 3:
//		  {
//			  printf("%d*%d=",a,b);
//			  scanf("%lf",&c);
//			  if(c==a*b)
//			  { Print(k);right++;continue;}
//			  if(c!=a*b)
//			  { Print2(k);continue; }
//		  }
//	  case 4:
//		  {
//			  printf("%d/%d=",a,b);
//			  scanf("%lf",&c);
//			  if(c==a/b)
//			  {Print(k); right++; continue;}
//			  if(c!=a/b)
//			  {Print2(k);continue;}
//		  }
//	  }
//  }
//  printf("分数为%d\n 正确率为%lf\n",right*10,right*0.1);
//  if(right<=7.5)
//  {
//	  printf("Please do a text again!");
//	  goto A;
//  }
//  if(right>7.5)	printf("Good job!  End!");
//  return 0;
//}
//
//void Print(int k)
//{
//	switch(k)
//	{
//	case 1:printf("Very good!\n");break;
//	case 2:printf("Excellent!\n");break;
//	case 3:printf("Nice work1\n");break;
//	case 4:printf("Keep up the good work!\n");break;
//	}
//}
//
//void Print2(int k)
//{
//	switch(k)
//	{
//	case 1:printf("NO.Please try again.\n");break;
//	case 2:printf("Wrong.Try once more.\n");break;
//	case 3:printf("Do not give up!\n");break;
//	case 4:printf("Not correct.Keep trying.\n");break;
//	}
//}