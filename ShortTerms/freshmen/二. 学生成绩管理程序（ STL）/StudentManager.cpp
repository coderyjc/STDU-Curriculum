#include "StudentManager.h"
#include<algorithm>
#include<fstream>
#include<sstream>

void StudentManager::importFiles() {
	system("cls");
	cout << ">正在导入学生文件<" << endl
		<< "请选择导入文件的数据形式: " << endl
		<< "1. 学生名单" << endl
		<< "2. 学号 学生姓名" << endl
		<< "3. 本程序导出类型" << endl
		<< "\n注意:所有学生默认在一个班级\n学号默认为1/2/3...以此类推\n不过不用担心，这些都可以修改\n" << endl
		<< "请输入您的选择: " << endl;
	int choose;
	cin >> choose;
	cout << "请输入文件所在的完整路径:";
	string path;
	cin >> path;
	ifstream ifs(path, ios::in);
	if (!ifs) {
		cout << "文件打开失败，确认后重新输入: " << endl;
		cin >> path;
		ifs.open(path, ios::in);
		if (!ifs) {
			cout << "两次输入错误，程序退出" << endl; 
			system("cls");
			return;
		}
	}
	cout << "是否将该路径作为文件默认保存的路径(是:1/否:0) ？" << endl;
	int isPath = 0;
	cin >> isPath;
	if (isPath == 1) this->filePath = path;
	else if (isPath == 0) cout << "未设置为默认保存路径" << endl;
	else cout << "输入有误，默认保存路径设置为该程序同目录下的studentInfo.txt" << endl;
	ifs.close();
	switch (choose) {
	case 1: this->readFile01(path); break;
	case 2: this->readFile02(path); break;
	case 3: this->readFile03(path); break;
	default:cout << "输入有误，请重新进入" << endl; return;
	}
	system("pause");
	system("cls");
}

void StudentManager::readFile01(string fileName) {
	//Student List
	ifstream ifs(fileName, ios::in);
	string name;
	int i = 1;
	cout << "请输入学生所在班级: " << endl;
	string clas;
	cin >> clas;
	if (this->m_Classes.find(clas) != m_Classes.end()) {
		cout << "班级已存在，请重试" << endl;
		return;
	}
	while (!ifs.eof()) {
		ifs >> name;
		string temp = to_string(i);
		this->m_Classes[clas].addStudentsForTheClass(name, temp);
		AllStudent.push_back(temp);
		i++;
	}
	this->m_Classes[clas].setClassName(clas);
	cout << "文件读取成功" << endl;
	ifs.close();
}

void StudentManager::readFile02(string fileName) {
	//number and name
	ifstream ifs(fileName, ios::in);
	string name;
	string number;
	cout << "请输入学生所在班级: " << endl;
	string clas;
	cin >> clas;
	if (this->m_Classes.find(clas) != m_Classes.end()) {
		cout << "班级已存在，请重试" << endl;
		return;
	}
	while (!ifs.eof()) {
		ifs >> number >> name;
		AllStudent.push_back(number);
		this->m_Classes[clas].addStudentsForTheClass(name, number);
	}
	this->m_Classes[clas].setClassName(clas);
	ifs.close();
	cout << "文件读取成功" << endl;
}	

void StudentManager::readFile03(string fileName) {
	//default
	ifstream ifs(fileName, ios::in);
	string clasName;
	int subNum;
	do {
		ifs >> clasName >> subNum;
		TeachingClasses temp;
		string subs;
		for (int i = 0; i < subNum; i++) {
			ifs >> subs;
			temp.simplyAddSubjects(subs);
		}
		int totalStud;
		ifs >> totalStud;
		string stuTempNum, stuTempName;
		double tempScore;
		map<string, double> stuTempScores;
		for (int i = 0; i < totalStud; i++) {
			ifs >> stuTempNum >> stuTempName;
			AllStudent.push_back(stuTempNum);
			for (int i = 0; i < subNum; i++) {
				ifs >> tempScore;
				stuTempScores[temp.getsubjects()[i]] = tempScore;
			}
			StudentInfo s(stuTempName, stuTempNum, stuTempScores);
			temp.addStudentsForTheClass(make_pair(stuTempNum, s));
		}
		this->m_Classes.insert(make_pair(clasName, temp));
	} while (!ifs.eof());
	ifs.close();
	cout << "文件读取成功" << endl;
}

