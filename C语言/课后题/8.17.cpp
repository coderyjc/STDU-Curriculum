//#include<stdio.h>
//
//void ReadScore();
//void Order();
//void PrintScore();
//
//
//int studentScore[40];
//int studentNumber ;
//
//void main (){
//	int n ;
//	printf("Please enter the students' total number : ");
//	scanf("%d",&studentNumber);
//	ReadScore();
//	Order();
//	PrintScore();
//}
//
//void ReadScore(){
//	int i ;
//	printf("Please enter you score : ");
//	for(i = 0;i < studentNumber;i++)
//		scanf("%d",&studentScore[i]);
//}
//
//void Order(){
//	int temp ;
//	int i , j;
//	for (i = 0;i < studentNumber;i++)
//	{
//		for(j = 0;j<studentNumber-1;j++)
//		{
//			if(studentScore[j]>studentScore[j+1])
//			{
//				temp = studentScore[j];
//				studentScore[j] = studentScore[j+1];
//				studentScore[j+1] = temp ;
//			}	
//		}
//	}
//}
//
//void PrintScore()
//{
//	int i ;
//	printf("The right order is :");
//	for (i = 0;i < studentNumber;i ++)
//		printf("%d  ",studentScore[i]);
//}
