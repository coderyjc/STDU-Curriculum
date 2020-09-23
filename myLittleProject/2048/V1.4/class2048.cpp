/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/15

Discription : 2048 Game

***********************/

#include"defination.h"
#include"class2048.h"
#include<Windows.h>
#include<algorithm>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
#include<ctime>

using namespace std;


/**************************************

	ClassName : sortScoreRank

	Purpose : As an affine to compare record:
				Arrange the modes in ascending order
				when modes is the same , arrannge the score in decending order

***************************************/

class sortScoreRank {

public:
	bool operator()(GameRecord g1, GameRecord g2) {
		if (g1.m_Mode != g1.m_Mode)
			return g1.m_Mode < g2.m_Mode;
		else
			return g1.m_Score > g2.m_Score;
	}
};


/**************************************

	FunctionName : GameBody

	Purpose : Initialized the class we creates in main function

***************************************/

GameBody::GameBody(){
	this->readFile(); //get all records to order them when game over
	this->m_GameStatus = 0;
	this->m_Score = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			this->m_Layout[i][j] = 0;
	this->m_FirstCard = (rand() % 4) / 2 == 1 ? 2 : 4; //add the first card

	// to save the time when game begin and end
	this->m_StartTime = 0;
	this->m_EndTime = 0;
}


/**************************************

	FunctionName : InitGame

	Purpose : When you finish a round, the last data will not be initialized 
			  automatically, so we create a function to re-initialize the data

***************************************/

void GameBody::InitGame() {
	this->m_GameStatus = 0;
	this->m_Score = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			this->m_Layout[i][j] = 0;
	this->m_StartTime = 0;
	this->m_EndTime = 0;
}


/**************************************

	FunctionName : PrintMainMenu

	Purpose : -> Print the primary menu to let you select start game or change
			  theme
			  -> Enter sunfunction

	Calls : -> PrintClassicalMenu()
			-> PrintRiskMenu()
			-> changeColor()
			-> PrintRank()

	Input : Ente your choice

	Output : Menu

***************************************/

