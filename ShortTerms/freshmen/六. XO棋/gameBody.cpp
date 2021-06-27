
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
		cout << "XO小游戏" << endl;
		cout << "1. 默认模式" << endl
			<< "2. 自定义地图大小" << endl
			<< "0. 退出游戏" << endl
			<< "请输入您的选择" << endl;
		cin >> choose;
		if (choose == 1 || choose == 2 || choose == 0)
			flag1 = 0;
		else flag1 = 1;
	} while (flag1);
	if (choose == 0) exit(0);
	int cinFlag = 1;
	if (choose == 2) {
		do {
			cout << "请输入地图大小" << endl;
			int size;
			cin >> size;
			if (size <= 0)
				cout << "输入地图大小有误，请重新输入" << endl;
			else { //输入合法
				init(size);
				cinFlag = 0;
			}
		} while (cinFlag);
	}
	do {
		cout << "请输入您使用的棋子类型（字母X/字母O）：";
		cin >> this->_playerType;
		if (this->_playerType == 'X') {
			this->_computerType = 'O';
			cinFlag = 0;
		} else if (this->_playerType == 'O') {
			this->_computerType = 'X';
			cinFlag = 0;
		} else {//输入不合法
			cout << "请在给出的大写字母X和大写字母O中选择：";
			cinFlag = 1;
		}
	} while (cinFlag);
	cinFlag = 0;
	do {
		cout << "请选择先下还是后下" << endl
			<< "1. 先手" << endl
			<< "2. 后手" << endl;
		cin >> this->_playerFirst;
		if (_playerFirst != 1 && _playerFirst != 2)
			cinFlag = 1;
		else cinFlag = 0;
	} while (cinFlag);
	system("cls");
	this->mainLoop(); //进入游戏主循环
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
		cout << "请输入你要下棋的横纵坐标,中间用空格隔开（如第 1 行第 2 列输入1 2 ）" << endl;
		int x, y;
		cin >> x >> y;
		if (x > _size || y > _size) {
			cout << "不能下在棋盘外面哦" << endl;
		}else if (this->gameMap[x - 1][y - 1] != '*') {
			cout << "该位置已经有棋子了，下在其他位置上吧" << endl;
		} else {
			this->gameMap[x - 1][y - 1] = _playerType;
			down = 0;
		}
	} while (down);
}

