//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//
//int RandomNumber();
//int Guess();
//
//int randomNumber;
//int number[4];
//
//
//int main ()
//{	
//	randomNumber=RandomNumber();
//	Guess();
//	printf("Random number is %d.\n",randomNumber);
//}
//
//int RandomNumber()
//{
//	int count ;
//	int replace;
//	srand(time(NULL));
//	do{
//		randomNumber=rand()%9000 + 1000;
//		replace = randomNumber;
//		for(count = 0;count <4;count++)
//		{
//			number[count]=replace%10;
//			replace /= 10;
//		}
//	}while(number[0]==number[1]||number[0]==number[2]||number[0]==number[3]||number[1]==number[2]||number[1]==number[3]||number[2]==number[3]);
//
//	return randomNumber;
//}
//
//int Guess()
//{
//	int guess;
//	int count;
//	int Guess[4]={};
//	int x , y ;
//	int i , j ;
//	int time ;
//
//	for (time = 1;time<=10;time++)
//	{
//
//	printf("\nEnter the number you guess : ");
//	scanf("%d",&guess);
//
//	for(x = 0,count = 0;count <4;count++)
//	{
//		Guess[count] = guess%10;
//		guess /= 10;
//		if(Guess[count]==number[count])	x++;
//	}
//	for(y = 0,i = 0;i < 4;i++)
//		for(j = 0;j < 4;j++)
//			if(Guess[i]==number[j])
//				y++;
//
//	if (x==4&&y==4) {
//		printf("Congratulations !\n");
//		return 0;
//	}
//	else printf("%dA  %dB",x,y);
//
//	}
//
//	printf("\nSorry ! you heaven't guess the right number ! \n ");
//
//}