void StudentManager::saveFiles() {
	system("cls");
	cout << ">正在保存文件<" << endl
		<< "您当前的文件保存路径为：" << this->filePath << endl
		<< "是否要更改文件保存路径？(是:1/否:0)" << endl;
	int choose;
	cin >> choose;
	if (choose == 1) {
		cout << "请输入文件保存路径:";
		cin >> this->filePath;
	} else cout << "保存路径未更改" << endl;
	ofstream ofs(filePath, ios::trunc);
	for (auto klass : this->m_Classes) {
		vector<string> subs = klass.second.getsubjects();
		map<string, StudentInfo> stus = klass.second.getStudents();
		ofs << klass.first << '\t' << subs.size() << '\t';
		for (int i = 0; i < subs.size(); i++) ofs << subs[i] << '\t';
		ofs << klass.second.getStudents().size() << endl;
		for (auto student : stus) {
			ofs << student.first << '\t'
				<< student.second.getName() << '\t';
			map<string, double> scores = student.second.getScores();
			for (int i = 0; i < subs.size(); i++) {
				ofs << scores[subs[i]] << '\t';
			}
			ofs << endl;
		}
	}
	ofs.close();
	cout << "文件保存成功" << endl;
	system("pause");
	system("cls");
}

void StudentManager::addNewTeachingClasses() {
	system("cls");
	cout << ">正在添加新的教学班<" << endl;
	string newClassName;
	cout << "请输入新的教学班的名称 : ";
	cin >> newClassName;
	if (this->m_Classes.size() != 0 && this->m_Classes.find(newClassName) != this->m_Classes.end()) {
		cout << "教学班名称重复，请重新输入" << endl;
		cin >> newClassName;
		if (this->m_Classes.size() != 0 && this->m_Classes.find(newClassName) != this->m_Classes.end()) {
			cout << "两次重复，自动退出" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	TeachingClasses temp;
	temp.setClassName(newClassName);
	this->m_Classes.insert(make_pair(newClassName, temp));
	cout << "教学班添加成功" << endl;
	system("pause");
	system("cls");
}

void StudentManager::addNewSubjectsForTeachingClasses() {
	system("cls");
	if (!this->noClasses()) return;
	cout << ">正在添加新的课程<" << endl;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入要添加课程的教学班的名称：";
	string nameToAddStudent;
	cin >> nameToAddStudent;
	if ( m_Classes.find(nameToAddStudent) == m_Classes.end()) {
		cout << "输入有误，请重新输入" << endl; //没找到
		cin >> nameToAddStudent;
		if (m_Classes.find(nameToAddStudent) == m_Classes.end()) {
			cout << "两次错误，请重试"<<endl;
			system("pause");
			system("cls");
			return;
		}
	}
	this->m_Classes[nameToAddStudent].addNewSubjects();
	system("pause");
	system("cls");
}

void StudentManager::addNewStudentForATeachingClass() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">正在为指定教学班添加新的学生<" << endl;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入想要添加学生的教学班名称 :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClasses>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "输入有误，请重新输入" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "两次错误，请重试" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else 
		(*it).second.addStudentsForTheClass();
	system("pause");
	system("cls");
}

void StudentManager::printSingleClassInfo() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入想要显示信息的教学班名称 :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClasses>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "输入有误，请重新输入" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "两次错误，请重试" << endl;
			return;
		} else it = m_Classes.find(clasName);
	}
	system("cls");
	(*it).second.printStudentInfo();
	system("pause");
	system("cls");
}

void StudentManager::orderedPrintSingleClassInfo() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入想要排序的教学班名称 :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClasses>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end())  {
		cout << "输入有误，请重新输入" << endl;
			cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "两次错误，请重试" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else (*it).second.orderedStudentScore();
	system("pause");
	system("cls");
}

