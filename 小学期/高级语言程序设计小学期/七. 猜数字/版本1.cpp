//#include<iostream>
//#include<cstdlib>
//#include<ctime>
//using namespace std;
//int main() {
//  srand(time(NULL));
//  int flag = 0;
//  do {
//	  int gameTime, guess, rst = rand() % 10001 + 1;
//	cout << "请输入游戏时间(秒)：" << endl;
//	cin >> gameTime;
//	string result;
//	time_t now = time(0);
//	do {
//		cout << "请输入您猜的数字：" << endl;
//		cin >> guess;
//		if (time(0) > now + gameTime) {
//			cout << "不好意思，时间到了，正确答案是" << rst << endl;
//			break;
//		}
//		if (rst > guess)
//			cout << "低了 " << endl;
//		else if (rst < guess)
//			cout << "高了" << endl;
//		else cout << "恭喜！正确猜出数字"<< rst << endl;
//	} while (rst != guess);
//	cout << "是否要再来一局 ？(是1/否0)" << endl;
//	cin >> flag;
//	if (flag) system("cls");
//  } while (flag);
//	return 0;
//}