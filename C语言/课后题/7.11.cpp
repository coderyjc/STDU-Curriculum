//#include<stdio.h>
//#include<time.h>
//#include<stdlib.h>
//
//void Computer ();
//void Man ();
//int a = 1;
//
//int main ()
//{
//	int e;
//	srand(time(NULL));
//	e = rand()%2+1;
//
//	if(e = 1)
//	{
//		for (;a < 30;)
//		{
//			Man();
//			if (a==30)	printf("You win!\n");
//			Computer();
//			if (a==30)	printf("You lose!\n");
//		}
//	}
//
//	if(e = 2)
//	{
//		for (;a < 30;)
//		{
//			Computer();
//			if (a==30)printf("You lose!\n");
//			Man();
//			if (a==30)printf("You win!\n");
//		}
//	}
//	return 0;
//}
//
//void Man ()
//{
//	int i , o ;
//	printf("Please enter a number or two(input 0 to stop this turn):");
//	for (i=1;i<=2;i++)
//	{
//		scanf("%d",&o);
//		if (o == 0) break;
//		if (o!=a+1)
//		{
//			printf("Enter wrong!\n");
//			a--;
//			i--;
//		}
//		a++ ;
//	}
//}
//
//void Computer ()
//{
//	int i ;
//
//	srand(time(NULL));
//	i = (30 - a) % 3 ;
//
//	if(i = 1)	a++;
//	else if(i = 2) a += 2;
//	else a += rand()%2+1 ;
//
//	printf("Now----a = %d\n",a);
//
//}
