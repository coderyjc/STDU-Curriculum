//#include<stdio.h>
//
//
//void FindMax(int findmax[])
//{
//	int MaxDirection,MinDirection;
//	int max=0,min=999;
//	int count,trans;
//	for (count = 0;count<10;count++)
//	{
//		if(max<findmax[count])
//		{
//			max = findmax[count];
//			MaxDirection = count ;
//		}
//		if(min>findmax[count])
//		{
//			min = findmax[count];
//			MinDirection = count ;
//		}
//	}
//	trans = findmax[MaxDirection];
//	findmax[MaxDirection]=findmax[MinDirection];
//	findmax[MinDirection]=trans;
//
//	for (count = 0;count<10;count++)
//	printf("%4d",findmax[count]);
//
//}
//
//void main ()
//{
//	int findmax[10];
//	int i ;
//	printf("Enter 10 numbers : ");
//	for(i=0;i<10;i++)
//		scanf("%d",&findmax[i]);
//	printf("\n");
//	FindMax(findmax);
//}