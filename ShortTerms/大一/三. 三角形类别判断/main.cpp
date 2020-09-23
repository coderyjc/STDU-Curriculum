#include"Triangle.h"

int main() {
	int choose;
	cout << ">三角形判别程序<" << endl;
	do {
		cout << "希望保留几位小数(精确到小数点后几位) ？" << endl;
		int precision;
		cin >> precision;
		Point p[3];
		double x, y;
		for (int i = 0; i < 3; i++) {
			cout << "请输入第 "<< 1+i << " 个点的x y坐标（以空格隔开） ：" << endl;
			cin >> x >> y;
			p[i].setX(x); p[i].setY(y);
		}
		Triangle t(p[0], p[1], p[2]);
		t.typeJudge(precision);
		cout << "继续判定吗 ？(是：1/否：0) ";
		cin >> choose;
	} while (choose);
	cout << "程序退出， 感谢使用" << endl;
	return 0;
}