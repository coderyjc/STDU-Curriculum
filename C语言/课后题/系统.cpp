//#include<stdio.h>
//#include<string.h>
//
//void inputrecord();
//void totalandaverage();
//void desendingscore();
//void aesendingscore();
//void aesendingnumber();
//void dictionary();
//void searchbynumber();
//void searchbyname();
//void statisticanaylysis();
//void listrecord();
//void transandput(int i,int j);
//void print();
//
//int score[30][2];
//char name[30][20]={};
//int level[5];
//int totalstudent;
//int total = 0;
//float average = 0;
//
//int main ()
//{
//	int option = 1;
//	while(option > 0)
//	{
//		printf("student achievement management system v3.0\n");
//		printf("1.input record.\n");
//		printf("2.caculate total and average score of course.\n");
//		printf("3.sort in descending order by score.\n");
//		printf("4.sort in ascending order by score.\n");
//		printf("5.sort in ascending order by number.\n");
//		printf("6.sort by dictionary order by name.\n");
//		printf("7.search by number.\n");
//		printf("8.search by name.\n");
//		printf("9.statistic anaylysis.\n");
//		printf("10.list record.\n");
//		printf("0.exit.\n");
//		printf("please enter your option:");
//		scanf("%d",&option);
//		switch(option)
//		{
//		case 1 : inputrecord();			break ;
//		case 2 : totalandaverage() ;	break ;
//		case 3 : desendingscore() ;		break ;
//		case 4 : aesendingscore() ;		break ;
//		case 5 : aesendingnumber() ;	break ;
//		case 6 : dictionary();			break ;
//		case 7 : searchbynumber() ;		break ;
//		case 8 : searchbyname();		break ;
//		case 9 : statisticanaylysis();  break ;
//		case 10:listrecord();  			break ;
//		case 0 : return 0 ;				break ;
//		default : printf("please enter a right number ! ") ; break ;
//		}
//	}
//	return 0 ;
//}
//
//void inputrecord()
//{
//	int i ;
//	char c;
//	int j ;
//	int control;
//
//	printf("1.input record.\n");
//	printf("\nplease input students' number,name and record : \n");
//
//	for (i = 0 ; i < 30 ; i ++)
//	{
//		control = 0 ;
//		scanf("%d",&score[i][0]);
//		if(score[i][0]<0)
//		{
//			totalstudent = i ;
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
//	printf("enter success ! \n\n");
//	totalstudent = i;
//	for (i = 0;i < totalstudent;i++)
//	{
//		total += score[i][1] ;
//		average += score[i][1]/(float)totalstudent;
//	}
//}
//
//void totalandaverage()
//{
//	int i ;
//	printf("\ncaculate total and average score of course.\n\n");
//	printf("-----------------------------\n");
//	printf("their total score is:%-5.2d.\n",total);
//	printf("their average score is:%-5.2f.\n",average);
//	printf("-----------------------------\n");
//	main();
//}
//
//void desendingscore()
//{
//	int i , j ;
//	int n ;
//	int temp1 ;
//	char temp[20];
//	for (i = 0;i < totalstudent ; i++)
//		for(j = i+1;j < totalstudent ; j++)
//			if(score[i][1]<score[j][1])
//				transandput(i,j);
//	print();
//}
//
//void aesendingscore()
//{
//	int i , j ;
//	int n ;
//	int temp1 ;
//	char temp[20];
//
//	for (i = 0;i < totalstudent ; i++)
//		for(j = i+1;j < totalstudent ; j++)
//			if(score[i][1]>score[j][1])
//				transandput(i,j);
//	print();
//}
//
//void aesendingnumber()
//{
//	int i , j ;
//	int temp1 ;
//	char temp[20];
//	int n;
//	for (i = 0;i < totalstudent ; i++)
//		for(j = i+1;j < totalstudent;j++)
//			if(score[i][0]>score[j][0])
//				transandput(i,j);
//	print();
//}
//
//void statisticanaylysis()
//{
//	int i ;
//	printf("   statisticanaylysis   \n\n");
//	printf("level    number   rate\n");
//	printf("-----------------------\n");
//	for (i = 0;i < 5;i ++)
//		printf("  %d        %d      %.3f\n",i+1,level[i],(float)level[i]/totalstudent);
//}
//
//void dictionary()
//{
//	int i , j ;
//	int temp1 ;
//	int n;
//	char temp[20];
//
//	for(i = 0;i < totalstudent;i ++)
//		for(j = i+1;j < totalstudent;j ++)
//			if(strcmp(name[i],name[j]) > 0)
//				transandput(i,j);
//	print();
//}
//
//void searchbynumber()
//{
//	int i ;
//	int search ;
//	printf("enter student's number : ");
//	scanf("%d",&search);
//	for(i = 0;i < totalstudent ; i++)
//		if(score[i][0]==search)
//			printf("\n\nscore is %d\n\n",score[i][1]);
//}
//
//void searchbyname()
//{
//	int i ;
//	char temp[20] = {};
//	printf("\nenter student's name : ");
//	for(i = 0;i < 20;i ++)
//	{
//		scanf("%c",&temp[i]);
//		if(temp[i] =='\n'&&i != 0)	break;
//	}
//	temp[0]=32;
//	temp[i]=32;
//	for(i = 0;i < totalstudent ; i++)
//		if(strcmp(temp,name[i])==0)
//			printf("score is %d\n\n",score[i][1]);
//}
//
//void listrecord()
//{
//	int i ;
//	int n ;
//	print();
//	printf("\n");
//	printf("-----------------------------\n");
//	printf("their total score is:%-5.2d.\n",total);
//	printf("their average score is:%-5.2f.\n",average);
//	printf("-----------------------------\n");
//}
//
//void transandput(int i,int j)
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
//void print()
//{
//	int i , n ;
//	printf("\n\n");
//	printf("number    name    score\n");
//	printf("-----------------------\n");
//	for (i = 0;i < totalstudent;i ++)
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