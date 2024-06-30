
#include "gameBody.h"
#include"Ranking.h"
#include<ctime>
#include<cstdlib>
#include<algorithm>
#include<iostream>
using namespace std;

gameBody::gameBody() {
	init(3);
}

gameBody::~gameBody() {
	for (int i = 0; i < _size; i++) 
		delete[] gameMap[i];
	delete[] gameMap;
}

void gameBody::init(int size) {
	_playerFirst = 0;
	_playerWin = 0;
	this->_size = size;
	gameMap = new char* [_size];
	for(int i = 0; i < _size; i++)
		gameMap[i] = new char[size];
	for (int i = 0; i < size; i++)
		for(int j = 0; j < _size; j++)
			gameMap[i][j] = '*';
	this->_computerType = 'X';
	this->_playerType = 'X';
}

void gameBody::printMenu() {
	int flag1 = 1;
	int choose;
	do {
		cout << "XOС��Ϸ" << endl;
		cout << "1. Ĭ��ģʽ" << endl
			<< "2. �Զ����ͼ��С" << endl
			<< "0. �˳���Ϸ" << endl
			<< "����������ѡ��" << endl;
		cin >> choose;
		if (choose == 1 || choose == 2 || choose == 0)
			flag1 = 0;
		else flag1 = 1;
	} while (flag1);
	if (choose == 0) exit(0);
	int cinFlag = 1;
	if (choose == 2) {
		do {
			cout << "�������ͼ��С" << endl;
			int size;
			cin >> size;
			if (size <= 0)
				cout << "�����ͼ��С��������������" << endl;
			else { //����Ϸ�
				init(size);
				cinFlag = 0;
			}
		} while (cinFlag);
	}
	do {
		cout << "��������ʹ�õ��������ͣ���ĸX/��ĸO����";
		cin >> this->_playerType;
		if (this->_playerType == 'X') {
			this->_computerType = 'O';
			cinFlag = 0;
		} else if (this->_playerType == 'O') {
			this->_computerType = 'X';
			cinFlag = 0;
		} else {//���벻�Ϸ�
			cout << "���ڸ����Ĵ�д��ĸX�ʹ�д��ĸO��ѡ��";
			cinFlag = 1;
		}
	} while (cinFlag);
	cinFlag = 0;
	do {
		cout << "��ѡ�����»��Ǻ���" << endl
			<< "1. ����" << endl
			<< "2. ����" << endl;
		cin >> this->_playerFirst;
		if (_playerFirst != 1 && _playerFirst != 2)
			cinFlag = 1;
		else cinFlag = 0;
	} while (cinFlag);
	system("cls");
	this->mainLoop(); //������Ϸ��ѭ��
}

void gameBody::mainLoop() {
	do {
		this->printMainBody();
		this->updateMap();
		if (this->gameStatus() == 0) break;
		this->comutersTurn();
		system("cls");
	} while (this->gameStatus());
	this->gameOver();
}

void gameBody::updateMap() {
	int down = 1;
	if (this->_playerFirst == 2) {
		this->comutersTurn();
		system("cls");
		this->printMainBody();
		this->_playerFirst = -1;
	}
	do {
		cout << "��������Ҫ����ĺ�������,�м��ÿո��������� 1 �е� 2 ������1 2 ��" << endl;
		int x, y;
		cin >> x >> y;
		if (x > _size || y > _size) {
			cout << "����������������Ŷ" << endl;
		}else if (this->gameMap[x - 1][y - 1] != '*') {
			cout << "��λ���Ѿ��������ˣ���������λ���ϰ�" << endl;
		} else {
			this->gameMap[x - 1][y - 1] = _playerType;
			down = 0;
		}
	} while (down);
}

