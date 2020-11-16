/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/14

Discription : 2048 Game

***********************/

#pragma once
#include"User.h"
class GameBody {
public:
	GameBody();

	//---------------
	
	void InitGame(); //init game when you play game again

	void ClassicalMode(int difficulty); //simpleMode

	void RiskMode(int ARGUMENT); //endless

	//----------------

	void PrintMainMenu(); //menu

	void PrintClassicalMenu(); //classical menu

	void PrintRiskMenu(); //risk menu

	void PrintMainGameBody(int ARGUMENT = 4); //print the surface

	void PrintRank(); //print your rank

	//----------------

	void addCard(int ARGUMENT = 4); //add card 2 or 4

	void moveCard(int ARGUMENT = 4); //move card

	void IsOver(int FLAG = -1, int ARGUMENT = 4); //judge status

	bool isFull(int ARGUMENT = 4); //is it all 0 ?

	//-----------------------------------

	void YouLose();// print you failed
		
	void YouWin(); // print you win

	void gameOver(); //endlessmode game over

	void changeColor(); //change the color of windows

	//--------------------------------

	void readFile(); //read history record

	void saveFile(); //save information to save rank;

public:
	User user;
	int m_Score;
	int m_GameStatus;
	int m_Layout[8][8];

	int m_FirstCard;
	int m_NextCard;
};
