#include "StudentManager.h"
#include<fstream>
#include<algorithm>

StudentManager::StudentManager() {
	filePath = "studentInfo.txt";
	account = 0;
}

void StudentManager::Login() {
	this->autoImport("studentInfo.txt");
	int flag = 0;
	long number;
	long password;
	do {
		system("cls");
		cout << "-----------------学生信息管理系统v1.5-------------------" << endl
			<< "\n\t\t请指定登录账户类型" << endl
			<< "\n\t\t1. root\n"
			<< "\n\t\t2. 学生\n" << endl
			<< "\n\t\t0. 退出\n" << endl
			<< "\n\t请选择 ";
		do {
			cin >> this->account;
			if (0 > this->account || 3 < account) {
				cout << "输入有误，请重新输入！" << endl;
				flag = 1;
			} else flag = 0;
		} while (flag);
		if (this->account == 0) return;
		switch (account) {
		case 1: this->showRootMenu(); break;
		case 2:
			this->autoImport(filePath);
			cout << "\n请输入学号 :";
			cin >> number;
			if (find(AllStudent.begin(), AllStudent.end(), number) == AllStudent.end()) {
				cout << "系统中不存在此学号" << endl;
				system("pause");
				system("cls");
				break;
			} else {
				nowAct = this->isExist(number);
				cout << "请输入密码（默认为123456）：";
				cin >> password;
				if (password == 123456) {
					cout << "登陆成功" << endl;
					system("cls");
					this->showStuMenu();					
				}
				else
					cout << "密码错误" << endl;
			}
			break;
		case 0:return;
		default: cout << "输入有误，退出" << endl; break;
		}
	} while (1);
}


void StudentManager::showRootMenu() {
	system("cls");
	int choose;
	do {
		cout << "-----------------学生信息管理系统v1.5--ROOT模式------------------\n" << endl;
		cout << "文件操作：1. 导入学生信息\t2.创建信息文件\t\t3. 存文件\n" << endl
			<< "班级操作：4. 增加班级\t\t5. 为某班级开课\t\t6. 为某班级退课\n" << endl
			<< "\t  7. 录入班级学生成绩\t8. 显示班级成绩单 \t9. 删除班级\n " << endl
			<< "学生操作：10. 增加学生\t\t11. 更新学生信息\t12. 查找学生信息\n" << endl
			<< "\t  13. 删除学生信息\t14. 单个学生选课\t15. 单个学生退课\n" << endl
			<< "全局操作：16. 显示年级大排名\t17. 清空所有数据\n" << endl
			<< "其他操作：18. 指定成绩单排序方式\n\n0. 返回上一层\n" << endl
			<< "请选择进行的操作：";
		cin >> choose;
		switch (choose) {
		case 1:this->importFiles(); break;
		case 2:this->createFile(); break;
		case 3:this->saveFile(); break;
		case 4:this->addClass(); autoSaveFile(); break;
		case 5:this->addSubjectForClass();  autoSaveFile(); break;
		case 6:this->delSubjectForClass(); autoSaveFile(); break;
		case 7:this->setScoresForClass(); autoSaveFile(); break;
		case 8:this->showClasInfo(); break;
		case 9:this->delClass(); autoSaveFile(); break;
		case 10:this->addStudent(); autoSaveFile(); break;
		case 11:this->updateStudent(); autoSaveFile(); break;
		case 12:this->findStudent(); break;
		case 13:this->delStudent(); autoSaveFile(); break;
		case 14:this->addSubForSingle(); autoSaveFile(); break;
		case 15:this->delClasForSingle(); autoSaveFile(); break;
		case 16:this->showGradeInfo(); break;
		case 17:this->clear(); break;
		case 18:this->setOrder(); break;
		case 0: break;
		default: 
			cout << "输入有误，重新输入" << endl; 
			system("cls");
			break;
		}
	} while (choose);
}


void StudentManager::showStuMenu() {
	int choose;
	do {
		cout << "-----------------学生信息管理系统v1.5--学生模式------------------\n" << endl;
		cout << "1. 显示班级成绩单\n " << endl
			<< "2. 查看学生信息\n" << endl
			<< "3. 选课\n" << endl
			<< "4. 退课\n" << endl
			<< "0. 返回上一层\n" << endl
			<< "请选择进行的操作：";
		cin >> choose;
		switch (choose) {
		case 1:this->showClasInfo(); break;
		case 2:this->findStudent(); break;
		case 3:this->addSubForSingle(nowAct->data.getNumber()); break;
		case 4:this->delClasForSingle(nowAct->data.getNumber()); break;
		case 0:this->Login(); break;
		default: cout << "输入有误，重新输入"; break;
		}
	} while (choose);
}


