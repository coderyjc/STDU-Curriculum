#include"StudentManager.h"

int main() {
	StudentManager sm;
	int choose = 0;
	do{
		sm.showMenu();
		cout << "请输入你的选择 ：";
		cin >> choose;
		switch (choose) {
			case 1: sm.createFiles(); break;
			case 2: sm.importFile(); break;
			case 3: sm.showAllInfo(); break;
			case 4: sm.addStudent(); break;
			case 5: sm.deleteStudent(); break;
			case 6: sm.updateStudent(); break;
			case 7: sm.findStudentInfo(); break;
			case 8: sm.sigmaScores(); break; 
			case 9: sm.sortScores(); break;
			case 10:sm.saveFile(); break; 
			case 11: sm.insertStudent(); break;
			case 0: cout << "\n\t程序即将退出，感谢您的使用。\n" << endl; exit(0);
			default: cout << "输入有误，请重新输入..." << endl; break;
		}
	} while (choose);
	return 0;
}