#pragma once
#include<iostream>

using namespace std;

/*
	车辆类型号   车辆类型    占用空间
	   1        小轿车        1
	   2		客车			1.5
	   3		十轮卡车		 3
*/

class Car {
public:
	int type;
	string ID;
	int enTime;
	int waitTime;

	Car(string id, int type, int time) { 
		// 【直接进入车库】的车的构造函数
		this->ID = id;
		this->type = type;
		this->waitTime = time;
		this->enTime = time;
	}

	Car(int time, string id, int type) {
		// 【在车库外等候】的车的构造函数
		this->ID = id;
		this->type = type;
		this->waitTime = time;
		this->enTime = 0;
	}

	Car(const Car& c) {
		this->enTime = c.enTime;
		this->ID = c.ID;
	}
};
