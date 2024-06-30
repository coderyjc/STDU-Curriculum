//#include<stdio.h>
//
//void PrintStars(int star[])
//{
//	int row1,row2;
//	for (row1=0;row1<10;row1++)
//	{
//		printf("  %-3d        %-3d     ",row1+1,star[row1]);
//		for (row2=0;row2<star[row1];row2++)
//		{
//			printf("* ");
//		}
//		printf("\n");
//	}
//	
//}
//
//int main ()
//{
//	int score[10];
//	int StudentScore;
//	int count ,row;
//	printf("Enter student's score:\n");
//	for (count = 0;count<40;count++)
//	{
//		scanf("%d",&StudentScore);
//		switch(StudentScore)
//		{
//		case 1:score[0]++;break;
//		case 2:score[1]++;break;
//		case 3:score[2]++;break;
//		case 4:score[3]++;break;
//		case 5:score[4]++;break;
//		case 6:score[5]++;break;
//		case 7:score[6]++;break;
//		case 8:score[7]++;break;
//		case 9:score[8]++;break;
//		case 10:score[9]++;break;
//		default:printf("Wrong!!\n");
//		}
//	}
////--------------------------------------------
//	printf("Grade      Count     Histogram\n");
//		PrintStars(score);
//}