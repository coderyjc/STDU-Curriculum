#include "ParkingManager.h"

#define PARK_PER_TIME 5.0 //停在停车场的单位时间内的价格
#define WAIT_PER_TIME 2.0 //停在便道上的单位时间内的价格

const string CARS[] = { "", "轿车", "客车", "卡车" };

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

	// 输入车号
	do {
		cout << "请输入车号" << endl;
		cin >> id;
		if (this->currentCar.find(id) != currentCar.end()) {
			// 车辆已经存在
			cout << "--------------------\n提醒\n\n车辆已存在，请重新输入\n--------------------\n" << endl;
		} else break;
	} while (1);

	this->currentCar.insert(id);
	// 输入车辆类型
	do {
		cout << "请选择车辆类型" << endl
			<< "---------------" << endl
			<< "1.轿车" << endl
			<< "2.客车" << endl
			<< "3.卡车" << endl
			<< "请输入: ";
		cin >> type;
		if (type < 1 || type > 3) {
			cout << "----------------\n警告：\n\n请输入正确的数字\n----------------" << endl;
		} else break;
	} while (1);

	// 输入当前时间
	do {
		cout << "请输入当前时间 : ";
		cin >> time;
		if (time < 0) {
			cout << "----------------\n警告：\n\n请输入正确的时间\n----------------" << endl;
		} else break;
	} while (1);


	if (this->size - OCCUPY[type] < 0) { //	检查车库有没有满
		cout << "----------------------------\n提醒：\n\n车已停满，车辆进入等候区等候...\n----------------------------" << endl;
		this->wait.push(new Car(time, id, type));
		system("pause");
		system("cls");
		return;
	}
	this->parking.push_0(new Car(id, type, time));
	cout << "-----------------------\n提醒\n\n车号 " << id << " 进入 " << this->parking.size() << " 号车位, 时间为" << time << endl 
		<< "-----------------------" << endl;
	this->size -= OCCUPY[type];

	system("pause");
	system("cls");
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
	
	cout << "请输入出停车场的车号: ";
	cin >> id;
	cout << "请输入当前时间：";
	cin >> time;
	
	int flag = 0;
	while (!this->parking.empty_0()) {
		if (this->parking.top_0()->ID != id) { 
			//这辆车不是要出去的车
			this->parking.push_1(this->parking.top_0());
			this->parking.pop_0();
		} else {
			// 这辆车是要出去的车
			double toPay = OCCUPY[this->parking.top_0()->type] * (PARK_PER_TIME * (time - this->parking.top_0()->enTime) +
				WAIT_PER_TIME * (this->parking.top_0()->enTime - this->parking.top_0()->waitTime));
			if (toPay < 0) {
				cout << "--------------------\n警告:\n\n计算错误！出站失败！\n--------------------" << endl;
				system("pause");
				system("cls");
				return;
			}
			cout << "--------------------\n提醒: \n\n车 " << this->parking.top_0()->ID
				<< " 出库，时长为 " <<
				(time - this->parking.top_0()->enTime) +
				(this->parking.top_0()->enTime - this->parking.top_0()->waitTime)
				<< " 应付金额为 "
				<< toPay
				<< endl
				<< "--------------------\n" << endl;
			Car* todel = this->parking.top_0();
			this->parking.pop_0();
			
			//车站的容量加上刚刚出去的这辆车的容量
			this->size += OCCUPY[todel->type]; 
			
			//delete 刚出栈的车
			delete todel;
			flag = 1;
			break;
		}
	}
	if (flag) { 
		// 在车库中找到了这辆车，这辆车已经出去了的情况下
		while (!this->parking.empty_1()) {
			// 将刚刚让路去的车弄进去
			this->parking.push_0(this->parking.top_1());
			this->parking.pop_1();
		}
		// 如果在外面等待的第一辆车符合要求，
		// 也就是车库中可以容纳这辆车
		// 就把在外面等待的1辆车放进车库
		if (!this->wait.empty()) { // 如果外面等待队列不空
			//  如果车库中还有空间
			if (this->size - OCCUPY[this->wait.front()->type] >= 0) {
				this->size -= OCCUPY[this->wait.front()->type];
				cout << "--------------\n提示：\n\n在等待队列中的车 " << this->wait.front()->ID << " 进入车库，时间为 " << time 
					<< "\n--------------"<< endl;
				this->wait.front()->enTime = time; 
				
				//设置等待队列最前面的车的入库时间
				this->parking.push_0(this->wait.front());
				this->wait.pop();
			}
		}
	} else { 
		// 在车库中没有找到这辆车，从等候区寻找这辆车
		flag = 0;
		// int findit = 0;
		for (int i = 0; i < this->wait.size(); i++) {
			if (this->wait.front()->ID == id) {
				// 找到了这辆车，这时候front位置就是我们要找的车辆
				cout << "车号 " << this->wait.front()->ID
					<< " 出库，时长为 " << time - this->wait.front()->waitTime
					<< " 应付金额为 " << OCCUPY[this->wait.front()->type] * WAIT_PER_TIME * (time - this->wait.front()->waitTime) << endl;
				Car* todel = this->wait.front();
				this->currentCar.erase(todel->ID); // 在所有的车辆集合中删除这辆车
				this->wait.pop();
				//出停车场的车，delete掉
				delete todel; 
				flag = 1;
				break;
			} else { 
				// 当前这辆车不是要找的对象， 则将这辆车插入到队列尾部（就算以后找到了也是要插到队列的尾部的）
				this->wait.push(this->wait.front());
				this->wait.pop();
			}
		}
	}
	if (!flag) cout << "--------------------\n提示: \n\n找不到这辆车\n--------------------" << endl;
	system("pause");
	system("cls");
}

