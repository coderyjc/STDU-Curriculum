/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/14

Discription : 2048 Game

***********************/

#include"class2048.h"
#include<Windows.h>
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;

//-----------------------------

GameBody::GameBody(){
	this->readFile();
	this->m_GameStatus = 0;
	this->m_Score = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m_Layout[i][j] = 0;
}

void GameBody::InitGame() {
	this->m_GameStatus = 0;
	this->m_Score = 0;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->m_Layout[i][j] = 0;
}

//------------------------------

void GameBody::SimpleMode()
{
	while (this->m_GameStatus == 0) {
		this->addCard();
		this->PrintMainBody();
		this->moveCard();
		this->IsOver();
		if (this->m_GameStatus == 1) {
			system("cls");
			this->YouWin();
			system("pause");
			return;
		}
		else if (this->m_GameStatus == -1) {
			system("cls");
			this->YouLose();
			system("pause");
			return;
		}
		system("cls");
	}
}

void GameBody::EndlessMode()
{
	while (this->m_GameStatus == 0) {
		this->addCard();
		this->PrintMainBody();
		this->moveCard();
		this->IsOver();
		if (this->m_GameStatus == -1) {
			system("cls");
			this->gameOver();
			system("pause");
		}
		system("cls");
	}
}

//--------------------------------

void GameBody::PrintMenu(){
	do {
		cout <<"**************" << endl
			<< "*  M E N U   *" << endl
			<< "* 2048  V1.2 *" << endl
			<< "**************" << endl
			<< "* 1. Simple  *" << endl
			<< "*------------*" << endl
			<< "* 2. Endless *" << endl
			<< "*------------*" << endl
			<< "* 3. Theme   *" << endl
			<< "*------------*" << endl
			<< "* 4. Rank    *" << endl
			<< "*------------*" << endl
			<< "* 0. Exit    *" << endl
			<< "**************" << endl;
		cout << "Your choice : ";
		int choose = 0;
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			this->SimpleMode(); 
			break;
		case 2:
			this->EndlessMode(); 
			break;
		case 3:
			this->changeColor(); 
			break;
		case 4:
			this->PrintRank(); 
			break;
		default: 
			exit(0);
		}
		system("cls");
	} while (1);
}

void GameBody::PrintMainBody() {
	cout << "\t2048  V1.2 \n      Author : YanJC" << endl;
	for (int i = 0; i < 17; i++)
	{
		if (i % 4 == 0)
			for (int j = 0; j < 24; j++)
				cout << "-";
		else
			for (int j = 0; j < 5; j++){
				if (j == 4){
					cout << "";
					break;
				}
				if (i % 2 == 0) {
					if (this->m_Layout[i / 4][j] == 0)
						cout << "      ";
					else
						cout << setw(6) << left << this->m_Layout[i / 4][j];
				}
				else
					cout << "     |";
			}
		cout << "\n";
	}
	cout << "Your score : " << this->m_Score << endl;
	cout << "\n\nTap �� �� �� �� to remove card." << endl;
}

void GameBody::PrintRank(){
	system("cls");
	cout << "\tR A N K\n\n    name\tscore" << endl;
	for (auto i : this->user.userAndScore) {
		if (i.second == 0)
		{
			cout << "\n  You haven't been in the game yet\n" << endl;
			continue;
		}
		cout << "    " << left << setw(10) << i.first
			 << "  " << i.second << endl;
	}
	cout << "You can clear your data if you tap 'Esc' " << endl;
	system("pause");
	int isEsc = 0;
	char choice;
	isEsc = GetAsyncKeyState(VK_ESCAPE);
	if (isEsc != 0) {
		cout << "Are you sure ? you will lose all your rank and it cannot be recovered!" << endl
			<< "The next time you open the game, your records will disappeared" << endl
			<< "enter Y/N : " << endl;
		cin >> choice; 
		if (choice == 'Y') {
			ofstream ofs;
			ofs.open("data.dat", ios::trunc);
			ofs.close();
		}
	}
}

//--------------------------------

