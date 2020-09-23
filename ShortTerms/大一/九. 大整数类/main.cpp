#include"BigInteger.h"

void MyAdd(BigInteger b1, BigInteger b2) {
	BigInteger b = b1 + b2;
	cout << "结果为：" << b << endl;
}

void MyMuti(BigInteger b1, BigInteger b2) {
	BigInteger b = b1 * b2;
	cout << "结果为：" << b << endl;
}

void MyFact(BigInteger b1) {
	BigInteger rst = 1;
	int i = b1.getINT();
	while (i) {
		BigInteger temp = rst * i;
		rst = temp;
		i--;
	}
	cout << "结果为：" << rst << endl;
}

void MyMinu(BigInteger b1, BigInteger b2) {
	BigInteger b = b1 - b2;
	cout << "结果为：" << b << endl;
}

int main() {
	BigInteger b1, b2;
	do {
		cout << "请选择进行的计算类型：" << endl
			<< "1. 加\n2. 减\n3. 乘\n4. 阶乘\n其他. 退出" << endl;
		int choose;
		cin >> choose;
		if (choose < 1 || choose > 4) break;
		switch (choose) {
		case 1:
		cout << "请输入进行计算的两个数: " << endl;
		cin >> b1 >> b2;
			MyAdd(b1, b2);
			break;
		case 2:
		cout << "请输入进行计算的两个数: " << endl;
		cin >> b1 >> b2;
			MyMinu(b1, b2);
			break;
		case 3:
		cout << "请输入进行计算的两个数: " << endl;
		cin >> b1 >> b2;
			MyMuti(b1, b2);
			break;
		case 4:
		cout << "请输入进行计算的数: " << endl;
		cin >> b1 ;
			MyFact(b1);
			break;
		}
		cout << endl;
	} while (1);
	return 0;
}