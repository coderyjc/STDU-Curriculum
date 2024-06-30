//#include<stdio.h>
//#include<string.h>
//
//void InputRecord();
//void TotalAndAverage();
//void DesendingScore();
//void AesendingScore();
//void AesendingNumber();
//void Dictionary();
//void SearchByNumber();
//void SearchByName();
//void StatisticAnaylysis();
//void ListRecord();
//void TransAndPut(int i,int j);
//void Print();
//
//int score[30][2];
//char name[30][20]={};
//int level[5];
//int totalStudent;
//int total = 0;
//float average = 0;
//
//int main ()
//{
//	int option = 1;
//	while(option > 0)
//	{
//		printf("Student achievement management system V3.0\n");
//		printf("1.Input record.\n");
//		printf("2.Caculate total and average score of course.\n");
//		printf("3.Sort in descending order by score.\n");
//		printf("4.Sort in ascending order by score.\n");
//		printf("5.Sort in ascending order by number.\n");
//		printf("6.Sort by dictionary order by name.\n");
//		printf("7.Search by number.\n");
//		printf("8.Search by name.\n");
//		printf("9.Statistic anaylysis.\n");
//		printf("10.List record.\n");
//		printf("0.Exit.\n");
//		printf("Please enter your option:");
//		scanf("%d",&option);
//		switch(option)
//		{
//		case 1 : InputRecord();			break ;
//		case 2 : TotalAndAverage() ;	break ;
//		case 3 : DesendingScore() ;		break ;
//		case 4 : AesendingScore() ;		break ;
//		case 5 : AesendingNumber() ;	break ;
//		case 6 : Dictionary();			break ;
//		case 7 : SearchByNumber() ;		break ;
//		case 8 : SearchByName();		break ;
//		case 9 : StatisticAnaylysis();  break ;
//		case 10:ListRecord();  			break ;
//		case 0 : return 0 ;				break ;
//		default : printf("Please enter a right number ! ") ; break ;
//		}
//	}
//	return 0 ;
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
//	for (i = 0 ; i < 30 ; i ++)
//	{
//		control = 0 ;
//		scanf("%d",&score[i][0]);
//		if(score[i][0]<0)
//		{
//			totalStudent = i ;
//			break;
//		}
//		for(j = 0;j < 20;j ++,control++)
//		{
//			scanf("%c",&name[i][j]);
//			if(control==0)	continue;
//			if(name[i][j] ==' ')
//				break;
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
//		}
//	}
//	printf("Enter Success ! \n\n");
//	totalStudent = i;
//	for (i = 0;i < totalStudent;i++)
//	{
//		total += score[i][1] ;
//		average += score[i][1]/(float)totalStudent;
//	}
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
//void DesendingScore()
//{
//	int i , j ;
//	int n ;
//	int temp1 ;
//	char temp[20];
//	for (i = 0;i < totalStudent ; i++)
//		for(j = i+1;j < totalStudent ; j++)
//			if(score[i][1]<score[j][1])
//				TransAndPut(i,j);
//	Print();
//}
//
//void AesendingScore()
//{
//	int i , j ;
//	int n ;
//	int temp1 ;
//	char temp[20];
//
//	for (i = 0;i < totalStudent ; i++)
//		for(j = i+1;j < totalStudent ; j++)
//			if(score[i][1]>score[j][1])
//				TransAndPut(i,j);
//	Print();
//}
//
//void AesendingNumber()
//{
//	int i , j ;
//	int temp1 ;
//	char temp[20];
//	int n;
//	for (i = 0;i < totalStudent ; i++)
//		for(j = i+1;j < totalStudent;j++)
//			if(score[i][0]>score[j][0])
//				TransAndPut(i,j);
//	Print();
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
//}
//
//void Dictionary()
//{
//	int i , j ;
//	int temp1 ;
//	int n;
//	char temp[20];
//
//	for(i = 0;i < totalStudent;i ++)
//		for(j = i+1;j < totalStudent;j ++)
//			if(strcmp(name[i],name[j]) > 0)
//				TransAndPut(i,j);
//	Print();
//}
//
//void SearchByNumber()
//{
//	int i ;
//	int search ;
//	printf("Enter student's number : ");
//	scanf("%d",&search);
//	for(i = 0;i < totalStudent ; i++)
//		if(score[i][0]==search)
//			printf("\n\nscore is %d\n\n",score[i][1]);
//}
//
//void SearchByName()
//{
//	int i ;
//	char temp[20] = {};
//	printf("\nEnter student's name : ");
//	for(i = 0;i < 20;i ++)
//	{
//		scanf("%c",&temp[i]);
//		if(temp[i] =='\n'&&i != 0)	break;
//	}
//	temp[0]=32;
//	temp[i]=32;
//	for(i = 0;i < totalStudent ; i++)
//		if(strcmp(temp,name[i])==0)
//			printf("score is %d\n\n",score[i][1]);
//}
//
//void ListRecord()
//{
//	int i ;
//	int n ;
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
//	char temp[20];
//	temp1=score[i][1];
//	score[i][1]=score[j][1];
//	score[j][1]=temp1;
//	temp1=score[i][0];
//	score[i][0]=score[j][0];
//	score[j][0]=temp1;
//	strcpy(temp,name[i]);
//	strcpy(name[i],name[j]);
//	strcpy(name[j],temp);
//}
//
//void Print()
//{
//	int i , n ;
//	printf("\n\n");
//	printf("Number    name    score\n");
//	printf("-----------------------\n");
//	for (i = 0;i < totalStudent;i ++)
//	{
//		printf("%-9d",score[i][0]);
//		for(n = 0;n < 20;n ++)
//		{
//			if(name[i][n]==0)	break;
//			printf("%c",name[i][n]);
//		}
//		printf("%5d\n",score[i][1]);
//	}
//	printf("\n");
//
//}