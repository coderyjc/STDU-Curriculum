//#include<stdio.h>
//#include<string.h>
//
//typedef struct candidate
//{
//	char name[20];
//	int score;
//
//}CANDIDATE;
//
//int main ()
//{
//	CANDIDATE can[3] = {"zhang",0,"li",0,"wang",0};
//	CANDIDATE temp;
//	char name1[20];
//	printf("Entre the candidate you prefer(zhang,wang,li) : \n");
//	for(int i = 1;i <= 10;i++)
//	{	
//		scanf("%s",name1);
//		for(int j = 0;j < 3;j++)
//			if(strcmp(name1,can[j].name) == 0)
//				can[j].score++;
//	}
//	printf("\nname	  score\n");
//	for(int i = 0;i < 3;i ++)
//		printf("%-10s%5d\n",can[i].name,can[i].score);
//	printf("\n");
//}