#pragma once
#include"Queue.h"
#include"Stack.h"
#include"Car.h"
#include<set>

class ParkingManager {
public:
	ParkingManager();
	~ParkingManager();

	void enterPark();
	void outPark();
	void mainLoop();

	void printParking();
	void printWaiting();

private:
	double size;

	//当前的所有车
	set<string> currentCar;
	
	// 车双栈
	MyDoubleStack<Car*> parking; 
	
	// 等待队列
	MyQueue<Car*> wait; 
};
