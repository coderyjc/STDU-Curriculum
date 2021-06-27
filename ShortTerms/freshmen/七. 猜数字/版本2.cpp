#include<iostream>
#include<ctime>
#include<cstdlib>
#include<thread>
using namespace std;

void calTime(int startTime, int guess, int rst) {
	while (1) {
		if (time(0) > startTime + guess) {
			cout << "很遗憾，未能在规定时间内猜出正确数字，该数字为" << rst << endl;
			return;
		}
	}
}

int main() {
	srand(time(NULL));
	int flag;
	int flag1;
	do {
		flag = 0;
		flag1 = 0;
		int rst = rand() % 10000 + 1;
		int guessTime;
		int guess;
		cout << "请输入规定时间： ";
		cin >> guessTime;
		time_t now = time(0);
		thread t(calTime, now, guessTime, rst);
		if (t.joinable()) t.detach();
		do {
			cout << "请输入您猜的数字：" << endl;
			cin >> guess;
			if (time(0) >= now + guessTime) break;
			if (guess > rst) cout << "高了" << endl;
			if (guess < rst) cout << "低了" << endl;
			if (guess == rst) {
				cout << "恭喜！正确猜出数字" << rst << endl;
				flag = 1;
			}
		} while (!flag);
		cout << "是否要重开一局(是 1/否 0)？" << endl;
		cin >> flag1;
	} while (flag1);
	return 0;
}