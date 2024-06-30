//#include<stdio.h>
//
//void ReadScore();
//void Mode();
//void Median();
//
//int score[40]={};
//int totalScore = 0;
//int Starscore[10];
//float averageScore;
//
//int main ()
//{
//	printf("Enter student's score:\n");
//	ReadScore();
//	Mode();
//	Median();
//}
//
//void ReadScore()
//{
//	int count ;
//	for (count = 0;count<40;count++)
//	{
//		scanf("%d",&score[count]);
//		totalScore += score[count];
//		(float)averageScore += (float)score[count]/40;
//	}
//	printf("Average number is : %f\n",averageScore);
//	printf("Total number is : %d\n",totalScore);
//}
//
//void Mode()
//{
//	int count ;
//	int i ;
//	int max ;
//	int temp ;
//	for (count = 0;count<40;count++)
//	{
//		switch(score[count])
//		{
//		case 1:Starscore[0]++;break;
//		case 2:Starscore[1]++;break;
//		case 3:Starscore[2]++;break;
//		case 4:Starscore[3]++;break;
//		case 5:Starscore[4]++;break;
//		case 6:Starscore[5]++;break;
//		case 7:Starscore[6]++;break;
//		case 8:Starscore[7]++;break;
//		case 9:Starscore[8]++;break;
//		case 10:Starscore[9]++;break;
//		default:printf("Wrong!!\n");
//		}
//	}
//	max = Starscore[0];
//	for (i=0 ; i<10;i++)
//	{
//		if (max<Starscore[i])
//		{
//			max = Starscore[i];
//			temp = i ;
//		}
//
//		else temp = 0;
//	}
//
//	printf("Mode number is %d.\n",temp);
//}
//
//void Median()
//{
//	int i , j ;
//	int max ;
//	int temp ;
//	for (i = 0;i < 40;i ++)
//	{
//		max = i ;
//		for (j = i + 1;j < 40;j ++)
//		{
//			if (max < score[j]) max = j ;
//		}
//		temp = score[i];
//		score[i] = score [j];
//		score[j] = temp;
//	}
//
//	printf("Median is %f.\n",((float)score[20]+(float)score[21])/2);
//
//}
