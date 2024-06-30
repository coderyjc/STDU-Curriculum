//#include<stdio.h>
//int *Search(int *chengji);
//int main ()
//
//{
//	int score[3][4] = {65,45,78,98,65,68,65,98,76,45,65,98,};
//
//	for(int i = 0;i < 3;i ++)
//	{
//		int *pt ;
//		pt  = Search(score[i]);
//		if(pt == NULL)	continue;
//		else{
//			printf("Student %d :\n",i+1);
//			for(int i = 0;i < 4;i ++)
//				printf("%d  ",*(pt + i));
//			printf("\n");
//		}
//	}
//	return 0;	
//}
//int *Search(int *chengji)
//{
//	for(int i = 0;i < 4;i++)
//		if(*(chengji + i) < 60)
//			return chengji;
//	return NULL;
//}
