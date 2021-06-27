#pragma once
#include<vector>
#include<string>

class gameBody {
public:
	gameBody();
	~gameBody();

	void init(int size);
	void printMenu();
	void mainLoop();
	void updateMap();
	void comutersTurn();
	int gameStatus();
	void gameOver();
	void printMainBody();

private:
	
	char** gameMap;
	int _size;
	char _playerType;
	char _computerType;

	int _playerFirst;
	int _playerWin;
};