void ParkingManager::mainLoop() {
	int choose = 0;
	while (true) {
		cout << "----------------\n停车场管理程序\n----------------" << endl
			<< "1.进入停车场" << endl
			<< "2.开出停车场" << endl
			<< "3.查看停车场车辆" << endl
			<< "4.查看等待区车辆" << endl
			<< "0.退出程序\n----------------" << endl
			<< "请输入选项: ";
		cin >> choose;
		switch (choose) {
			case 1: enterPark(); break;
			case 2: outPark(); break;
			case 3: printParking(); break;
			case 4: printWaiting(); break;
			case 0: default: return;
		}
	}
}

void ParkingManager::printParking() {
	// 用辅助栈帮助遍历
	if (this->parking.empty_0()) {
		cout << "--------------------\n提示：\n\n当前停车场中没有车辆\n----------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "\n----------------\n停车场中的车辆\n----------------\n" << endl;

	// 表头
	cout << "序号" << "\t车号" << "\t车辆类型" << "\t进入车场时间" << "\t所占空间" << endl;
	cout << "----------------------------------------------------------" << endl;
	// 把已经遍历过的车放到辅助栈中
	// 遍历完了之后再从辅助栈中拿出来
	// 在辅助栈中进行操作的时候就不用进行 size 相关的操作了
	// 先从 0 栈中放进辅助栈中，同时遍历。
	int i = 1;
	while (!this->parking.empty_0()) {
		Car* temp = this->parking.top_0();
		// 访问
		cout << i++ << "\t" << temp->ID << "\t" << CARS[temp->type] << "\t\t" << temp->enTime << "\t\t" << OCCUPY[temp->type] <<  endl;
		// 放进辅助栈
		this->parking.push_1(temp);
		// 弹出栈
		this->parking.pop_0();
	}
	// 再从 1 栈中放进 0 栈中
	while (!this->parking.empty_1()) {
		this->parking.push_0(this->parking.top_1());
		this->parking.pop_1();
	}
	system("pause");
	system("cls");
}

void ParkingManager::printWaiting() {
	if (this->wait.size() == 0) {
		cout << "----------------------\n提示：\n\n当前等待队列中没有车辆\n----------------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	// 做一个 size 大小的出队和入队
	// 获取现在等待队列的大小
	int waitNumber = this->wait.size();
	cout << "\n----------------\n等待队列中的车辆\n----------------\n" << endl;
	// 表头
	cout << "序号" << "\t车号" << "\t车辆类型" << "\t进入队列时间" << "\t所占空间" << endl;
	cout << "----------------------------------------------------------" << endl;

	// i 是打印序号
	int i = 1;
	while (waitNumber--) {
		// 把当前遍历的车先遍历，再出栈，再入栈
		Car* temp = this->wait.front();
		cout << i++ << "\t" << temp->ID << "\t" << CARS[temp->type] << "\t\t" << temp->waitTime << "\t\t" << OCCUPY[temp->type] << endl;
		this->wait.push(this->wait.front());
		this->wait.pop();
	}
	system("pause");
	system("cls");
}
