//#include<stdio.h>
//void average(float *a);
//void Search(float *a);
//void Search2(float *a);
//int main()
//{
//	float studentScore[3][4] = {61,59,93,94,95,96,20,98,99,87,86,85};
//	float* p = studentScore[0];
//	average(p);
//	Search(p);
//	Search2(p);
//}
//
//void average(float *a)
//{
//	float i = *a;
//	float aver = 0;
//	for(	;i<*a+12;i++)
//		aver += i/12;
//	printf("%.3f\n",aver);
//}
//
//void Search(float *a)
//{
//	int x ;
//	printf("Enter the student's number : ");
//	scanf("%d",&x);
//	int i ;
//	for(int i = *a+4*x;i < *a+4*x+4;i ++)
//		printf("%4d",i);
//	printf("\n");
//
//}
//void Search2(float *a)
//{
//	printf("These student that has a score less than 60 is:\n ");
//	float *i = a;
//	for(int k = 0;k < 3;k++)
//	{
//		for(int l = 0;l < 4;l++)
//		{
//			if(*((i+k)+l) < 60)
//			{
//				printf("student%d ",k);
//				for(int h = 0;h < 4;h++)
//				{
//					printf("%.1f ",*((i+k)+h));
//				}
//				printf("\n");
//			}
//
//		}
//	}
//}