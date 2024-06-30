//#include<stdio.h>
//
//void InputRecord();
//void TotalAndAverage();
//void OrderByScore();
//void StatisticAnaylysis();
//void OrderByNumber();
//void Search();
//void ListRecord();
//
//int score[30][2];
//int level[5];
//int totalStudent;
//int total = 0 ;
//float average = 0 ;
//
//int main ()
//{
//	int option;
//	int A;
//	printf("Student achievement management system V1.0\n");
//	printf("1.Input record.\n");
//	printf("2.Caculate total and average score of course.\n");
//	printf("3.Sort in descending order by score.\n");
//	printf("4.Sort in ascending order by number.\n");
//	printf("5.Search by number.\n");
//	printf("6.Statistic anaylysis.\n");
//	printf("7.List record.\n");
//	printf("0.Exit.\n");
//	printf("Please enter your option:");
//
//	scanf("%d",&option);
//
//	switch(option)
//	{
//	case 1 : InputRecord();			break ;
//	case 2 : TotalAndAverage();		break ;
//	case 3 : OrderByScore();		break ;
//	case 4 : OrderByNumber();		break ;
//	case 5 : Search();				break ;
//	case 6 : StatisticAnaylysis();	break ;
//	case 7 : ListRecord();			break ;
//	case 0 : return 0;
//	default: return 0;
//	}
//}
//
//void InputRecord()
//{
//	int i ;
//	char c;
//	printf("1.Input record.\n");
//	printf("\nPlease input students' number and record : \n");
//	for (i = 0 ; i < 30 ; i ++)
//	{
//		scanf("%d",&score[i][0]);
//		if(score[i][0]<0)
//		{
//			totalStudent = i ;
//			break;
//		}
//		scanf("%d",&score[i][1]);
//		switch(score[i][1]/10)
//		{
//		case 1: level[4]++ ; break ;
//		case 2: level[4]++ ; break ;
//		case 3: level[4]++ ; break ;
//		case 4: level[4]++ ; break ;
//		case 5: level[4]++ ; break ;
//		case 6: level[3]++ ; break ;
//		case 7: level[2]++ ; break ;
//		case 8: level[1]++ ; break ;
//		case 9: level[0]++ ; break ;
//		case 10:level[0]++ ; break ;
//		default : break ;
//		}
//	}
//	printf("Enter Success ! \n\n");
//	totalStudent = i ;
//		for (i = 0;i < totalStudent;i++)
//	{
//		total += score[i][1] ;
//		average += score[i][1]/(float)totalStudent;
//	}
//
//	main();
//}
//
//void TotalAndAverage()
//{
//	int i ;
//	printf("\nCaculate total and average score of course.\n\n");
//	printf("-----------------------------\n");
//	printf("Their total score is:%-5.2d.\n",total);
//	printf("Their average score is:%-5.2f.\n",average);
//	printf("-----------------------------\n");
//	main();
//}
//
//void OrderByScore()
//{
//	int i , j ;
//	int temp1 ;
//	for (i = 0;i < totalStudent ; i++)
//	{
//		for(j = i+1;j < totalStudent ; j++)
//		{
//			if(score[i][1]<score[j][1])
//			{
//			temp1=score[i][1];
//			score[i][1]=score[j][1];
//			score[j][1]=temp1;
//			temp1=score[i][0];
//			score[i][0]=score[j][0];
//			score[j][0]=temp1;
//			}
//		}
//	}
//	printf("  Student score  \n\n");
//	printf("Number    score\n");
//	printf("-----------------\n");
//	for (i = 0;i < totalStudent;i ++)
//		printf("%-4d    %-4d\n",score[i][0],score[i][1]);
//
//	printf("\n");
//	main();
//}
//
//void ListRecord()
//{
//	int i ;
//	printf("  Student score  \n\n");
//	printf("Number    score\n");
//	printf("-----------------\n");
//	for (i = 0;i < totalStudent;i ++)
//		printf("%d     %d\n",score[i][0],score[i][1]);
//	printf("\n");
//	printf("-----------------------------\n");
//	printf("Their total score is:%-5.2d.\n",total);
//	printf("Their average score is:%-5.2f.\n",average);
//	printf("-----------------------------\n");
//	main();
//}
//
//void StatisticAnaylysis()
//{
//	int i ;
//	printf("   StatisticAnaylysis   \n\n");
//	printf("Level    number   rate\n");
//	printf("-----------------------\n");
//	for (i = 0;i < 5;i ++)
//		printf("  %d        %d      %.3f\n",i+1,level[i],(float)level[i]/totalStudent);
//	main();
//}
//
//void OrderByNumber()
//{
//	int i , j ;
//	int temp1 ;
//	for (i = 0;i < totalStudent ; i++)
//	{
//		for(j = i+1;j < totalStudent;j++)
//		{
//			if(score[i][0]>score[j][0])
//			{
//				temp1=score[i][0];
//				score[i][0]=score[j][0];
//				score[j][0]=temp1;
//				temp1=score[i][1];
//				score[i][1]=score[j][1];
//				score[j][1]=temp1;
//			}
//		}
//	}
//	printf("Number    score\n");
//	printf("-----------------\n");
//	for (i = 0;i < totalStudent;i ++)
//		printf("%-4d    %-4d\n",score[i][0],score[i][1]);
//	printf("\n");
//	main();
//}
//
//void Search()
//{
//	int i ;
//	int search ;
//	printf("Enter student's number : ");
//	scanf("%d",&search);
//	for(i = 0;i < totalStudent ; i++)
//		if(score[i][0]==search)
//			printf("score is %d\n",score[i][1]);
//	main();
//}
