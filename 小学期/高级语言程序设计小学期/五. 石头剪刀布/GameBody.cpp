#include "GameBody.h"
#include<ctime>
#include<vector>

int GameBody::mainLoop() {
	cout << "��ȭ��Ϸ" << endl;
	int lastTurn = 0, vec = 0;
	for(int i = 0; ;i++){
		int inputRifht = 1;
		int choose;
		do {
			cout << "ѡ�������ʽ" << endl
				<< "1. ʯͷ" << endl
				<< "2. ����" << endl
				<< "3.  ��" << endl
				<< "0. ����" << endl
				<< "�����룺";
			cin >> choose;
			if (!choose) { this->showResults(); return 0; }
			if (choose < 0 || choose > 3) cout << "������������������" << endl;
			else inputRifht = 0;
		} while (inputRifht);
		int computerNext;
		if(i != 0) computerNext = this->getNext(lastTurn, vec);
		else computerNext = rand() % 3 + 1;
		cout << "���������Ϊ��" << this->attackOption[computerNext] << endl;
		this->totalTimes++;
		if (choose == STONE) {
			//��ҳ�ʯͷ
			switch (computerNext) {
			case STONE:
				//�����ʯͷ
				draws++;
				cout << "ƽ��" << endl;
				if (i) 
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = STONE;
				vec = DRAW;
				break;
			case SCISSOR:
				//���������
				playerWins++;
				cout << "���ʤ" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = STONE;
				vec = WIN;
				break;
			case CLOTH:
				//����� ��
				computerWins++;
				cout << "�����ʤ" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = STONE;
				vec = LOSE;
				break;
			}
		} else if (choose == SCISSOR) {
			//��ҳ�����
			switch (computerNext) {
			case STONE:
				//�����ʯͷ
				computerWins++;
				cout << "�����ʤ" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = SCISSOR;
				vec = LOSE;
				break;
			case SCISSOR:
				//���������
				draws++;
				cout << "ƽ��" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = SCISSOR;
				vec = DRAW;
				break;
			case CLOTH:
				//����� ��
				playerWins++;
				cout << "���ʤ" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = SCISSOR;
				vec = WIN;
				break;
			}
		} else {
			//��ҳ���
			switch (computerNext) {
			case STONE:
				//�����ʯͷ
				playerWins++;
				cout << "���ʤ" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
				lastTurn = CLOTH;
				vec = WIN;
				break;
			case SCISSOR:
				//���������
				computerWins++;
				cout << "�����ʤ" << endl;
				if (i)
					this->upDateGuess(lastTurn, choose, vec);
					lastTurn = CLOTH;
					vec = LOSE;
				break;
			case CLOTH:
				//����� ��
				draws++;
				cout << "ƽ��" << endl;
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
	cout << "��Ϸ����" << endl;
	cout << "�ϼ���Ϸ����" << this->totalTimes << endl;
	cout << "�����ʤ��������" << this->computerWins << endl
		<< "���ʤ��������" << this->playerWins << endl
		<< "ƽ�ִ�����" << this->draws << endl
		<< "���ʤ�ʣ�" << this->playerWins / this->totalTimes << endl
		<< "����ʤ�ʣ�" << this->computerWins / this->totalTimes << endl;
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