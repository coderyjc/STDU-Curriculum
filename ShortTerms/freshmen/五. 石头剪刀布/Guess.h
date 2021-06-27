#pragma once

enum Types {
	STONE = 1,
	SCISSOR,
	CLOTH
};

enum WinORLose {
	LOSE = -1,
	DRAW,
};

class Guess {
public:
	Guess(int l = 0, int t = 0, int v = 0) : lastTurn(l), thisTurn(t), vecOrLose(v) {}

	int getLastTurn() { return this->lastTurn; }
	int getThisTurn() { return this->thisTurn; }
	int getWinOrLose() { return this->vecOrLose; }

private:
	int lastTurn;
	int thisTurn;
	int vecOrLose;
};