void StudentManager::delSubjectForClass() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">正在取消课程<" << endl;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	string ClasTobeDel;
	cout << "请输入要取消课程的班级: ";
	cin >> ClasTobeDel;
	if (this->m_Classes.find(ClasTobeDel) == m_Classes.end()) {
		cout << "查无此班" << endl;
		system("pause");
		system("cls");
		return;
	}
	else {
		this->m_Classes[ClasTobeDel].delASubject();
		system("pause");
		system("cls");
	}
}

void StudentManager::findStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">正在查找指定学生<" << endl;
	cout << "请输入您要查找的学生的学号：";
	string numToBeFound;
	cin >> numToBeFound;
	if (find(AllStudent.begin(), AllStudent.end(), numToBeFound) == AllStudent.end())
		cout << "很抱歉，查无此人" << endl;
	else 
		for (auto classes : this->m_Classes) {
			map<string, StudentInfo> mp = classes.second.getStudents();
			map<string, StudentInfo>::iterator it = mp.find(numToBeFound);
			if (it != mp.end()) classes.second.showSingleInfo(numToBeFound);
		}
	system("pause");
	system("cls");
}

void StudentManager::deleteStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">正在删除某学生<" << endl;
	cout << "请输入您要删除的学生的学号：";
	string numToBeDel;
	cin >> numToBeDel;
	string className;
	if (find(AllStudent.begin(), AllStudent.end(), numToBeDel) == AllStudent.end()){
		cout << "很抱歉，查无此人" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (auto classes : this->m_Classes) {
		map<string, StudentInfo> mp = classes.second.getStudents();
		map<string, StudentInfo>::iterator it = mp.find(numToBeDel);
		if (it != mp.end()) {
			cout << "请确认该生的信息\n" << endl;
			classes.second.showSingleInfo(numToBeDel);
 			className = classes.first;
		}
	}
	cout << "确认删除？（是:1/否:0）：";
	int del;
	cin >> del;
	if (!del) {
		cout << "取消删除" << endl;
		system("pause");
		system("cls");
		return;
	} else if (del == 1) {
		this->m_Classes[className].delAStudentInTheClass(numToBeDel);
		AllStudent.erase(find(AllStudent.begin(), AllStudent.end(), numToBeDel));
		cout << "删除成功" << endl;
	} else cout << "输入有误" << endl;
	system("pause");
	system("cls");
	return;
}

void StudentManager::updateStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">正在更新某学生信息<" << endl;
	system("cls");
	cout << "请输入您要更新的学生的学号：";
	string numToBeFound;
	string className;
	pair<string, StudentInfo> newStudent;
	cin >> numToBeFound;
	if (find(AllStudent.begin(), AllStudent.end(), numToBeFound) == AllStudent.end()) {
		cout << "很抱歉，查无此人" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (auto classes : this->m_Classes) {
		map<string, StudentInfo> mp = classes.second.getStudents();
		map<string, StudentInfo>::iterator it = mp.find(numToBeFound);
		if (it != mp.end()) {
			cout << "请确认该生的信息\n" << endl;
			classes.second.showSingleInfo(numToBeFound);
			className = classes.first;
		}
	}
	this->m_Classes[className].updateAStudentInTheClass(numToBeFound);
	cout << "更新成功" << endl;
	system("pause");
	system("cls");
	return;
}

class OverallSort {
public:
	bool operator()(pair<string, StudentInfo> p1, pair<string, StudentInfo> p2) {
	return p1.second.getTotalScore() > p2.second.getTotalScore();
	}
};

void StudentManager::GreadRanking() {
	system("cls");
	vector<pair<string, StudentInfo>> allStud;
	for (auto classes : m_Classes) {
		classes.second.calculateTotalScore();
		for (auto studs : classes.second.getStudents()) {
			studs.second.setClass(classes.first);
			allStud.push_back(studs);
		}
	}
	sort(allStud.begin(), allStud.end(), OverallSort());
	cout << "排名\t班级\t学号\t姓名\t平均分" << endl;
	for (int i = 0; i < allStud.size(); i++) {
		cout << i + 1 << "\t" << allStud[i].second.getClas() << "\t"
			<< allStud[i].second.getNumber() << "\t"
			<< allStud[i].second.getName() << "\t"
			<< allStud[i].second.getAverScore() << endl;
	}
	system("pause");
	system("cls");
}

