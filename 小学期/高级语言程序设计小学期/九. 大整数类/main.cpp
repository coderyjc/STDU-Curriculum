#include"BigInteger.h"

void MyAdd(BigInteger b1, BigInteger b2) {
	BigInteger b = b1 + b2;
	cout << "���Ϊ��" << b << endl;
}

void MyMuti(BigInteger b1, BigInteger b2) {
	BigInteger b = b1 * b2;
	cout << "���Ϊ��" << b << endl;
}

void MyFact(BigInteger b1) {
	BigInteger rst = 1;
	int i = b1.getINT();
	while (i) {
		BigInteger temp = rst * i;
		rst = temp;
		i--;
	}
	cout << "���Ϊ��" << rst << endl;
}

void MyMinu(BigInteger b1, BigInteger b2) {
	BigInteger b = b1 - b2;
	cout << "���Ϊ��" << b << endl;
}

int main() {
	BigInteger b1, b2;
	do {
		cout << "��ѡ����еļ������ͣ�" << endl
			<< "1. ��\n2. ��\n3. ��\n4. �׳�\n����. �˳�" << endl;
		int choose;
		cin >> choose;
		if (choose < 1 || choose > 4) break;
		switch (choose) {
		case 1:
		cout << "��������м����������: " << endl;
		cin >> b1 >> b2;
			MyAdd(b1, b2);
			break;
		case 2:
		cout << "��������м����������: " << endl;
		cin >> b1 >> b2;
			MyMinu(b1, b2);
			break;
		case 3:
		cout << "��������м����������: " << endl;
		cin >> b1 >> b2;
			MyMuti(b1, b2);
			break;
		case 4:
		cout << "��������м������: " << endl;
		cin >> b1 ;
			MyFact(b1);
			break;
		}
		cout << endl;
	} while (1);
	return 0;
}