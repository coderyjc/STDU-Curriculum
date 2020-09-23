/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/15

Discription : 2048 Game

***********************/

#pragma once
#include"UserAndTime.h"
#include<vector>

/*

ATTENTION : 

	The detailed comments are in the function implementation section.
	The detailed comments are in the function implementation section.
	The detailed comments are in the function implementation section.

*/

class GameBody {
public:
	GameBody();
	
	void InitGame(); //init game when you play game again

	//simpleMode
	//parameter is difficulty degree : 128/256/512/2048 
	//is also a flag to judge pass or not
	void ClassicalMode(int difficulty); 

	//ARGUMENT is risk mode degree, it is size of the window
	//4*4 6*6 and 8*8
	void RiskMode(int ARGUMENT); 

	// Main menu
	//to select game mode and set theme.
	void PrintMainMenu(); 

	//when you choose classical menu, it will be called
	//thus you can select your classical mode: 128/256/512/2048
	void PrintClassicalMenu(); 

	//to choose risk menu
	//different degree represants different size of windows
	void PrintRiskMenu();

	//print the game surface
	void PrintMainGameBody(int ARGUMENT = 4); 

	//print your rank
	void PrintRank(); 

	//add card 2 or 4
	void addCard(int ARGUMENT = 4);

	//move card
	void moveCard(int ARGUMENT = 4); 

	//judge game status
	//ARGUMENT : 4/6/8
	//FLAG represents classical mode or risk mode
	void IsOver(int FLAG = -1, int ARGUMENT = 4); 

	//is it all 0 ?
	bool isFull(int ARGUMENT = 4); 

	void YouLose();// print "you failed" and save file
		
	void YouWin(); // print "you win" and save file

	void GameOver(); //print "game over" and save file

	//change the color of windows
	void changeColor(); 

	//read history record
	void readFile(); 

	//save information to save rank and sort all record
	void saveFile(); 

public:

	//to save all game records
	vector<GameRecord> m_Rank;

	int m_Score; //score of this round
	int m_GameStatus; //to judge game status
	int m_Layout[8][8]; //to save cards
	int m_MODE; //game mode

	int m_StartTime; //when you start this turn
	int m_EndTime; //when this turn finished

	//to save first card and next card to tell you the value of next card
	int m_FirstCard; 
	int m_NextCard;
};
