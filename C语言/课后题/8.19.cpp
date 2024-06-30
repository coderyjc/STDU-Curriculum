//#include<stdio.h>
//
//void Inputscore();
//void Judge();
//void OrderJudge();
//
//float studentScore[999][999]={};
//float judge[999][2]={};
//int n , m;
//
//int main ()
//{
//	printf("Enter the students' number(n): ");
//	scanf("%d",&n);
//	printf("Enter the judges' number(m): ");
//	scanf("%d",&m);
//
//	Inputscore();
//	Judge();
//	OrderJudge();
//}
//
//void Inputscore()  
//{
//	int i , j ;		// the first place in m is student number  ,  and 1--n is score , n+1 is average .
//	int k ;
//	int x ;
//	int temp ;
//
//	printf("Enter the students' number and score : \n");
//	for(i = 0;i < n;i ++)
//	{
//		studentScore[i][m+1] = 0;
//		for(j = 0;j <= m;j ++)
//			scanf("%f",&studentScore[i][j]);
//	}
//
//	for (i = 0;i < n;i++)
//	{
//		for(j = 1;j <= n;j++)
//			for(k = j+1;k <= n;k++)
//				if(studentScore[i][j]<studentScore[i][k])
//				{
//					temp = studentScore[i][j];
//					studentScore[i][j] = studentScore[i][k];
//					studentScore[i][k] = temp;
//				}
//				for(x = 2;x < n; x++) 
//				{
//					studentScore[i][m+1] +=  studentScore[i][x]/(m-2);
//				}
//	}
//
//	for(i = 0;i < n;i ++)
//		for(j = i +1;j < n;j ++)
//			if(studentScore[i][m+1]<studentScore[j][m+1])
//			{
//				temp = studentScore[i][m+1];
//				studentScore[i][m+1] = studentScore[j][m+1];
//				studentScore[j][m+1] = temp;
//				temp = studentScore[i][0];
//				studentScore[i][0] = studentScore[j][0];
//				studentScore[j][0] = temp;
//			}
//	printf("Rank\tStudent Number\tFinal score\n");
//	printf("-----------------------------------\n");
//	for(i = 0;i < n;i++)		
//		printf("NO.%d\t\t%.0f\t    %.2f\n", i+1 ,studentScore[i][0],studentScore[i][m+1]);
//}
//
//
//void Judge()
//{
//	int i , j ;
//	for(i = 0;i < m;i ++)
//	{
//		judge[i][0] = i;
//		judge[i][1] = 0;
//		for(j = 1;j < n;j++)
//		{
//			judge[i][1] += (studentScore[i][m+1]-studentScore[i][i+1])*(studentScore[i][m+1]-studentScore[i][i+1]);
//		}
//	}
//}
//
//void OrderJudge()
//{
//	int i , j ;
//	float temp ;
//
//	for(i = 0;i < m;i++)
//	{
//		for(j = i + 1;j < m;j ++)
//		{
//			if(judge[i][1]>judge[j][1])
//			{
//				temp = judge[i][1];
//				judge[i][1] = judge[j][1];
//				judge[j][1] = temp;
//				temp = judge[j][0];
//				judge[j][0] = judge[i][0];
//				judge[i][0] = temp;
//			}
//		}
//	}
//	printf("\nRank\tJudge Number\tFinal score\n");
//	printf("-----------------------------------\n");
//
//	for(i = 0;i < m;i++)
//	{
//		printf("NO.%d\t\t%.0f\t    %.2f\n",i+1,judge[i][0]+1,judge[i][1]);
//	}
//}