void gameBody::comutersTurn() {
	//Ѱ����ǿ��ַ���
	//����length����Ȩֵ
	//�������*10+5
	//�û��� *10
	vector<Ranking> ranks;
	int i = 0, j = 0;
	char currChar;
	int currCol = 0, currRow = 0; //�����*���ڵ�λ��
	int currLength = 1;
	int isComPiece = 0;
	for (i = 0; i < _size; i++) {//ÿһ������
		for (j = 1; j < _size; j++) {
			if (gameMap[i][j] == '*') {
				currCol = i;
				currRow = j;
				if(gameMap[i][j - 1] == '*') continue;
			}
			if (gameMap[i][j] != gameMap[i][j - 1] || j == _size - 1) {
				//����һ������Ȼ��ߵ�ͷ�ˣ���鲢�����ײ�
				//�������λ��
				if (gameMap[i][j] == '*') {
					//�����˲�һ���ģ��� *���������λ��
					if (gameMap[i][j - 1] == _computerType) isComPiece = 1; else isComPiece = 0;
					Ranking temp(i, j, currLength, isComPiece);
					ranks.push_back(temp);
				}
				if (gameMap[i][j] == gameMap[i][j - 1])  //ֻҪ����ǰ���һ������˵���ǵ�ͷ��
					currLength++; //��ͷ�� �� ��һ���ģ�length++�����Ҽ�鹹���ײ�*
				//��������˲�һ���ģ�length����+��Ҳ��鲢�����ײ�
				if (j == currRow + currLength) {
					//�ײ���λ�ÿ���
					//����������Ӵ��ײ�λ��
					if (gameMap[i][j - 1] == _computerType) isComPiece = 1; else isComPiece = 0;
					Ranking temp(currCol, currRow, currLength, isComPiece);
					if(gameMap[currCol][currRow] == '*') ranks.push_back(temp);
					currCol = 0; currRow = 0;
				} 
				currLength = 1;
			}
			else
				currLength++;
		}
	}

	currLength = 1;
	for (j = 0; j < _size; j++) {//ÿһ������
		for (i = 1; i < _size; i++) { //������
			if (gameMap[i][j] == '*') {
				currCol = i;
				currRow = j;
				if(gameMap[i - 1][j] == '*') continue;
			}
			if (gameMap[i][j] != gameMap[i - 1][j] || i == _size - 1) {
				//����һ������Ȼ��ߵ�ͷ��
				//�������λ��
				if (gameMap[i][j] == '*') {
					if (gameMap[i - 1][j] == _computerType) isComPiece = 1; else isComPiece = 0;
					Ranking temp(i, j, currLength, isComPiece);
					ranks.push_back(temp);
				}
				if (gameMap[i][j] == gameMap[i - 1][j]) 
					currLength++;
				//���������Ӵ��ײ��Ƿ����
				if (i == currCol + currLength) {
					//�ײ���λ�ÿ���
					//����������Ӵ��ײ�λ��
					if (gameMap[i - 1][j] == _computerType) isComPiece = 1; else isComPiece = 0;
					Ranking temp(currCol, currRow, currLength, isComPiece);
					if (gameMap[currCol][currRow] == '*') ranks.push_back(temp);
					currCol = 0; currRow = 0;
				}
				currLength = 1;
			} else currLength++;
		}
	}
	currLength = 1;

	//���Խ���
	for (i = 1 , j = _size - 2; j >= 0; j--, i++) {
		if (gameMap[i][j] == '*') {
			currCol = i;
			currRow = j;
			if(gameMap[i - 1][j + 1] == '*') continue;
		}
		if (gameMap[i][j] != gameMap[i - 1][j + 1] || j == 0) {
			//����һ������Ȼ��ߵ�ͷ��
			//�������λ��
			if (gameMap[i][j] == '*') {
				if (gameMap[i - 1][j + 1] == _computerType) isComPiece = 1; else isComPiece = 0;
				Ranking temp(i, j, currLength, isComPiece);
				ranks.push_back(temp);
			}
			if (gameMap[i][j] == gameMap[i - 1][j + 1]) 
				currLength++;
			if (j == _size - 1 - currRow - currLength) {
				//�ײ���λ�ÿ���
				//����������Ӵ��ײ�λ��
				if (gameMap[i - 1][j + 1] == _computerType) isComPiece = 1; else isComPiece = 0;
				Ranking temp(currCol, currRow, currLength, isComPiece);
				if (gameMap[currCol][currRow] == '*') ranks.push_back(temp);
				currCol = 0; currRow = 0;
			}
			currLength = 1;
		} else currLength++;
	}
	currLength = 1;

	//�ζԽ���
	for (i = 1, j = 1; j < _size; j++, i++) {
		if (gameMap[i][j] == '*') {
			currCol = i;
			currRow = j;
			if(gameMap[i - 1][j - 1] == '*') continue;
		}
		if (gameMap[i][j] != gameMap[i - 1][j - 1] || j == _size - 1) {
			//����һ������Ȼ��ߵ�ͷ��
			//�������λ��
			if (gameMap[i][j] == '*') {
				if (gameMap[i - 1][j - 1] == _computerType) isComPiece = 1;
				else isComPiece = 0;
				Ranking temp(i, j, currLength, isComPiece);
				ranks.push_back(temp);
			}
			if (gameMap[i][j] == gameMap[i - 1][j - 1]) 
				currLength++;
				//���������Ӵ��ײ��Ƿ����
			if (j == currRow + currLength) {
				//�ײ���λ�ÿ���
				//����������Ӵ��ײ�λ��
				if (gameMap[i - 1][j - 1] == _computerType) isComPiece = 1; else isComPiece = 0;
				Ranking temp(currCol, currRow, currLength, isComPiece);
				if (gameMap[currCol][currRow] == '*') ranks.push_back(temp);
				currCol = 0; currRow = 0;
			}
			currLength = 1;
		} else currLength++;
	}
	//Ȩֵ�������
	//��ʼ����
	if (ranks.empty()) { //���������
		srand(time(NULL));
		this->gameMap[rand() % _size][rand() % _size] = this->_computerType;
	} else {//�������
		sort(ranks.begin(), ranks.end());
		ranks.erase(unique(ranks.begin(), ranks.end()), ranks.end());
		//��Ȩֵ��ͬ���������ѡ��һ��
		Ranking temp = ranks[0];
		int i;
		for (i = 0; i < ranks.size(); i++)
			if (ranks[i] != temp) break;
		i--;
		if(i >= 1)	this->gameMap[ranks[rand() % i].getCol()][ranks[rand() % i].getRow()] = this->_computerType;
		else this->gameMap[ranks[0].getCol()][ranks[0].getRow()] = this->_computerType;
	}
}

