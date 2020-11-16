/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/12

Discription : 2048 Game

***********************/

#include<iostream>
#include<ctime>
#include<Windows.h>
#include"class2048.h"
using namespace std;

GameBody::GameBody(){
	this->m_GameStatus = 0;
	this->m_Score = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m_Layout[i][j] = 0;
}

void GameBody::PrintMainBody() {
	cout << "\t2048  V1.0 \n      Author : YanJC" << endl;
	for (int i = 0; i < 17; i++)
	{
		if (i % 4 == 0)
			for (int j = 0; j < 25; j++)
				cout << " ";
		else
			for (int j = 0; j < 5; j++){
				if (j == 4){
					cout << " ";
					break;
				}
				if (i % 2 == 0)
					cout << "   " << this->m_Layout[i / 4][j] << "  ";
				else
					cout << "      ";
			}
		cout << "\n";
	}
	cout << "\n\nTap �� �� �� �� to remove card \n\nTask : Create a 2048 card\n\n" << endl;
}

void GameBody::addCard() {
	if (!this->isFull())
		return;
	srand(time(NULL));
	int curCard = (rand() % 4 + 1) / 2 == 1 ? 2 : 4;
	int curCol, curRow, isInserted = 0;
	while (isInserted == 0) {
		curCol = rand() % 4 + 0;
		curRow = rand() % 4 + 0;
		if (this->m_Layout[curCol][curRow] == 0){
			this->m_Layout[curCol][curRow] = curCard;
			isInserted = 1;
		}
	}
}

void GameBody::moveCard() {
	system("pause");
	int upArrow = GetAsyncKeyState(VK_UP);
	int downArrow = GetAsyncKeyState(VK_DOWN);
	int leftArrow = GetAsyncKeyState(VK_LEFT);
	int rightArrow = GetAsyncKeyState(VK_RIGHT);
	if (upArrow != 0){
		for(int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j --) {
				if (this->m_Layout[j][i] == this->m_Layout[j - 1][i]) {
					this->m_Layout[j - 1][i] *= 2;
					this->m_Layout[j][i] = 0;
				}
				if (this->m_Layout[j][i] != 0 && this->m_Layout[j - 1][i] == 0) {
					this->m_Layout[j - 1][i] = this->m_Layout[j][i];
					this->m_Layout[j][i] = 0;
				}
			}
	}
	else if(downArrow != 0){
		for(int i = 0; i < 4; i ++)
			for (int j = 0; j < 3; j++) {
				if (this->m_Layout[j][i] == this->m_Layout[j + 1][i]) {
					this->m_Layout[j + 1][i] *= 2;
					this->m_Layout[j][i] = 0;
				}
				if (this->m_Layout[j][i] != 0 && this->m_Layout[j + 1][i] == 0) {
					this->m_Layout[j + 1][i] = this->m_Layout[j][i];
					this->m_Layout[j][i] = 0;
				}
			}
	}
	else if (leftArrow != 0) {
		for(int i = 0; i < 4; i++)
			for (int j = 3; j > 0; j--) {
				if (this->m_Layout[i][j] == this->m_Layout[i][j - 1]) {
					this->m_Layout[i][j - 1] *= 2;
					this->m_Layout[i][j] = 0;
				}
				if (this->m_Layout[i][j] != 0 && this->m_Layout[i][j - 1] == 0) {
					this->m_Layout[i][j - 1] = this->m_Layout[i][j];
					this->m_Layout[i][j] = 0;
				}
			}
	}
	else if (rightArrow != 0) {
		for(int i = 0; i < 4; i++)
			for (int j = 0; j < 3; j++) {
				if (this->m_Layout[i][j] == this->m_Layout[i][j + 1]) {
					this->m_Layout[i][j + 1] *= 2;
					this->m_Layout[i][j] = 0;
				}
				if (this->m_Layout[i][j] != 0 && this->m_Layout[i][j + 1] == 0) {
					this->m_Layout[i][j + 1] = this->m_Layout[i][j];
					this->m_Layout[i][j] = 0;
				}
			}
	}
}

void GameBody::IsOver() {
	int flag = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (this->m_Layout[i][j] == 2048)
				this->m_GameStatus = 1;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 3; j++) 
			if (this->m_Layout[i][j] == this->m_Layout[i][j + 1] || this->m_Layout[j][i] == this->m_Layout[j + 1][i])
				flag = 1;
	if (!flag)
		this->m_GameStatus = -1;
}

bool GameBody::isFull() {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			if (this->m_Layout[i][j] == 0)
				return 1;
	return 0;
}

void GameBody::YouLose() {
	cout << "��        ��    ��������      ��     ��" << endl;
	cout << "  ��    ��     ��      ��     ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��        ��     ��      ��     ��" << endl;
	cout << "     ��         ��������        ������\n\n\n" << endl;
	cout << "��         ��������      ��������    ��������    " << endl;
	cout << "��       ��       ��    ��            ��         " << endl;
	cout << "��       ��       ��    ��            ��        " << endl;
	cout << "��       ��       ��     ��������     ������   " << endl;
	cout << "��       ��       ��            ��    ��        " << endl;
	cout << "��       ��       ��            ��    ��        " << endl;
	cout << "��������   ��������      ��������     ��������   "<< endl;
}

void GameBody::YouWin() {
	cout << "��        ��    ��������      ��     ��" << endl;
	cout << "  ��    ��     ��      ��     ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��        ��     ��      ��     ��" << endl;
	cout << "     ��         ��������        ������\n\n\n" << endl;

	cout << "��      ��      ��   ������    ��          ��" << endl;
	cout << "��      ��      ��     ��      ����        ��" << endl;
	cout << "��      ��      ��     ��      ��  ��      ��" << endl;
	cout << "��      ��      ��     ��      ��    ��    ��" << endl;
	cout << " ��   ��  ��   ��      ��      ��      ��  ��" << endl;
	cout << "  ��  ��   �� ��       ��      ��        ����" << endl;
	cout << "    ��      ��       ������    ��          �� " << endl;
}