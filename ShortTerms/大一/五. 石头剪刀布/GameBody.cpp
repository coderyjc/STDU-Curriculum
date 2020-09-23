#include "GameBody.h"
#include<ctime>
#include<vector>

int GameBody::mainLoop() {
	cout << "猜拳游戏" << endl;
	int lastTurn = 0, vec = 0;
	for(int i = 0; ;i++){
		int inputRifht = 1;
		int choose;
		do {
			cout << "选择你的招式" << endl
				<< "1. 石头" << endl
				<< "2. 剪刀" << endl
				<< "3.  布" << endl
				<< "0. 结束" << endl
				<< "请输入：";
			cin >> choose;
			if (!choose) { this->showResults(); return 0; }
			if (choose < 0 || choose > 3) cout << "输入有误，请重新输入" << endl;
			else inputRifht = 0;
		} while (inputRifht);
		int computerNext;
		if(i != 0) computerNext = this->getNext(lastTurn, vec);
		else computerNext = rand() % 3 + 1;
		cout << "计算机出招为：" << this->attackOption[computerNext] << endl;
		this->totalTimes++;
		if (choose == STONE) {
			//玩家出石头
			switch (computerNext) {
			case STONE:
				//计算机石头
				draws++;
				cout << "平局" << endl;
				if (i) 
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = STONE;
				vec = DRAW;
				break;
			case SCISSOR:
				//计算机剪刀
				playerWins++;
				cout << "玩家胜" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = STONE;
				vec = WIN;
				break;
			case CLOTH:
				//计算机 布
				computerWins++;
				cout << "计算机胜" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = STONE;
				vec = LOSE;
				break;
			}
		} else if (choose == SCISSOR) {
			//玩家出剪刀
			switch (computerNext) {
			case STONE:
				//计算机石头
				computerWins++;
				cout << "计算机胜" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = SCISSOR;
				vec = LOSE;
				break;
			case SCISSOR:
				//计算机剪刀
				draws++;
				cout << "平局" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = SCISSOR;
				vec = DRAW;
				break;
			case CLOTH:
				//计算机 布
				playerWins++;
				cout << "玩家胜" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = SCISSOR;
				vec = WIN;
				break;
			}
		} else {
			//玩家出布
			switch (computerNext) {
			case STONE:
				//计算机石头
				playerWins++;
				cout << "玩家胜" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = CLOTH;
				vec = WIN;
				break;
			case SCISSOR:
				//计算机剪刀
				computerWins++;
				cout << "计算机胜" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
					lastTurn = CLOTH;
					vec = LOSE;
				break;
			case CLOTH:
				//计算机 布
				draws++;
				cout << "平局" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
					lastTurn = CLOTH;
					vec = DRAW;
				break;
			}
		}
		cout << endl;
	}while (1);
}

void GameBody::showResults() {
	cout << "游戏结束" << endl;
	cout << "合计游戏次数" << this->totalTimes << endl;
	cout << "计算机胜利次数：" << this->computerWins << endl
		<< "玩家胜利次数：" << this->playerWins << endl
		<< "平局次数：" << this->draws << endl
		<< "玩家胜率：" << this->playerWins / this->totalTimes << endl
		<< "电脑胜率：" << this->computerWins / this->totalTimes << endl;
}

void GameBody::upDateGuess(int last, int zhis, int vec) {
	Guess temp(last, zhis, vec);
	this->late20Turns.push_back(temp);
	if (this->late20Turns.size() == 21)
		this->late20Turns.pop_front();
}

int GameBody::getNext(int last, int vec) {
	srand(time(NULL));
	vector<int> statistic(4);
	statistic[STONE] = 0;
	statistic[SCISSOR] = 0;
	statistic[CLOTH] = 0;
	for (deque<Guess>::iterator it = late20Turns.begin(); it != late20Turns.end(); it++) {
		if ((*it).getLastTurn() == last && (*it).getWinOrLose() == vec) {
			statistic[(*it).getThisTurn()]++;
		}
	}
	int maxDir = 0;
	int flag1 = 10;
	int flag2 = 20;
	for (int i = 0; i < statistic.size(); i++)
		maxDir = statistic[maxDir] > statistic[i] ? maxDir : i;
	if (maxDir == STONE) { //extension
		flag1 = 8;
		flag2 = 16;
	} else if (maxDir == SCISSOR){
		flag1 = 14;
		flag2 = 22;
	} else if (maxDir == CLOTH) {
		flag1 = 8;
		flag2 = 22;
	} else;
	int randNum = rand() % 31 + 1;
	if (randNum < flag1) return STONE;
	if (randNum >= flag1&& randNum <= flag2) return SCISSOR;
	if (randNum > flag2) return CLOTH;
}