//#include<stdio.h>
//
//void Swap(int tran[]);
//
//int main()
//{
//	int rand[10];
//	printf("Input 10 numbers : ");
//	for(int i = 0;i < 10;i++)
//		scanf("%d",&rand[i]);
//	Swap(rand);
//	for(int i = 0;i < 10;i++)
//	printf("%d ",rand[i]);
//}
//
//void Swap(int tran[])
//{
//	int max, maxdir;
//	int min, mindir;
//	max = min = tran[0];
//	maxdir = mindir = 0;
//	for(int i = 1;i < 10; i++)
//	{
//		if(tran[i] < min)
//		{
//			min = tran[i];
//			mindir = i;
//		}
//		if(tran[i] > max)
//		{
//			max = tran[i];
//			maxdir = i;
//		}
//	}
//
//	int temp;
//	temp = tran[maxdir];
//	tran[maxdir] = tran[mindir];
//	tran[mindir] = temp;
//}