void StudentManager::printOverallScores() {
	system("cls");
	map<string, TeachingClasses>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		cout << (*it).first << "班成绩单\n" << endl;
		(*it).second.printStudentInfo();
		cout << endl;
	}
	system("pause");
	system("cls");
	return;
}

void StudentManager::setScoresForClass() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">正在录入成绩<" << endl;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	string ClasToImport;
	cout << "请输入要录入成绩的班级: ";
	cin >> ClasToImport;
	if (this->m_Classes.find(ClasToImport) == m_Classes.end()) {
		cout << "查无此班" << endl;
		system("pause");
		system("cls");
		return;
	} else {
		this->m_Classes[ClasToImport].importScores();
		system("pause");
		system("cls");
	}
}

void StudentManager::delClass() {
	system("cls");
	if (!this->noClasses()) return;
	cout << "正在删除教学班" << endl;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	string ClasTobeDel;
	cout << "请输入要删除的班级: ";
	cin >> ClasTobeDel;
	if (this->m_Classes.find(ClasTobeDel) == m_Classes.end()) {
		cout << "查无此班" << endl;
		system("pause");
		system("cls");
		return;
	} else {
		cout << "删除班级会将班中的学生一并删除，是否继续？（是1/否0） ";
		int flag; cin >> flag;
		if (flag == 1) {
			this->m_Classes.erase(this->m_Classes.find(ClasTobeDel));
			cout << "删除成功" << endl;
		}
	}
	system("pause");
	system("cls");
}

void StudentManager::clear() {
	system("cls");
	cout << "正在清空数据" << endl;
	cout << "请计算并输入3/11的结果的前6位小数：";
	int flag1; cin >> flag1;
	if (flag1 == 272727) {
		cout << "确认删除？(是1/否0)" << endl;
		cin >> flag1;
		if (flag1 == 1) {
			this->m_Classes.clear();
			cout << "删除成功" << endl;
		} else cout << "取消删除" << endl;
	} else cout << "取消删除" << endl;
	system("pause");
	system("cls");
}

int StudentManager::showMenu() {
	cout << "\t\t欢迎使用学生信息管理系统v1.3" << endl
		<< "------------------------------------------------------" << endl
		<< "1 . 从文件导入学生信息\t\t2 . 添加新的教学班\n" << endl
		<< "3 . 为指定教学班添加课程\t4 . 录入某班学生某门课的成绩\n" << endl
		<< "5 . 为指定教学班取消课程\t6 . 为指定教学班添加学生\n" << endl
		<< "7 . 显示出某教学班全部学生信息\t8. 对指定教学班的学生进行排序\n" << endl
		<< "9. 查找某学生信息\t\t10. 删除某学生信息\n" << endl
		<< "11. 修改某学生信息\t\t12. 根据平均分对学生进行年级排名\n" << endl
		<< "13. 查看所有班级的学生的成绩\t14. 导出所有学生的成绩\n" << endl
		<< "15. 删除教学班\t\t\t16. 清空所有数据\n" << endl
		<< "0 . 退出程序\n" << endl
		<< "请输入您的选择" << endl;
	int choose; cin >> choose;
	return choose;
}

bool StudentManager::noClasses() {
	if (this->m_Classes.size() == 0) {
		cout << "目前没有教学班，是否立即添加教学班 ？（是：1/否：0）" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			this->addNewTeachingClasses();
			return 1;
		} else {
			cout << "取消添加教学班" << endl;
			system("pause");
			system("cls");
			return 0;
		}
	} else return 1;
}

bool StudentManager::noStudents() {
	if (AllStudent.size() == 0) {
		cout << "目前没有学生， 是否立即向教学班添加学生？（是：1/否：0）" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			this->addNewStudentForATeachingClass();
			return 1;
		} else {
			cout << "取消添加学生" << endl;
			system("pause");
			system("cls");
			return 0;
		}
	} else return 1;
}