/**********************

Copyright : Jancoyan

Auther : Jancoyan

Date : 2020/04/15

Discription : 2048 Game

***********************/

#pragma once
#include<iostream>

using namespace std;


// AS A FLAG WHEN SAVE , READ AND PRINT RANK
// it is the first propety of the record vector
// it is used to identify the mode when print rank
const int RANK_CLASSICAL_EASY = 1;
const int RANK_CLASSICAL_HARDER = 2;
const int RANK_CLASSICAL_HELL = 3;
const int RANK_CLASSICAL_HEAVEN = 4;
const int RANK_ENDLESS_TRY = 5;
const int RANK_ENDLESS_PRO = 6;
const int RANK_ENDLESS_SUP = 7;

// It is flag of pass the classical mode
const int CLASSICAL_MODE_EASY = 128;
const int CLASSICAL_MODE_HARDER = 256;
const int CLASSICAL_MODE_HELL = 512;
const int CLASSICAL_MODE_HEAVEN = 2048;

//In risk mode , it is degree of difficulty
const int ENDLESS_MODE_TRY = 4;
const int ENDLESS_MODE_PRO = 6;
const int ENDLESS_MODE_SUP = 8;

//To print rank 
const string TITLE[8] =
{
	" ",
	"\tCASSICAL EASY MODE\n",
	"\tCASSICAL HARDER MODE\n",
	"\tCASSICAL HELL MODE\n",
	"\tCASSICAL HEAVEN MODE\n",
	"\tENDLESS TRY MODE\n",
	"\tENDLESS PRO MODE\n",
	"\tENDLESS SUP MODE\n"
};