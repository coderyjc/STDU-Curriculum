#include<iostream>
#include<ctime>
#include<cstdlib>
#include<thread>
using namespace std;

void calTime(int startTime, int guess, int rst) {
	while (1) {
		if (time(0) > startTime + guess) {
			cout << "���ź���δ���ڹ涨ʱ���ڲ³���ȷ���֣�������Ϊ" << rst << endl;
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
		cout << "������涨ʱ�䣺 ";
		cin >> guessTime;
		time_t now = time(0);
		thread t(calTime, now, guessTime, rst);
		if (t.joinable()) t.detach();
		do {
			cout << "���������µ����֣�" << endl;
			cin >> guess;
			if (time(0) >= now + guessTime) break;
			if (guess > rst) cout << "����" << endl;
			if (guess < rst) cout << "����" << endl;
			if (guess == rst) {
				cout << "��ϲ����ȷ�³�����" << rst << endl;
				flag = 1;
			}
		} while (!flag);
		cout << "�Ƿ�Ҫ�ؿ�һ��(�� 1/�� 0)��" << endl;
		cin >> flag1;
	} while (flag1);
	return 0;
}