void GameBody::PrintMainMenu() {
	do {
		cout << "****************" << endl
			<< "*    M E N U   *" << endl
			<< "*  2048  V1.4  *" << endl
			<< "****************" << endl
			<< "* 1. Classical *" << endl
			<< "*--------------*" << endl
			<< "*   2. Risk    *" << endl
			<< "*--------------*" << endl
			<< "*   3. Theme   *" << endl
			<< "*--------------*" << endl
			<< "*   4. Rank    *" << endl
			<< "*--------------*" << endl
			<< "*   0. Exit    *" << endl
			<< "****************" << endl;
		cout << " Your choice : ";
		int choose = 0;
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			this->PrintClassicalMenu();
			break;
		case 2:
			this->PrintRiskMenu();
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


/**************************************

	FunctionName : PrintClassicalMenu

	Purpose : -> Print the Classical menu to let you select classical game
			  mode
			  -> Enter sunfunction
			  -> Change the size of windows
			  -> Set the mode

	Calls : ClassicalMode()

	Input : your choice

	Output : ClassicalMenu

***************************************/

void GameBody::PrintClassicalMenu() {
	cout << "******************" << endl
		<< "* CLASSICAL MODE *" << endl
		<< "******************" << endl
		<< "*    1. Easy     *" << endl
		<< "*----------------*" << endl
		<< "*    2. Harder   *" << endl
		<< "*----------------*" << endl
		<< "*    3. Hell     *" << endl
		<< "*----------------*" << endl
		<< "*    4. Heaven   *" << endl
		<< "******************" << endl
		<< "*    0. Back     *" << endl
		<< "******************" << endl
		<< "Please enter your choice :" << endl;
	int choose = 0;
	cin >> choose;
	system("mode con cols=70 lines=19");
	system("cls");
	switch (choose) {
	case 1:
		this->m_MODE = RANK_CLASSICAL_EASY; //set the mode
		this->ClassicalMode(CLASSICAL_MODE_EASY); // enter subfunction
		break;
	case 2:
		this->m_MODE = RANK_CLASSICAL_HARDER;
		this->ClassicalMode(CLASSICAL_MODE_HARDER);
		break;
	case 3:
		this->m_MODE = RANK_CLASSICAL_HELL;
		this->ClassicalMode(CLASSICAL_MODE_HELL);
		break;
	case 4:
		this->m_MODE = RANK_CLASSICAL_HEAVEN;
		this->ClassicalMode(CLASSICAL_MODE_HEAVEN);
		break;
	default:
		break;
	}
}


/**************************************

	FunctionName : PrintRiskMenu

	Purpose : -> Print the Risk menu to let you select risk game
			  mode
			  -> Enter sunfunction
			  -> Change the size of windows
			  -> Set the mode

	Calls : RiskMode()

	Input : your choice

	Output : RiskMenu

***************************************/

void GameBody::PrintRiskMenu() {
	cout << "******************" << endl
		<< "*    RISK MODE   *" << endl
		<< "******************" << endl
		<< "*  1. Try        *" << endl
		<< "*----------------*" << endl
		<< "*  2. Super      *" << endl
		<< "*----------------*" << endl
		<< "*  3. Professor  *" << endl
		<< "******************" << endl
		<< "*  0. Back       *" << endl
		<< "******************" << endl
		<< "Please enter your choice :" << endl;
	int choose = 0;
	cin >> choose;
	system("cls");
	switch (choose)
	{
	case 1:
		system("mode con cols=70 lines=19"); //change size of windows
		system("cls");
		this->m_MODE = RANK_ENDLESS_TRY; //set the mode
		this->RiskMode(ENDLESS_MODE_TRY); //enter subfunction
		break;
	case 2:
		system("mode con cols=76 lines=28");
		system("cls");
		this->m_MODE = RANK_ENDLESS_PRO;
		this->RiskMode(ENDLESS_MODE_PRO);
		break;
	case 3:
		system("mode con cols=90 lines=36");
		system("cls");
		this->m_MODE = RANK_ENDLESS_SUP;
		this->RiskMode(ENDLESS_MODE_SUP);
		break;
	default:
		break;
	}
}


/**************************************

	FunctionName : ClassicalMode

	Purpose : Enter the classical main loop

	Parameter : Difficulty : Represents the simple mode clearance condition

	Calls : addCard()
			PrintMainGameBody()
			moveCard()
			IsOver(Difficulty)
			YouWin()

***************************************/

void GameBody::ClassicalMode(int Difficulty)
{
	time_t now;
	this->m_StartTime = time(&now); //get start time
	while (this->m_GameStatus == 0) {
		this->addCard();
		this->PrintMainGameBody(); 
		this->moveCard();
		this->IsOver(Difficulty); //Determine if the game is over
		if (this->m_GameStatus == 1) {
			//You have won this round
			this->m_EndTime = time(&now); //get the time
			system("cls");
			this->YouWin(); // enter Youwin()
			system("pause");
			return;
		}
		else if (this->m_GameStatus == -1) {
			//You lose
			this->m_EndTime = time(&now); //get the time
			system("cls");
			this->YouLose();// enter Youlose()
			system("pause");
			return;
		}
		system("cls");
	}
}


/**************************************

	FunctionName : RiskMode

	Purpose : Enter the classical main loop

	Parameter : ARGUMENT : The number of squares 4/6/8, default is 4

	Calls : addCard(ARGUMENT)
			PrintMainGameBody(ARGUMENT)
			moveCard(ARGUMENT)
			IsOver(-1, ARGUMENT) // -1 cound not be 128/256/512/2048
			Gameover()

***************************************/

void GameBody::RiskMode(int ARGUMENT)
{
	time_t now;
	this->m_StartTime = time(&now); // get time
	while (this->m_GameStatus == 0) {
		this->addCard(ARGUMENT);
		this->PrintMainGameBody(ARGUMENT);
		this->moveCard(ARGUMENT);
		this->IsOver(-1, ARGUMENT);

		if (this->m_GameStatus == -1) {
			// game over
			this->m_EndTime = time(&now);
			system("cls");
			this->GameOver();
			system("pause");
			return;
		}
		system("cls");
	}
}


/**************************************

	FunctionName : PrintMainGameBody

	Purpose : -> Print overall game framework
			  -> SQUARE is The number of squares 4/6/8, default is 4

	Parameter : SQUARE is The number of squares 4/6/8, default is 4

	Output : PrintMainGameBody

***************************************/

void GameBody::PrintMainGameBody(int SQUARE) {
	for (int i = 0; i < SQUARE * 4 + 1; i++)
	{
		if (i % 4 == 0)
			for (int j = 0; j < SQUARE * 6; j++)
				cout << "-";
		else
			for (int j = 0; j < SQUARE + 1; j++){
				if (j == SQUARE){
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

		switch (i){
			// other infomation
			case 2: 
				cout << "\tThe next card : " << this->m_NextCard ;
				break;
			case 4:
				cout << "\tYour score : " << this->m_Score ;
				break;
			case 12:
				cout << "\tTap ● ◎ ○ ★ to remove card." ;
				break;
			default:
				break;
		}
		cout << "\n";
	}
}


/**************************************

	FunctionName : PrintRank

	Purpose : -> Print the whole rank by sort of mode
			  -> Ask user wether delete the database
			  -> Change the window's size

***************************************/

void GameBody::PrintRank(){
	system("mode con cols=60 lines=70");
	system("cls");
	cout << "\t\t      R A N K\n----------------------------------------------------\n" << endl;

	for (int j = RANK_CLASSICAL_EASY; j <= RANK_ENDLESS_SUP; j++){
		cout << "\t" << TITLE[j] << endl;
		cout << "RANK\t" << "NAME\t" << "SCORE\t" << "USE TIME\t\t" << "TIME" << endl;
		int rank = 1;
		for (auto i : this->m_Rank) {
			if (i.m_Mode == j) {
				cout << left << " " << setw(7) << rank  << setw(8) << i.m_Name << setw(10) << i.m_Score 
					<< i.m_GameTime << "s\t\t" << i.m_Time.m_Year << "."
					<< i.m_Time.m_Month << "." << i.m_Time.m_Day << " "
					<< i.m_Time.m_Hour << ":" << i.m_Time.m_Minute << ":" << i.m_Time.m_Second << endl;
				rank++;
			}
		}
		rank = 1;
		cout << "\n----------------------------------------------------------\n\n";
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


/**************************************

	FunctionName : addCard

	Purpose : when all the number is not 0, add a number in it

	Parameter : ARGUMENT is The number of squares 4/6/8, default is 4

	Calls : isFull()

***************************************/

void GameBody::addCard(int ARGUMENT) {
	if (this->isFull()) return;
	int curCol, curRow, isInserted = 0;
	srand((unsigned int)time(NULL));
	while (isInserted == 0) {
		curCol = rand() % ARGUMENT;
		curRow = rand() % ARGUMENT;
		// if the founded place is 0, insrt the number
		// or else create a random number again
		if (this->m_Layout[curCol][curRow] == 0){
			this->m_Layout[curCol][curRow] = this->m_FirstCard;
			isInserted = 1;
			this->m_NextCard = (rand() % 4) / 2 == 1 ? 2 : 4; //will be showen at game body
			this->m_FirstCard = this->m_NextCard;
		}
	}
}


/**************************************

	FunctionName : moveCard

	Purpose : To move card.
			  -> Traverses the grid of each row or column
			  -> The traversal direction of each row or column is opposite 
					 to the direction of the direction key being pressed
			  -> Find out if there is space in the direction of the direction key pressed. 
			  -> If so, move all of them first, and then merge the card
	
	Parameter : ARGUMENT is The number of squares 4/6/8, default is 4

	Input : Keys on the keyboard

***************************************/

void GameBody::moveCard(int ARGUMENT) {
	system("pause");
	int upArrow = 0;
	int downArrow = 0;
	int leftArrow = 0;
	int rightArrow = 0;

	//Get keyboard commands
	upArrow = GetAsyncKeyState(VK_UP);
	downArrow = GetAsyncKeyState(VK_DOWN);
	leftArrow = GetAsyncKeyState(VK_LEFT);
	rightArrow = GetAsyncKeyState(VK_RIGHT);

	//judge which key was taped and respond accordingly.
	if (upArrow != 0){
		for(int i = 0; i < ARGUMENT; i++)
			for(int k = 0; k < ARGUMENT; k++)
				for (int j = ARGUMENT - 1; j > 0; j --) {
					if (this->m_Layout[j][i] != 0 && this->m_Layout[j - 1][i] == 0) {
						// combine
						this->m_Layout[j - 1][i] = this->m_Layout[j][i];
						this->m_Layout[j][i] = 0;
					}
					if (this->m_Layout[j][i] == this->m_Layout[j - 1][i]) {
						this->m_Layout[j - 1][i] *= 2; //combine
						this->m_Score += this->m_Layout[j - 1][i];  //add score
						this->m_Layout[j][i] = 0;
					}
				}
	}
	else if(downArrow != 0){
		for(int i = 0; i < ARGUMENT; i ++)
			for (int k = 0; k < ARGUMENT; k++)
				for (int j = 0; j < ARGUMENT - 1; j++) {
					if (this->m_Layout[j][i] != 0 && this->m_Layout[j + 1][i] == 0) {
						this->m_Layout[j + 1][i] = this->m_Layout[j][i];
						this->m_Layout[j][i] = 0;
					}
					if (this->m_Layout[j][i] == this->m_Layout[j + 1][i]) {
						this->m_Layout[j + 1][i] *= 2;
						this->m_Score += this->m_Layout[j + 1][i]; //add score
						this->m_Layout[j][i] = 0;
					}
				}
	}
	else if (leftArrow != 0) {
		for(int i = 0; i < ARGUMENT; i++)
			for (int k = 0; k < ARGUMENT; k++)
				for (int j = ARGUMENT - 1; j > 0; j--) {
					if (this->m_Layout[i][j] != 0 && this->m_Layout[i][j - 1] == 0) {
						this->m_Layout[i][j - 1] = this->m_Layout[i][j];
						this->m_Layout[i][j] = 0;
					}
					if (this->m_Layout[i][j] == this->m_Layout[i][j - 1]) {
						this->m_Layout[i][j - 1] *= 2;
						this->m_Score += this->m_Layout[i][j - 1]; //add score
						this->m_Layout[i][j] = 0;
					}
				}
	}
	else if (rightArrow != 0) {
		for(int i = 0; i < ARGUMENT; i++)
			for (int k = 0; k < ARGUMENT; k++)
				for (int j = 0; j < ARGUMENT - 1; j++) {
					if (this->m_Layout[i][j] != 0 && this->m_Layout[i][j + 1] == 0) {
						this->m_Layout[i][j + 1] = this->m_Layout[i][j];
						this->m_Layout[i][j] = 0;
					}
					if (this->m_Layout[i][j] == this->m_Layout[i][j + 1]) {
						this->m_Layout[i][j + 1] *= 2;
						this->m_Score += this->m_Layout[i][j + 1]; //add score
						this->m_Layout[i][j] = 0;
					}
				}
	}
}


/**************************************

	FunctionName : IsOver

	Purpose : judge the game status

	Parameter : FLAG : 
					-> In simple mode , as a standard for whether or not to clear customs
					-> It will be 128/256/512/2048
					-> Four numbers , four patterns

				ARGUMENT : 
					-> ARGUMENT is The number of squares 4/6/8, default is 4

***************************************/

void GameBody::IsOver(int FLAG, int ARGUMENT) {
	int flag = 0;
	for (int i = 0; i < ARGUMENT; i++)
		for (int j = 0; j < ARGUMENT - 1; j++) {
			//Determine if there are two adjacentand equal Numbers
			//Or whether there is a number that satisfies flag
			if (this->m_Layout[i][j] == this->m_Layout[i][j + 1] || this->m_Layout[j][i] == this->m_Layout[j + 1][i])
				flag = 1;
			if (this->m_Layout[i][j] == FLAG || this->m_Layout[i][j + 1] == FLAG)
				this->m_GameStatus = 1;
		}
	if (!flag)
		// If not, Game over
		this->m_GameStatus = -1;
}


/**************************************

	FunctionName : isFull

	Purpose : Judge if it's all 0

	Parameter : ARGUMENT is The number of squares 4/6/8, default is 4
	
	Return :  1 : full
			  0 : not full

***************************************/

bool GameBody::isFull(int ARGUMENT) {
	for (int i = 0; i < ARGUMENT; i++)
		for (int j = 0; j < ARGUMENT; j++)
			if (this->m_Layout[i][j] == 0)
				return 0;
	return 1;
}


/**************************************

	FunctionName : changeColor

	Purpose : change the Color

***************************************/

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
	this->PrintMainMenu();
}


/**************************************

	FunctionName : YouLose

	Purpose : -> Print You lose picture
			  -> show final score
			  -> call save()
			  -> initialize the game

	Calls : saveFile()
			initGame()

***************************************/

void GameBody::YouLose() {
	system("mode con cols=50 lines=23");
	system("cls");
	cout << "込        込    込込込込      込     込" << endl;
	cout << "  込    込     込      込     込     込" << endl;
	cout << "     込       込        込    込     込" << endl;
	cout << "     込       込        込    込     込" << endl;
	cout << "     込       込        込    込     込" << endl;
	cout << "     込        込     込      込     込" << endl;
	cout << "     込         込込込込        込込込\n" << endl;
	cout << "\t\tFINAL SCORE : " << this->m_Score << endl << endl;
	cout << "込         込込込込      込込込込    込込込込    " << endl;
	cout << "込       込       込    込            込         " << endl;
	cout << "込       込       込    込            込        " << endl;
	cout << "込       込       込     込込込込     込込込   " << endl;
	cout << "込       込       込            込    込        " << endl;
	cout << "込       込       込            込    込        " << endl;
	cout << "込込込込   込込込込      込込込込     込込込込   " << endl;
	cout << "\n\n";
	this->saveFile();
	this->InitGame();
}


/**************************************

	FunctionName : YouWin

	Purpose : -> Print You win picture
			  -> show final score
			  -> call save()
			  -> initialize the game

	Calls : saveFile()
			initGame()


***************************************/

void GameBody::YouWin() {
	system("mode con cols=47 lines=26");
	system("cls");
	cout << "込        込    込込込込      込     込" << endl;
	cout << "  込    込     込      込     込     込" << endl;
	cout << "     込       込        込    込     込" << endl;
	cout << "     込       込        込    込     込" << endl;
	cout << "     込       込        込    込     込" << endl;
	cout << "     込        込     込      込     込" << endl;
	cout << "     込         込込込込        込込込\n\n\n" << endl;
	cout << "\t\tFINAL SCORE : " << this->m_Score << endl << endl;
	cout << "込      込      込   込込込    込          込" << endl;
	cout << "込      込      込     込      込込        込" << endl;
	cout << "込      込      込     込      込  込      込" << endl;
	cout << "込      込      込     込      込    込    込" << endl;
	cout << " 込   込  込   込      込      込      込  込" << endl;
	cout << "  込  込   込 込       込      込        込込" << endl;
	cout << "    込      込       込込込    込          込 " << endl;
	cout << "\n\n";
	this->saveFile();
	this->InitGame();
}


/**************************************

	FunctionName : Gameover

	Purpose : -> Print You lose picture
			  -> show final score
			  -> call save()
			  -> initialize the game

	Calls : saveFile()
			initGame()

***************************************/

void GameBody::GameOver(){
	system("mode con cols=61 lines=22");
	system("cls");
	cout << "込込込込込込        込       込          込     込込込込込" << endl
		<< "込                込  込    込込       込込     込"<< endl
		<< "込              込      込  込  込    込  込    込" << endl
		<< "込    込込込込  込込込込込  込     込     込    込込込込" << endl
		<< "込      込 込   込      込  込     込     込    込" << endl
		<< "込     込  込   込      込  込     込     込    込" << endl
		<< " 込込込込  込   込      込  込     込     込    込込込込込" << endl << endl;
	cout << "\t\tFINAL-SCORE-" << this->m_Score << endl << endl;
	cout << " 込込込込    込      込   込込込込    込込込込" << endl
		<< "込      込   込      込   込          込      込" << endl
		<< "込      込    込    込    込          込     込 " << endl
		<< "込      込    込    込    込込込込    込込込  " << endl
		<< "込      込     込  込     込          込   込  " << endl
		<< "込      込      込込      込          込    込   " << endl
		<< " 込込込込        込       込込込込    込     込" << endl;
	cout << "\n\n";
	this->saveFile();
	this->InitGame();
}


/**************************************

	FunctionName : readFile

	Purpose : -> when you open the game , it will read your last records
			  -> wash the data : these that is totally similar

***************************************/

void GameBody::readFile(){
	GameRecord cur;
	ifstream ifs;
	ifs.open("data.dat", ios::in);
	if (!ifs || ifs.peek() == EOF) return; //if is empty , return
	while (ifs.peek() != EOF) {
		// read the file
		ifs >> cur.m_Mode >> cur.m_Name >> cur.m_Score >> cur.m_GameTime 
			>> cur.m_Time.m_Year >> cur.m_Time.m_Month >> cur.m_Time.m_Day
			>> cur.m_Time.m_Hour >> cur.m_Time.m_Minute >> cur.m_Time.m_Second;
		this->m_Rank.push_back(cur);
	}

	//data cleaning
	for (int i = 0; i < this->m_Rank.size() - 1; i++) {
		if (this->m_Rank[i].m_Score == 0)
			this->m_Rank.erase(this->m_Rank.begin() + i);
		if(this->m_Rank[i] == this->m_Rank[i + 1])
			this->m_Rank.erase(this->m_Rank.begin() + i);
	}

	ifs.close();
}


/**************************************

	FunctionName : saveFile

	Purpose : -> Save local game record
			  -> Calculate the game time
			  -> write the file

***************************************/

void GameBody::saveFile(){

	cout << "Please enter your name to save your record:" << endl;
	GameRecord cur;
	cin >> cur.m_Name;
	cur.m_Score = this->m_Score;
	cur.m_Mode = this->m_MODE;
	struct tm t;
	time_t nowTime;
	time(&nowTime);
	localtime_s(&t, &nowTime);
	cur.m_GameTime = this->m_EndTime - this->m_StartTime;
	cur.m_Time.m_Year = t.tm_year + 1900;
	cur.m_Time.m_Month = t.tm_mon + 1;
	cur.m_Time.m_Day = t.tm_mday;
	cur.m_Time.m_Hour = t.tm_hour;
	cur.m_Time.m_Minute = t.tm_min;
	cur.m_Time.m_Second = t.tm_sec;
	this->m_Rank.push_back(cur);

	sort(this->m_Rank.begin(), this->m_Rank.end(), sortScoreRank());

	ofstream  ofs;
	ofs.open("data.dat", ios::binary | ios::trunc);
	for (auto i : this->m_Rank) {
		ofs << i.m_Mode << " " << i.m_Name << " " << i.m_Score << " " 
			<< i.m_GameTime << " " << i.m_Time.m_Year << " " 
			<< i.m_Time.m_Month << " " << i.m_Time.m_Day << " " 
			<< i.m_Time.m_Hour << " " << i.m_Time.m_Minute << " " << i.m_Time.m_Second << endl;
	}
	ofs.close();
}
