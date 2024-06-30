//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//#include<time.h>
//
//typedef struct card
//{
//	char suit[10];
//	char face[10];
//}CARD;
//
//int main()
//{
//	CARD card[52] = 
//	{
//		"Spades","A","Spades","2","Spades","3",
//		"Spades","4","Spades","5","Spades","6",
//		"Spades","7","Spades","8","Spades","9",
//		"Spades","10","Spades","Jack",
//		"Spades","Queen","Spades","King",
//		"Hearts","A","Hearts","2","Hearts","3",
//		"Hearts","4","Hearts","5","Hearts","6",
//		"Hearts","7","Hearts","8","Hearts","9",
//		"Hearts","10","Hearts","Jack",
//		"Hearts","Queen","Hearts","King",
//		"Clubs","A","Clubs","2","Clubs","3",
//		"Clubs","4","Clubs","5","Clubs","6",
//		"Clubs","7","Clubs","8","Clubs","9",
//		"Clubs","10","Clubs","Jack",
//		"Clubs","Queen","Clubs","King",
//		"Diamonds","A","Diamonds","2","Diamonds","3",
//		"Diamonds","4","Diamonds","5","Diamonds","6",
//		"Diamonds","7","Diamonds","8","Diamonds","9",
//		"Diamonds","10","Diamonds","Jack",
//		"Diamonds","Queen","Diamonds","King"
//	};
//
//
//	printf("Before shuffling:\n");
//	for(int i = 0;i < 52;i ++)
//	{
//		if(i % 4 == 0)
//			printf("\n");
//		printf("%s %s	",card[i].suit,card[i].face);
//	}
//	printf("\n\nAfter shuffling:\n");
//
//	CARD temp;
//	srand(time(NULL));
//	int a, b;
//
//	for(int i = 0;i < 1000;i ++)
//	{
//		a = rand()%52;
//		b = rand()%52;
//		temp = card[a];
//		card[a] = card[b];
//		card[b] = temp;
//	}
//
//	for(int i = 0;i < 52;i ++)
//	{
//		if(i % 4 == 0)
//			printf("\n");
//		printf("%s %s	",card[i].suit,card[i].face);
//	}
//	return 0;
//}