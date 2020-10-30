#include "ParkingManager.h"

#define PARK_PER_TIME 5.0 //停在停车场的单位时间内的价格
#define WAIT_PER_TIME 2.0 //停在便道上的单位时间内的价格

const string CARS[] = { "", "小轿车", "客车", "十轮卡车" };

const double OCCUPY[4] = { 0, 1, 1.5, 3 }; //不同的车占据的车位数量，也是收取金额的系数

/*
	车辆类型的作用:
	- 判断车辆的占地面积
	- 根据占地面积来计算停车人应该付的金额【在车库和在等候区】
*/

ParkingManager::ParkingManager() {
	this->size = MAX_STACK_SIZE;
}

ParkingManager::~ParkingManager() {
	Car* temp = NULL;

	while (!this->parking.empty_0()) { // 析构车栈头
		delete this->parking.top_0();
		this->parking.pop_0();
	}

	while (!this->parking.empty_1()) { //析构车栈尾
		delete this->parking.top_1();
		this->parking.pop_1();
	}

	while (!this->wait.empty()) {
		delete this->wait.front();
		this->wait.pop();
	}
}


// 前提：等候区容量无限

void ParkingManager::enterPark() {
	string id;
	int time;
	int type;
	cin >> id >> type >> time;
	if (this->size - OCCUPY[type] < 0) { //	检查车库有没有满
		cout << "车已停满，车辆进入等候区等候..." << endl;
		this->wait.push(new Car(time, id, type));
		return;
	}
	this->parking.push_0(new Car(id, type, time));
	cout << "车号 " << id << " 进入 " << this->parking.size() << " 号车位, 时间为" << time << endl;
	this->size -= OCCUPY[type];
}

/*
	考虑三种情况:
	1. 一直在停车场
	2. 原来在便道等候，后来进入了停车场
	3. 一直在便道等候
*/

void ParkingManager::outPark() {
	string id;
	int time;
	int type;
	cin >> id >> type >> time;
	int flag = 0;
	while (!this->parking.empty_0()) {
		if (this->parking.top_0()->ID != id) { //这辆车不是要出去的车
			this->parking.push_1(this->parking.top_0());
			this->parking.pop_0();
		} else { // 这辆车是要出去的车
			cout << "车号 " << this->parking.top_0()->ID
				<< " 出库，时长为 " <<
				(time - this->parking.top_0()->enTime) +
				(this->parking.top_0()->enTime - this->parking.top_0()->waitTime)
				<< " 应付金额为 "
				<< OCCUPY[type] * (PARK_PER_TIME * (time - this->parking.top_0()->enTime) + 
					WAIT_PER_TIME * (this->parking.top_0()->enTime - this->parking.top_0()->waitTime))
				<< endl;
			Car* todel = this->parking.top_0();
			this->parking.pop_0();
			this->size -= OCCUPY[todel->type]; //减去容量
			delete todel;//delete 刚出栈的车
			flag = 1;
			break;
		}
	}
	if (flag) { // 在车库中找到了这辆车
		while (!this->parking.empty_1()) { // 将刚才出去的车弄进去
			this->parking.push_0(this->parking.top_1());
			this->parking.pop_1();
		}
		if (!this->wait.empty()) { // 把在外面等待的1辆车放进车库
			this->wait.front()->enTime = time; //设置等待队列最前面的车的入库时间
			this->parking.push_0(this->wait.front());
			this->wait.pop();
		}
	} else { // 在车库中没有找到这辆车，从等候区寻找这辆车
		flag = 0;
		// int findit = 0;
		for (int i = 0; i < this->wait.size(); i++) {
			if (this->wait.front()->ID == id) {
				// 找到了这辆车，这时候front位置就是我们要找的车辆
				cout << "车号 " << this->wait.front()->ID
					<< " 出库，时长为 " << time - this->wait.front()->waitTime
					<< " 应付金额为 " << OCCUPY[type] * WAIT_PER_TIME * (time - this->wait.front()->waitTime) << endl;
				Car* todel = this->wait.front();
				this->wait.pop();
				delete todel; //出停车场的车，delete掉
				flag = 1;
				break;
			} else { 
				// 当前这辆车不是要找的对象， 则将这辆车插入到队列尾部（就算以后找到了也是要插到队列的尾部的）
				this->wait.push(this->wait.front());
				this->wait.pop();
			}
		}
	}
	if (!flag) cout << "车库和等候区中没有这辆车" << endl;
}

void ParkingManager::mainLoop() {
	char choose = 0;
	while (true) {
		cout << "A.进入" << endl
			<< "D.开出" << endl
			<< "E.退出" << endl
			<< "请输入选项（A、D、E）、车号、车辆类型【小轿车（1）、客车（2）、十轮卡车（3）】和进入时间" << endl;
		cin >> choose;
		switch (choose) {
			case 'A': case 'a': enterPark(); break;
			case 'D': case 'd': outPark(); break;
			case 'E': case 'e': default: return;
		}
	}
}