int gameBody::gameStatus() { //���������
	int i, j;
	int num = 0, num1 = 0;
	for (i = 0; i < _size; i++) { //ÿһ������
		num = count(gameMap[i], gameMap[i] + _size, _playerType);
		num1 = count(gameMap[i], gameMap[i] + _size, _computerType);
		if(num1 == _size) _playerWin = 0;
		if(num == _size) _playerWin = 1;
		if(num1 == _size || num == _size) return 0;
	}
	num = 0; num1 = 0;
	for (j = 0; j < _size; j++) { //ÿһ������
		for (i = 0; i < _size; i++) {
			if (gameMap[i][j] == _playerType)
				num++;
			if (gameMap[i][j] == _computerType)
				num1++;
		}
		if (num1 == _size) _playerWin = 0;
		if (num == _size) _playerWin = 1;
		if (num1 == _size || num == _size) return 0;
		num = 0; num1 = 0;
	}
	num = 0; num1 = 0;
//���Խ���
	for (i = 0, j = _size - 1; j >= 0; i++, j--) {
		if (gameMap[i][j] == _playerType)
			num++;
		if (gameMap[i][j] == _computerType)
			num1++;
	}
	if (num1 == _size) _playerWin = 0;
	if (num == _size) _playerWin = 1;
	if (num1 == _size || num == _size) return 0;
	num1 = 0; num = 0;
//�ζԽ���
	for (i = 0, j = 0; j < _size; i++, j++) {
		if (gameMap[i][j] == _playerType)
			num++;
		if (gameMap[i][j] == _computerType)
			num1++;	
	}
	if (num1 == _size) _playerWin = 0;
	if (num == _size) _playerWin = 1;
	if (num1 == _size || num == _size) return 0;
//ƽ�ַ�
	int flag = 0;
	for (int i = 0; i < _size; i++)
		flag += count(gameMap[i], gameMap[i] + _size, '*');
	if (!flag) {
		_playerWin = -1;
		return 0;
	}
	return 1;
}

void gameBody::gameOver() {
	system("cls");
	this->printMainBody();
	cout << endl;
	cout << "��Ϸ����\n" << endl;
	if (this->_playerWin == 1) cout << "���ʤ��" << endl;
	else if (this->_playerWin == 0) cout << "�����ʤ��" << endl;
	else cout << "ƽ��" << endl;
}

void gameBody::printMainBody() {
	int i, j, k;
	for (i = 0; i < _size * 3; i++) cout << "-";
	cout << endl;
	for (i = 0; i < _size; i++) {
		for (j = 0; j < _size; j++)
			cout << " " << gameMap[i][j] << " ";
		cout << endl;
		for (k = 0; k < _size * 3; k++)
			cout << "-";
		cout << endl;
	}
}
