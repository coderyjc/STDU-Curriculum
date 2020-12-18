#include"ArrayMap.h"
#include"TableMap.h"


/*
目前的想法：其中，

邻接表存储的是有向图

邻接矩阵存储的是无向图
*/
int main() {

	ArrayMap am;
	TableMap tm;

	int choose = 0;
	while (true) {
		cout << "选择存储方式" << endl
			<< "----------------" << endl
			<< "1.邻接表存储（有向）" << endl
			<< "2.邻接矩阵存储（无向）" << endl
			<< "0.退出" << endl
			<< "----------------" << endl
			<< "输入要测试的功能: ";
		cin >> choose;
		switch (choose) {
			case 1: system("cls");  tm.mainLoop();  break;
			case 2:system("cls");  am.mainLoop();  break;
			default: return 0;
		}
	}
	return 0;
}