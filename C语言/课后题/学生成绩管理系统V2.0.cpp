//#include<stdio.h>
//
//void InputRecord();
//void TotalAndAverage();
//void OrderByScore1();
//void OrderByScore2();
//void StatisticAnaylysis();
//void OrderByNumber();
//void Search();
//void ListRecord();
//void TransAndPut(int i,int j);
//void Print();
//
//int score[60];
//int level[5];
//int totalStudent;
//int total = 0;
//float average = 0;
//
//int main ()
//{
//	int option = 1;
//	while(option > 0){
//		printf("Student achievement management system V1.0\n");
//		printf("1.Input record.\n");
//		printf("2.Caculate total and average score of course.\n");
//		printf("3.Sort in descending order by score.\n");
//		printf("4.Sort in ascending order by score.\n");
//		printf("5.Sort in ascending order by number.\n");
//		printf("6.Search by number.\n");
//		printf("7.Statistic anaylysis.\n");
//		printf("8.List record.\n");
//		printf("0.Exit.\n");
//		printf("Please enter your option:");
//
//		scanf("%d",&option);
//
//		switch(option)
//		{
//		case 1 : InputRecord();			break ;
//		case 2 : TotalAndAverage();		break ;
//		case 3 : OrderByScore1();		break ;
//		case 4 : OrderByScore2();		break ;
//		case 5 : OrderByNumber();		break ;
//		case 6 : Search();				break ;
//		case 7 : StatisticAnaylysis();	break ;
//		case 8 : ListRecord();			break ;
//		case 0 : return 0;
//		default: printf("Please enter a right number ! ") ; break ;
//		}
//	}
//	return 0;
//}
//
//void InputRecord()
//{
//	int i ;
//	char c;
//	int j ;
//	int control;
//
//	printf("1.Input record.\n");
//	printf("\nPlease input students' number,name and record : \n");
//
//	for (i = 0 ; i < 60 ; i = i+2)
//	{
//		control = 0 ;
//		scanf("%d",&score[i]);// odd number is number 
//		if(score[i]<0)
//		{
//			totalStudent = i/2;
//			break;
//		}
//		scanf("%d",&score[i+1]);// ji shu is score 
//		switch(score[i+1]/10)
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
//		}
//	}
//	printf("Enter Success ! \n\n");
//	totalStudent = i/2;
//	for (i = 1;i < totalStudent*2;i = i+2)
//	{
//		total += score[i] ;
//		average += score[i]/(float)totalStudent;
//	}
//}
//
//void TotalAndAverage()
//{
//	printf("\nCaculate total and average score of course.\n\n");
//	printf("-----------------------------\n");
//	printf("Their total score is:%-5.2d.\n",total);
//	printf("Their average score is:%-5.2f.\n",average);
//	printf("-----------------------------\n");
//	main();
//}
//
//void OrderByScore1()
//{
//	int i , j ;
//	for (i = 1;i < totalStudent*2 ; i = i + 2)
//		for(j = i+2;j < totalStudent*2 ; j = j + 2)
//			if(score[i]<score[j])
//				TransAndPut(i,j);
//	Print();
//}
//
//void OrderByScore2()
//{
//	int i , j ;
//	for (i = 1;i < totalStudent*2 ; i = i + 2)
//		for(j = i+2;j < totalStudent*2 ; j = j + 2)
//			if(score[i]>score[j])
//				TransAndPut(i,j);
//	Print();
//
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
//
//}
//
//void OrderByNumber()
//{
//	int i , j ;
//	int n;
//	for (i = 0;i < totalStudent*2 ;i = i+2)
//		for(j = i+2;j < totalStudent*2;j = j+2)
//			if(score[i]>score[j])
//				TransAndPut(i+1,j+1);
//	Print();
//}
//
//void Search()
//{
//	int i;
//	int search;
//	printf("Enter student's number : ");
//	scanf("%d",&search);
//	for(i = 0;i < totalStudent*2 ; i = i+2)
//	{
//		if(score[i]==search)
//		{
//			printf("\n\n---------------\nscore is %d\n--------------\n\n",score[i+1]);
//			return ;
//		}		
//	}
//	printf("number wrong !!!\n");
//}
//void ListRecord()
//{
//	Print();
//	printf("\n");
//	printf("-----------------------------\n");
//	printf("Their total score is:%-5.2d.\n",total);
//	printf("Their average score is:%-5.2f.\n",average);
//	printf("-----------------------------\n");
//}
//
//void TransAndPut(int i,int j)
//{
//	int temp1;
//	temp1=score[i];
//	score[i]=score[j];
//	score[j]=temp1;
//	temp1=score[i-1];
//	score[i-1]=score[j-1];
//	score[j-1]=temp1;
//}
//
//void Print()
//{
//	int i;
//	printf("\n\n");
//	printf("Number       score\n");
//	printf("-------------------\n");
//	for (i = 0;i < totalStudent*2;i = i + 2)
//		printf(" %d            %d \n",score[i],score[i+1]);
//	printf("\n");
//}