void StudentManager::importFiles() {
	system("cls");
	cout << ">正在导入学生文件<" << endl
		<< "请选择导入文件的数据形式: " << endl
		<< "1. 学生名单" << endl
		<< "2. 学号 学生姓名" << endl
		<< "3. 本程序导出类型" << endl
		<< "0. 返回上一层" << endl
		<< "\n注意:所有学生默认在一个班级\n学号默认为1/2/3...以此类推\n不过不用担心，这些都可以修改\n" << endl
		<< "请输入您的选择: " << endl;
	int choose;
	cin >> choose;
	if (choose == 0) {
		system("cls");
		return;
	}
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

	string tempName;
	long tempNumber;
	string tempClassName;
	int flag = 1;


	TeachingClass tempClass(tempClassName);

	switch (choose) {
	case 1:
		do {
			cout << "请输入这些学生所在的班级：";
			cin >> tempClassName;
			if (m_Classes.find(tempClassName) == m_Classes.end()) flag = 0;
			else cout << "班级重复，请重新输入" << endl;
		} while (flag);
		for (int i = 1; !ifs.eof(); i++) {
			ifs >> tempName;
			AllStudent.push_back(i);
			studentInfo temp(tempClassName, i, tempName);
			tempClass.insertStudent(temp);
		}
		m_Classes.insert(make_pair(tempClassName, tempClass));
		break;
	case 2:
		do {
			cout << "请输入这些学生所在的班级：";
			cin >> tempClassName;
			if (m_Classes.find(tempClassName) == m_Classes.end()) flag = 0;
			else cout << "班级重复，请重新输入" << endl;
		} while (flag);
		for (int i = 1; !ifs.eof(); i++) {
			ifs >> tempNumber >> tempName;
			AllStudent.push_back(tempNumber);
			studentInfo temp(tempClassName, tempNumber, tempName);
			tempClass.insertStudent(temp);
		}
		m_Classes.insert(make_pair(tempClassName, tempClass));
		break;
	case 3: this->autoImport(path);	break;
	}
	ifs.close();
	cout << "文件导入成功！" << endl;
	system("pause");
 	system("cls");
}

void StudentManager::autoImport(string path) {
	ifstream ifs("studentInfo.txt", ios::in);
	if (!ifs) return;
	while (!ifs.eof()) {
		vector<string> tempReqSubs;
		string tempClasName;
		int numOfReqSubs;
		ifs >> tempClasName >> numOfReqSubs;
		TeachingClass tempClass(tempClasName);
		for (int i = 0; i < numOfReqSubs; i++) {
			string tempSubs;
			ifs >> tempSubs;
			tempReqSubs.push_back(tempSubs);
		}
		tempClass.setSubjects(tempReqSubs);
		int numOfStus;
		ifs >> numOfStus;
		for (int i = 0; i < numOfStus; i++) {
			long tempNumber;
			string subName;
			double subScore;
			map<string, double> tempScore;
			map<string, double> tempOther;
			string tempName;
			ifs >> tempNumber >> tempName;
			ifs >> numOfReqSubs;
			AllStudent.push_back(tempNumber);
			for (int j = 0; j < numOfReqSubs; j++) {
				ifs >> subName >> subScore;
				tempScore.insert(make_pair(subName, subScore));
			}
			int numOfOthers;
			ifs >> numOfOthers;
			for (int j = 0; j < numOfOthers; j++) {
				ifs >> subName >> subScore;
				tempOther.insert(make_pair(subName, subScore));
			}
			studentInfo tempStu(tempClasName, tempNumber, tempName, tempScore,  tempOther);
			tempClass.insertStudent(tempStu);
		}
		this->m_Classes.insert(make_pair(tempClasName, tempClass));
	}
	ifs.close();
}


void StudentManager::createFile() {
	system("cls");
	cout << "当前的文件所在位置为：" << this->filePath << endl;
	cout << "是否要更改文件位置？（是1/否0）";
	int choose; cin >> choose;
	if (choose == 1) {
		cout << "请输入新的文件保存位置：";
		cin >> this->filePath;
		cout << "文件位置设置成功" << endl;
	} else if (choose == 0) {
		cout << "未更改" << endl;
	} else cout << "输入有误" << endl;
	system("pause");
	system("cls");
}


void StudentManager::addClass() {
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
	TeachingClass temp(newClassName);
	this->m_Classes.insert(make_pair(newClassName, temp));
	cout << "教学班添加成功" << endl;
	system("pause");
	system("cls");
}


