//#include<iostream>
//#include<cstdlib>
//#include<ctime>
//using namespace std;
//int main() {
//  srand(time(NULL));
//  int flag = 0;
//  do {
//	  int gameTime, guess, rst = rand() % 10001 + 1;
//	cout << "��������Ϸʱ��(��)��" << endl;
//	cin >> gameTime;
//	string result;
//	time_t now = time(0);
//	do {
//		cout << "���������µ����֣�" << endl;
//		cin >> guess;
//		if (time(0) > now + gameTime) {
//			cout << "������˼��ʱ�䵽�ˣ���ȷ����" << rst << endl;
//			break;
//		}
//		if (rst > guess)
//			cout << "���� " << endl;
//		else if (rst < guess)
//			cout << "����" << endl;
//		else cout << "��ϲ����ȷ�³�����"<< rst << endl;
//	} while (rst != guess);
//	cout << "�Ƿ�Ҫ����һ�� ��(��1/��0)" << endl;
//	cin >> flag;
//	if (flag) system("cls");
//  } while (flag);
//	return 0;
//}