void GameBody::addCard() {
	if (!this->isFull())
		return;
	srand((unsigned int)time(NULL));
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
					this->m_Layout[j - 1][i] *= 2; //combine
					this->m_Score += this->m_Layout[j - 1][i];  //add score
					this->m_Layout[j][i] = 0;
				}
				if (this->m_Layout[j][i] != 0 && this->m_Layout[j - 1][i] == 0) {
					// combine
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
					this->m_Score += this->m_Layout[j + 1][i]; //add score
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
					this->m_Score += this->m_Layout[i][j - 1]; //add score
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
					this->m_Score += this->m_Layout[i][j + 1]; //add score
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

//--------------------------------

void GameBody::changeColor(){
	cout << "Please select your theme : \n"
		<< "1. Geek's world." << endl
		<< "2. Misty morning." << endl
		<< "3. Bloody Mary" << endl
		<< "4. Blue Sky" << endl
		<< "0. Origin" << endl
		<< "Please enter you choice: " << endl;
	int choose;
	cin >> choose;
	switch (choose)
	{
	case 1: system("color 0A"); break;
	case 2: system("color 70"); break;
	case 3: system("color c0"); break;
	case 4: system("color b9"); break;
	case 0: system("color 07"); break;
	}
	system("cls");
	this->PrintMenu();
}

//--------------------------------

void GameBody::YouLose() {
	cout << "��        ��    ��������      ��     ��" << endl;
	cout << "  ��    ��     ��      ��     ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��        ��     ��      ��     ��" << endl;
	cout << "     ��         ��������        ������\n" << endl;
	cout << "\t\tFINAL SCORE : " << this->m_Score << endl << endl;
	cout << "��         ��������      ��������    ��������    " << endl;
	cout << "��       ��       ��    ��            ��         " << endl;
	cout << "��       ��       ��    ��            ��        " << endl;
	cout << "��       ��       ��     ��������     ������   " << endl;
	cout << "��       ��       ��            ��    ��        " << endl;
	cout << "��       ��       ��            ��    ��        " << endl;
	cout << "��������   ��������      ��������     ��������   " << endl;
	cout << "\n\n";
	this->saveFile();
	this->InitGame();
}

void GameBody::YouWin() {
	cout << "��        ��    ��������      ��     ��" << endl;
	cout << "  ��    ��     ��      ��     ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��       ��        ��    ��     ��" << endl;
	cout << "     ��        ��     ��      ��     ��" << endl;
	cout << "     ��         ��������        ������\n\n\n" << endl;
	cout << "\t\tFINAL SCORE : " << this->m_Score << endl << endl;
	cout << "��      ��      ��   ������    ��          ��" << endl;
	cout << "��      ��      ��     ��      ����        ��" << endl;
	cout << "��      ��      ��     ��      ��  ��      ��" << endl;
	cout << "��      ��      ��     ��      ��    ��    ��" << endl;
	cout << " ��   ��  ��   ��      ��      ��      ��  ��" << endl;
	cout << "  ��  ��   �� ��       ��      ��        ����" << endl;
	cout << "    ��      ��       ������    ��          �� " << endl;
	cout << "\n\n";
	this->saveFile();
	this->InitGame();
}

void GameBody::gameOver(){

	cout << "������������        ��       ��          ��     ����������" << endl
		<< "��                ��  ��    ����       ����     ��" << endl
		<< "��              ��      ��  ��  ��    ��  ��    ��" << endl
		<< "��    ��������  ����������  ��     ��     ��    ��������" << endl
		<< "��      �� ��   ��      ��  ��     ��     ��    ��" << endl
		<< "��     ��  ��   ��      ��  ��     ��     ��    ��" << endl
		<< " ��������  ��   ��      ��  ��     ��     ��    ����������" << endl << endl;
	cout << "\t\tFINAL-SCORE-" << this->m_Score << endl << endl;
	cout << " ��������    ��      ��   ��������    ��������             " << endl
		<< "��      ��   ��      ��   ��          ��      ��                 " << endl
		<< "��      ��    ��    ��    ��          ��     ��       " << endl
		<< "��      ��    ��    ��    ��������    ������    " << endl
		<< "��      ��     ��  ��     ��          ��   ��                " << endl
		<< "��      ��      ����      ��          ��    ��   " << endl
		<< " ��������        ��       ��������    ��     ��" << endl;
	cout << "\n\n";
	this->saveFile();
	this->InitGame();
}

//--------------------------------

void GameBody::readFile(){
	pair<string, int> cur;
	ifstream ifs;
	ifs.open("data.dat", ios::in);
	if (!ifs|| ifs.peek() == EOF) return;
	while (ifs.peek() != EOF) {
		ifs >> cur.first >> cur.second;
		this->user.userAndScore.push_back(cur);
	}
	for (int i = 0; i < this->user.userAndScore.size() - 1; i++) {
		if (this->user.userAndScore[i].second == 0)
			this->user.userAndScore.erase(this->user.userAndScore.begin() + i);
		if(this->user.userAndScore[i].second == this->user.userAndScore[i+1].second && this->user.userAndScore[i].first == this->user.userAndScore[i+1].first)
			this->user.userAndScore.erase(this->user.userAndScore.begin() + i);
	}
	ifs.close();

}

void GameBody::saveFile(){

class rank {
public:
	bool operator()(pair<string, int> p1, pair<string, int> p2) {
		return p1.second > p2.second;
	}
};

	cout << "Please enter your name to save your record:" << endl;
	pair<string, int> curr;
	cin >> curr.first;
	curr.second = this->m_Score;
	//if (this->user.userAndScore[0].second == 0)
		//user.userAndScore[0] = curr;
	//else
		this->user.userAndScore.push_back(curr);
	sort(this->user.userAndScore.begin(), this->user.userAndScore.end(), rank());

	//write files
	ofstream  ofs;
	ofs.open("data.dat", ios::binary | ios::trunc);
	for (auto i : this->user.userAndScore) {
		ofs << i.first << " " << i.second << endl;
	}
	ofs.close();
}
