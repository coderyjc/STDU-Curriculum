/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/15

Discription : 2048 Game

***********************/

#pragma once
#include<vector>
#include<iostream>

using namespace std;

// to show when you play the game
class PlayGameTime {
public:
	// reload the == operator
	bool operator==(PlayGameTime p) {
		if (this->m_Day == p.m_Day && this->m_Hour == p.m_Hour &&
			this->m_Minute == p.m_Minute && this->m_Minute && this->m_Month == p.m_Month
			&& this->m_Second == p.m_Second && this->m_Year == p.m_Year)
			return 1;
		else
			return 0;
	}

public:
	int m_Year;
	int m_Month;
	int m_Day;
	int m_Hour;
	int m_Minute;
	int m_Second;
};

class GameRecord {
public:
	// reload the == operator
	bool operator==(GameRecord g){
		if (this->m_GameTime == g.m_GameTime && this->m_Mode == g.m_Mode &&
			this->m_Name == g.m_Name && this->m_Score == g.m_Score
			&& this->m_Time == g.m_Time)
			return 1;
		else
			return 0;
	}

public:
	int m_Mode;
	// it is used to identify the mode when print rank
	// it is the first propety of the record

	string m_Name; // user name
	int m_Score; // the score of this turn
	int m_GameTime; // it shows how long you play the round
	PlayGameTime m_Time; //when you play the game
};
