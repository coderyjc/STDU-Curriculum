#include"StudentManager.h"

int main() {

	StudentManager sm;
	int choose = 0;
	while (1) {
		switch (sm.showMenu()) {
		case 1:sm.importFiles(); break;
		case 2:sm.addNewTeachingClasses(); break;
		case 3:sm.addNewSubjectsForTeachingClasses(); break;
		case 4:sm.setScoresForClass(); break;
		case 5:sm.delSubjectForClass(); break;
		case 6:sm.addNewStudentForATeachingClass(); break;
		case 7:sm.printSingleClassInfo(); break;
		case 8:sm.orderedPrintSingleClassInfo(); break;
		case 9:sm.findStudent(); break;
		case 10:sm.deleteStudent(); break;
		case 11:sm.updateStudent(); break;
		case 12:sm.GreadRanking(); break;
		case 13:sm.printOverallScores(); break;
		case 14:sm.saveFiles(); break; 
		case 15:sm.delClass(); break; 
		case 16:sm.clear(); break; 
		case 0: cout << "程序正在退出，感谢您的使用" << endl; return 0;
		default: cout << "输入有误，请重新输入" << endl; break;
		}
	}
	return 0;
}