#include"Triangle.h"

int main() {
	int choose;
	cout << ">�������б����<" << endl;
	do {
		cout << "ϣ��������λС��(��ȷ��С�����λ) ��" << endl;
		int precision;
		cin >> precision;
		Point p[3];
		double x, y;
		for (int i = 0; i < 3; i++) {
			cout << "������� "<< 1+i << " �����x y���꣨�Կո������ ��" << endl;
			cin >> x >> y;
			p[i].setX(x); p[i].setY(y);
		}
		Triangle t(p[0], p[1], p[2]);
		t.typeJudge(precision);
		cout << "�����ж��� ��(�ǣ�1/��0) ";
		cin >> choose;
	} while (choose);
	cout << "�����˳��� ��лʹ��" << endl;
	return 0;
}