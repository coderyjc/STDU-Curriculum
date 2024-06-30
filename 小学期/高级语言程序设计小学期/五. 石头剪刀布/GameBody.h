#pragma once
#include"Guess.h"
#include<iostream>
#include<cstdlib>
#include<deque>
using namespace std;

enum Types {
	STONE = 1,
	SCISSOR,
	CLOTH
};

enum WinORLose {
	LOSE = -1,
	DRAW,
	WIN
};

class GameBody {
public:
	
	GameBody() {
		computerWins = 0;
		playerWins = 0;
		draws = 0;
		totalTimes = 0;
	}

	int getNext(int last, int vec); //��ȡ��һ�г�ʲô
	int mainLoop(); //��Ϸ��ѭ��
	void showResults(); //������ͳ��

	void upDateGuess(int last, int zhis, int vec );

private:

	//--------------------BasicFunctions------------------

	string attackOption[4] = {"", "ʯͷ", "����", "��"};
	double computerWins;
	double playerWins;
	double draws;
	double totalTimes;
	 
	// ----------------AlgorithmFunctions-------------------
	 
	deque<Guess> late20Turns;
};