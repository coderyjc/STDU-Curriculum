/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/15

Discription : 2048 Game

***********************/

#include"class2048.h"
#include<iostream>
using namespace std;

int main(){
	system("title 2048v1.4.0");
	GameBody game;
	game.PrintMainMenu(); // Enter main menu to select choice
	return 0;
}