/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/12

Discription : 2048 Game

***********************/

#include"class2048.h"
#include<iostream>
using namespace std;

int main(){
	GameBody game;
	while (game.m_GameStatus == 0) {
		game.addCard();
		game.PrintMainBody();
		game.moveCard();
		game.IsOver();

		switch (game.m_GameStatus) 
		{
		case 1:
			system("cls");
			game.YouWin(); 
			break;
		case -1:
			system("cls");
			game.YouLose();
			system("pause");
			break;
		}

		system("cls");
	}
	return 0;
}