void StudentManager::addSubjectForClass() {
	system("cls");
	if (!this->noClasses()) return;
	cout << ">正在添加新的课程<" << endl;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入要添加课程的教学班的名称：";
	string nameToAddStudent;
	cin >> nameToAddStudent;
	if (m_Classes.find(nameToAddStudent) == m_Classes.end()) {
		cout << "输入有误，请重新输入" << endl; //没找到
		cin >> nameToAddStudent;
		if (m_Classes.find(nameToAddStudent) == m_Classes.end()) {
			cout << "两次错误，请重试" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	this->m_Classes[nameToAddStudent].addNewSubjects();
	system("pause");
	system("cls");
}


void StudentManager::delSubjectForClass() {
	system("cls");
	if (!this->noClasses()) return;
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
	} else {
		this->m_Classes[ClasTobeDel].delSubject();
		system("pause");
		system("cls");
	}
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


void StudentManager::addStudent() {
	system("cls");
	if (!this->noClasses()) return;
	cout << ">正在为指定教学班添加新的学生<" << endl;
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入想要添加学生的教学班名称 :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClass>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "输入有误，请重新输入" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "两次错误，请重试" << endl;
			system("pause");
			system("cls");
			return;
		}
	} else
		(*it).second.addStudents();
	system("pause");
	system("cls");

}


void StudentManager::delStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">正在删除某学生<" << endl;
	cout << "请输入您要删除的学生的学号：";
	long numToBeDel;
	cin >> numToBeDel;
	string className;

	if (find(AllStudent.begin(), AllStudent.end(), numToBeDel) == AllStudent.end()) {
		cout << "很抱歉，查无此人" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (auto classes : this->m_Classes) {
		NodePosi(studentInfo) it = classes.second.isExist(numToBeDel);
		if (it) {
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
	if (nowAct) {
		this->m_Classes[nowAct->data.getClass()].updateStudent(nowAct->data.getNumber());
		system("pause");
		system("cls");
		return;
	}
	cout << ">正在更新某学生<" << endl;
	cout << "请输入您要更新的学生的学号：";
	long numToBeUp;
	cin >> numToBeUp;
	string className;

	if (find(AllStudent.begin(), AllStudent.end(), numToBeUp) == AllStudent.end()) {
		cout << "很抱歉，查无此人" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (auto classes : this->m_Classes) {
		NodePosi(studentInfo) it = classes.second.isExist(numToBeUp);
		if (it) {
			cout << "请确认该生的信息\n" << endl;
			classes.second.showSingleInfo(numToBeUp);
			className = classes.first;
		}
	}
	this->m_Classes[className].updateStudent(numToBeUp);
	cout << "更新成功" << endl;
	system("pause");
	system("cls");
	return;
}

void StudentManager::findStudent() {
	system("cls");
	if(!this->noClasses()) return;
	if (!this->noStudents()) return;
	if (nowAct) {
		this->m_Classes[nowAct->data.getClass()].showSingleInfo(nowAct->data.getNumber());
		system("pause");
		system("cls");
		return;
	}
	cout << ">正在查询某学生<" << endl;
	cout << "请输入您要查询的学生的学号：";
	long numToBeFound;
	cin >> numToBeFound;
	string className;

	if (find(AllStudent.begin(), AllStudent.end(), numToBeFound) == AllStudent.end()) {
		cout << "很抱歉，查无此人" << endl;
		system("pause");
		system("cls");
		return;
	} else 
		for (auto classes : this->m_Classes) {
			NodePosi(studentInfo) it = classes.second.isExist(numToBeFound);
			if (it) {
				cout << "请确认该生的信息\n" << endl;
				classes.second.showSingleInfo(numToBeFound);
				className = classes.first;
			}
		}

	system("pause");
	system("cls");
	return;
}


void StudentManager::addSubForSingle(long number) {
	system("cls");
	if (number == -1) {
		cout << "请输入要添加课程的学生的学号：";
		cin >> number;
		if (find(AllStudent.begin(), AllStudent.end(), number) == AllStudent.end()) {
			cout << "查无此生" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		if ((*it).second.isExist(number)) {
			(*it).second.addSubForSingle(number);
			break;
		}
	}
	cout << "添加成功" << endl;
	system("pause");
	system("cls");
	return;
}


void StudentManager::delClasForSingle(long number) {
	system("cls");
	if (number == -1) {
		cout << "请输入要取消课程的学生的学号：";
		cin >> number;
		if (find(AllStudent.begin(), AllStudent.end(), number) == AllStudent.end())
			cout << "查无此生" << endl;
	}
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		if ((*it).second.isExist(number)) {
			(*it).second.delSubForSingle(number);
			break;
		}
	}
	system("pause");
	system("cls");
	return;
}


void StudentManager::showClasInfo() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	this->TotalAndAver();
	if (nowAct) {
		this->m_Classes[nowAct->data.getClass()].showClasInfo();
		system("pause");
		system("cls");
		return;
	}
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入想要显示信息的教学班名称 :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClass>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "输入有误，请重新输入" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "两次错误，请重试" << endl;
			system("pause");
			system("cls");
			return;
		} else it = m_Classes.find(clasName);
	}
	system("cls");
	(*it).second.showClasInfo();
	system("pause");
	system("cls");
	return;
}