void gameBody::comutersTurn() {
	//寻找最长非空字符串
	//用其length计算权值
	//计算机：*10+5
	//用户： *10
	vector<Ranking> ranks;
	int i = 0, j = 0;
	char currChar;
	int currCol = 0, currRow = 0; //最近的*所在的位置
	int currLength = 1;
	int isComPiece = 0;
	for (i = 0; i < _size; i++) {//每一个横行
		for (j = 1; j < _size; j++) {
			if (gameMap[i][j] == '*') {
				currCol = i;
				currRow = j;
				if(gameMap[i][j - 1] == '*') continue;
			}
			if (gameMap[i][j] != gameMap[i][j - 1] || j == _size - 1) {
				//与上一个不相等或者到头了，检查并构造首部
				//构造可行位置
				if (gameMap[i][j] == '*') {
					//遇到了不一样的，是 *，构造这个位置
					if (gameMap[i][j - 1] == _computerType) isComPiece = 1; else isComPiece = 0;
					Ranking temp(i, j, currLength, isComPiece);
					ranks.push_back(temp);
				}
				if (gameMap[i][j] == gameMap[i][j - 1])  //只要和其前面的一样，就说明是到头了
					currLength++; //到头了 且 是一样的，length++，并且检查构造首部*
				//如果遇到了不一样的，length不用+，也检查并构造首部
				if (j == currRow + currLength) {
					//首部该位置可行
					//构造该连续子串首部位置
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
	for (j = 0; j < _size; j++) {//每一个纵行
		for (i = 1; i < _size; i++) { //从左到右
			if (gameMap[i][j] == '*') {
				currCol = i;
				currRow = j;
				if(gameMap[i - 1][j] == '*') continue;
			}
			if (gameMap[i][j] != gameMap[i - 1][j] || i == _size - 1) {
				//与上一个不相等或者到头了
				//构造可行位置
				if (gameMap[i][j] == '*') {
					if (gameMap[i - 1][j] == _computerType) isComPiece = 1; else isComPiece = 0;
					Ranking temp(i, j, currLength, isComPiece);
					ranks.push_back(temp);
				}
				if (gameMap[i][j] == gameMap[i - 1][j]) 
					currLength++;
				//检查该连续子串首部是否可行
				if (i == currCol + currLength) {
					//首部该位置可行
					//构造该连续子串首部位置
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

	//主对角线
	for (i = 1 , j = _size - 2; j >= 0; j--, i++) {
		if (gameMap[i][j] == '*') {
			currCol = i;
			currRow = j;
			if(gameMap[i - 1][j + 1] == '*') continue;
		}
		if (gameMap[i][j] != gameMap[i - 1][j + 1] || j == 0) {
			//与上一个不相等或者到头了
			//构造可行位置
			if (gameMap[i][j] == '*') {
				if (gameMap[i - 1][j + 1] == _computerType) isComPiece = 1; else isComPiece = 0;
				Ranking temp(i, j, currLength, isComPiece);
				ranks.push_back(temp);
			}
			if (gameMap[i][j] == gameMap[i - 1][j + 1]) 
				currLength++;
			if (j == _size - 1 - currRow - currLength) {
				//首部该位置可行
				//构造该连续子串首部位置
				if (gameMap[i - 1][j + 1] == _computerType) isComPiece = 1; else isComPiece = 0;
				Ranking temp(currCol, currRow, currLength, isComPiece);
				if (gameMap[currCol][currRow] == '*') ranks.push_back(temp);
				currCol = 0; currRow = 0;
			}
			currLength = 1;
		} else currLength++;
	}
	currLength = 1;

	//次对角线
	for (i = 1, j = 1; j < _size; j++, i++) {
		if (gameMap[i][j] == '*') {
			currCol = i;
			currRow = j;
			if(gameMap[i - 1][j - 1] == '*') continue;
		}
		if (gameMap[i][j] != gameMap[i - 1][j - 1] || j == _size - 1) {
			//与上一个不相等或者到头了
			//构造可行位置
			if (gameMap[i][j] == '*') {
				if (gameMap[i - 1][j - 1] == _computerType) isComPiece = 1;
				else isComPiece = 0;
				Ranking temp(i, j, currLength, isComPiece);
				ranks.push_back(temp);
			}
			if (gameMap[i][j] == gameMap[i - 1][j - 1]) 
				currLength++;
				//检查该连续子串首部是否可行
			if (j == currRow + currLength) {
				//首部该位置可行
				//构造该连续子串首部位置
				if (gameMap[i - 1][j - 1] == _computerType) isComPiece = 1; else isComPiece = 0;
				Ranking temp(currCol, currRow, currLength, isComPiece);
				if (gameMap[currCol][currRow] == '*') ranks.push_back(temp);
				currCol = 0; currRow = 0;
			}
			currLength = 1;
		} else currLength++;
	}
	//权值加载完毕
	//开始排序
	if (ranks.empty()) { //计算机先手
		srand(time(NULL));
		this->gameMap[rand() % _size][rand() % _size] = this->_computerType;
	} else {//其他情况
		sort(ranks.begin(), ranks.end());
		ranks.erase(unique(ranks.begin(), ranks.end()), ranks.end());
		//在权值相同的里面随机选择一个
		Ranking temp = ranks[0];
		int i;
		for (i = 0; i < ranks.size(); i++)
			if (ranks[i] != temp) break;
		i--;
		if(i >= 1)	this->gameMap[ranks[rand() % i].getCol()][ranks[rand() % i].getRow()] = this->_computerType;
		else this->gameMap[ranks[0].getCol()][ranks[0].getRow()] = this->_computerType;
	}
}

int gameBody::gameStatus() { //不进行输出
	int i, j;
	int num = 0, num1 = 0;
	for (i = 0; i < _size; i++) { //每一个横行
		num = count(gameMap[i], gameMap[i] + _size, _playerType);
		num1 = count(gameMap[i], gameMap[i] + _size, _computerType);
		if(num1 == _size) _playerWin = 0;
		if(num == _size) _playerWin = 1;
		if(num1 == _size || num == _size) return 0;
	}
	num = 0; num1 = 0;
	for (j = 0; j < _size; j++) { //每一个纵行
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
//主对角线
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
//次对角线
	for (i = 0, j = 0; j < _size; i++, j++) {
		if (gameMap[i][j] == _playerType)
			num++;
		if (gameMap[i][j] == _computerType)
			num1++;	
	}
	if (num1 == _size) _playerWin = 0;
	if (num == _size) _playerWin = 1;
	if (num1 == _size || num == _size) return 0;
//平局否
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
	cout << "游戏结束\n" << endl;
	if (this->_playerWin == 1) cout << "玩家胜利" << endl;
	else if (this->_playerWin == 0) cout << "计算机胜利" << endl;
	else cout << "平局" << endl;
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
