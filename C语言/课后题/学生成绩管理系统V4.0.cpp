//#include<stdio.h>
//#include<string.h>
//
//void inputrecord();
//void totalandaveragecourse();
//void totalandaveragestudent();
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
//float totalandaverage[6][2];
//float score[30][30];
//int level[6][5];
//int totalstudent;
//int total = 0;
//int subject;
//char name[30][20];
//float average = 0;
//
//int main ()
//{
//	int option = 1;
//	while(option > 0)
//	{
//		printf("student achievement management system v4.0\n");
//		printf("1.input record.\n");
//		printf("2.caculate total and average score of every course.\n");
//		printf("3.caculate total and average score of every student.\n");
//		printf("4.sort in descending order by total score of every student.\n");
//		printf("5.sort in ascending order by total score of every student.\n");
//		printf("6.sort in ascending order by number.\n");
//		printf("7.sort in dictionary order by name.\n");
//		printf("8.search by number.\n");
//		printf("9.search by name.\n");
//		printf("10.statistic anaylysis for every course.\n");
//		printf("11.list record.\n");
//		printf("0.exit.\n");
//		printf("please enter your option:");
//		scanf("%d",&option);
//		switch(option)
//		{
//		case 1 : inputrecord();				break ;
//		case 2 : totalandaveragecourse() ;	break ;
//		case 3 : totalandaveragestudent();	break ;
//		case 4 : desendingscore() ;			break ;
//		case 5 : aesendingscore() ;			break ;
//		case 6 : aesendingnumber() ;		break ;
//		case 7 : dictionary();				break ;
//		case 8 : searchbynumber() ;			break ;
//		case 9 : searchbyname();			break ;
//		case 10: statisticanaylysis();		break ;
//		case 11: listrecord();  			break ;
//		case 0 : return 0 ;					break ;
//		default : printf("Please enter a right number ! ") ; break ;
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
//	printf("Enter the whole subjects: ");
//	scanf("%d",&subject);
//	printf("\nplease input students' number,name and all scores : \n");
//
//	for (i = 0 ; i < 30 ; i ++)
//	{
//		control = 0 ;
//		scanf("%f",&score[i][0]);	// number
//		if(score[i][0]<0)
//		{
//			totalstudent = i ;
//			break;
//		}
//		for(j = 0;j < 20;j ++,control++)	//name
//		{
//			scanf("%c",&name[i][j]);
//			if(control==0)	continue;
//			if(name[i][j] ==' ')
//				break;
//		}
//		for(int k = 1;k <= subject;k ++)	//all scores
//		{
//			scanf("%f",&score[i][k]);
//			switch((int)score[i][k]/10)
//			{
//			case 1: level[k-1][4]++ ; break ;
//			case 2: level[k-1][4]++ ; break ;
//			case 3: level[k-1][4]++ ; break ;
//			case 4: level[k-1][4]++ ; break ;
//			case 5: level[k-1][4]++ ; break ;
//			case 6: level[k-1][3]++ ; break ;
//			case 7: level[k-1][2]++ ; break ;
//			case 8: level[k-1][1]++ ; break ;
//			case 9: level[k-1][0]++ ; break ;
//			case 10:level[k-1][0]++ ; break ;
//			}
//		}
//	}
//	printf("enter success !\n\n");
//	totalstudent = i;
//	for (i = 0;i < totalstudent;i++)
//	{
//		total += score[i][1];
//		average += score[i][1]/(float)totalstudent;
//	}
//}
//
//void totalandaveragecourse()
//{
//	for(int j = 0;j < subject;j ++)
//	{
//		for(int i = 0;i < totalstudent;i ++)
//		{
//			totalandaverage[j][0] += score[i][j+1];	//the first is total subject score.
//			totalandaverage[j][1] += score[i][j+1]/totalstudent;	//the second is subject average score.
//		}
//	}
//	printf("\n\nsubject        total          average\n");
//	printf("--------------------------------------\n");
//	for(int i = 0;i < subject;i ++)
//		printf("%-7d        %-10.1f %10.1f\n",i+1,totalandaverage[i][0],totalandaverage[i][1]);
//	printf("\n\n");
//}
//
//void totalandaveragestudent()
//{
//	for(int i = 0;i < totalstudent;i ++)
//	{
//		for(int j = 1;j <= subject;j ++)
//		{
//			score[i][subject+1] += score[i][j];	//the subject+1 is total subject score
//			score[i][subject+2] += score[i][j]/subject;	//the subject+2 is subject average score
//		}
//	}
//
//	printf("\n\nnumber        total          average\n");
//	printf("--------------------------------------\n");
//	for(int i = 0;i < totalstudent;i ++)
//		printf("%-8.1f %10.1f%18.1f\n",score[i][0],score[i][subject+1],score[i][subject+2]);
//	printf("\n\n");
//}
//
//void desendingscore()
//{
//	for (int i = 0;i < totalstudent ; i++)
//		for(int j = i+1;j < totalstudent ; j++)
//			if(score[i][subject+1]<score[j][subject+1])
//				transandput(i,j);
//	print();
//}
//
//void aesendingscore()
//{
//	for (int i = 0;i < totalstudent ; i++)
//		for(int j = i+1;j < totalstudent ; j++)
//			if(score[i][subject+1]>score[j][subject+1])
//				transandput(i,j);
//	print();
//}
//
//void aesendingnumber()
//{
//	for (int i = 0;i < totalstudent ; i++)
//		for(int j = i+1;j < totalstudent;j++)
//			if(score[i][0]>score[j][0])
//				transandput(i,j);
//	print();
//}
//
//void dictionary()
//{
//	for(int i = 0;i < totalstudent;i ++)
//		for(int j = i+1;j < totalstudent;j ++)
//			if(strcmp(name[i],name[j]) > 0)
//				transandput(i,j);
//	print();
//}
//
//void searchbynumber()
//{
//	for (int i = 0;i < totalstudent ; i++)
//		for(int j = i+1;j < totalstudent ; j++)
//			if(score[i][subject+1]<score[j][subject+1])
//				transandput(i,j);
//	int i;
//	int search;
//	printf("enter student's number : ");
//	scanf("%d",&search);
//	for(i = 0;i < totalstudent;i ++)
//		if(score[i][0]==search)
//		{
//			printf("\n\n");
//			puts(name[i]);
//			printf("His rank is : %d\n",i+1);
//			printf("His score is :\n");
//			for(int l = 0;l < subject;l ++)
//				printf("Subject.%d. %8.3f\n\n\n",l+1,score[i][l+1]);
//		}
//}
//
//void searchbyname()
//{
//	for (int i = 0;i < totalstudent ; i++)
//		for(int j = i+1;j < totalstudent ; j++)
//			if(score[i][subject+1]<score[j][subject+1])
//				transandput(i,j);
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
//		{
//			printf("\n\n");
//			puts(name[i]);
//			printf("His rank is : %d\n",i+1);
//			printf("His score is :\n");
//			for(int l = 0;l < subject;l ++)
//				printf("Subject.%d.%8.3f\n\n\n",l+1,score[i][l+1]);
//		}
//}
//
//void statisticanaylysis()
//{
//	for(int k = 0; k < subject;k ++)
//	{
//		printf("\nsubject.%d\n  level    number   rate\n",k+1);
//		printf("-----------------------\n");
//		for (int i = 0;i < 5;i ++)
//			printf("  %d        %d      %.3f\n",i+1,level[k][i],(float)level[k][i]/totalstudent);
//		printf("\n");
//	}
//}
//
//void listrecord()
//{
//	printf("\n");
//	printf("\n前两个为学号和姓名，倒数第一个为平均分，倒数第二个为总分\n\n");
//	for(int i = 0;i < totalstudent;i ++)
//	{
//		printf("%.0f  ",score[i][0]);
//		printf("%s",name[i]);
//		for(int j = 1;j <= subject+2;j ++)
//			printf("%.1f  ",score[i][j]);
//		printf("\n");
//	}
//	printf("\n\nsubject        total          average\n");
//	printf("--------------------------------------\n");
//	for(int i = 0;i < subject;i ++)
//		printf("%4.1d %15.1f %17.1f\n",i+1,totalandaverage[i][0],totalandaverage[i][1]);
//	printf("\n\n");
//}
//
//void transandput(int i,int j)
//{
//	int temp1;
//	char temp[20];
//	temp1=score[i][subject+1];
//	score[i][subject+1]=score[j][subject+1];
//	score[j][subject+1]=temp1;
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
//	printf("number    name    totalscore\n");
//	printf("----------------------------\n");
//	for (i = 0;i < totalstudent;i ++)
//	{
//		printf("%-10.0f",score[i][0]);
//		for(n = 0;n < 20;n ++)
//		{
//			if(name[i][n]==0)	break;
//			printf("%c",name[i][n]);
//		}
//		printf("%10.1f\n",score[i][subject+1]);
//	}
//	printf("\n\n");
//}