class sortByScore {
public:
	bool operator()(studentInfo stu1, studentInfo stu2) {
		return stu1.getAver() > stu2.getAver();
	}
};

void StudentManager::showGradeInfo() {
	system("cls");
	m_Classes.erase("");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	this->TotalAndAver();
	vector<studentInfo> allStu;
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		NodePosi(studentInfo) p = (*it).second.getFirstStus();
		while (p->suc) {
			allStu.push_back(p->data);
			p = p->suc;
		}
	}
	sort(allStu.begin(), allStu.end(), sortByScore());
	cout << "排名\t" << "班级\t" << "学号\t" << "姓名\t" << "平均分" << endl;
	for (int i = 0; i < allStu.size(); i++) {
		cout << i + 1 << "\t" 
			<< allStu[i].getClass() << "\t"
			<< allStu[i].getNumber() << "\t"
			<< allStu[i].getName() << "\t"
			<< allStu[i].getAver() << endl;
	}
	system("pause");
	system("cls");
	return;
}


void StudentManager::setOrder() {
	system("cls");
	cout << "现在有教学班：" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "请输入要排序的班级：";
	string clasName;
	cin >> clasName;
	map<string, TeachingClass>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "输入有误，请重新输入" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "两次错误，请重试" << endl;
			system("pause");
			system("cls");
			return;
		} else it = m_Classes.find(clasName);
	}
	(*it).second.setSort();
	cout << "排序成功" << endl;
	system("pause");
	system("cls");
	return;
}


void StudentManager::saveFile() {
	cout << "正在保存文件" << endl;
	cout << "现在的文件保存路径为 ：" << this->filePath << endl;
	cout << "是否更改文件保存路径(是1/否0) ：";
	int choose; cin >> choose;
	if (choose == 1) {
		cout << "请输入文件保存路路径：";
		cin >> this->filePath;
		cout << "设置成功" << endl;
	} else cout << "未更改文件保存路径" << endl;
	this->autoSaveFile();
	cout << "文件保存成功" << endl;
	system("pause");
	system("cls");
	return;
}

void StudentManager::autoSaveFile() {
	ofstream ofs(filePath, ios::out);
	for (auto clas : this->m_Classes) {
		ofs << clas.first << " " << clas.second.getRequiredSubs().size() << " ";
		for (int i = 0; i < clas.second.getRequiredSubs().size(); i++) 
			ofs << clas.second.getRequiredSubs()[i] << " ";
		ofs << clas.second.getNumberOfStu() << endl;
		for (NodePosi(studentInfo) temp = clas.second.getFirstStus(); temp->suc != NULL; temp = temp->suc) {
			ofs << temp->data.getNumber() << " " << temp->data.getName() << " ";

			map<string, double> tempScore = temp->data.getScores();
			ofs << tempScore.size() << " ";
			for(map<string, double>::iterator it = tempScore.begin(); it != tempScore.end(); it++)
				ofs << (*it).first << " " << (*it).second << " ";

			map<string, double> tempScore2 = temp->data.getOtherScores();
			ofs << tempScore2.size() << " ";
			for (map<string, double>::iterator it = tempScore2.begin(); it != tempScore2.end(); it++)
				ofs << (*it).first << " " << (*it).second << " ";
			ofs << endl;
		}
	}
	ofs.close();
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


bool StudentManager::noClasses() {
	if (this->m_Classes.size() == 0) {
		cout << "目前没有教学班，是否立即添加教学班 ？（是：1/否：0）" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			this->addClass();
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
			this->addStudent();
			return 1;
		} else {
			cout << "取消添加学生" << endl;
			system("pause");
			system("cls");
			return 0;
		}
	} else return 1;
}

void StudentManager::TotalAndAver() {
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		(*it).second.TotalAndAver();
	}
}

NodePosi(studentInfo) StudentManager::isExist(long number) {
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++)
		if ((*it).second.isExist(number))
			return (*it).second.isExist(number);	
}
