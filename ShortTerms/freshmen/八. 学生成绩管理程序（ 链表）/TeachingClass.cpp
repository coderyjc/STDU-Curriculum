#include "TeachingClass.h"

TeachingClass::TeachingClass() {
	clasName = "null";
}

TeachingClass::~TeachingClass() {
}

TeachingClass::TeachingClass(string name) {
	this->clasName = name;
}

void TeachingClass::setSubjects(vector<string> subs) {
	this->RequiredSubjects = subs;
}

vector<string> TeachingClass::getRequiredSubs() {
	return this->RequiredSubjects;
}

NodePosi(studentInfo) TeachingClass::getFirstStus() {
	return this->stuList.first();
}

int TeachingClass::getNumberOfStu() {
	return this->stuList.size();
}

void TeachingClass::insertStudent(studentInfo stu) {
	this->stuList.insertAsLast(stu);
}

void TeachingClass::addNewSubjects() {
	cout << "请输入将要添加课程的数量: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "正在添加第 " << i + 1 << " 个课程" << endl;
		string subjectName;
		int flag = 1;
		do {
			cout << "请输入该课程的名称 : ";
			cin >> subjectName;
			if (find(RequiredSubjects.begin(), RequiredSubjects.end(), subjectName) != RequiredSubjects.end()) {
				cout << "课程已存在, 请重新输入" << endl;
				flag = 1;
			} else flag = 0;
		} while (flag);
		this->RequiredSubjects.push_back(subjectName);
		cout << "第 " << i + 1 << " 个课程添加成功\n" << endl;
	}
	cout << "课程添加完毕" << endl;

}

void TeachingClass::delSubject() {
	cout << "现在的课程有：";
	for (auto sub : this->RequiredSubjects) cout << sub << " ";
	cout << "\n请输入将要取消课程的名称：";
	string sub;
	cin >> sub;
	if (find(RequiredSubjects.begin(), RequiredSubjects.end(), sub) == RequiredSubjects.end()) {
		cout << "查无此课程" << endl;
		return;
	} else {
		cout << "删除课程的同时也会删除所有学生该课程的成绩 ! 是否继续？(是:1/否:0)" << endl;
		int choose;
		cin >> choose;
		if (choose != 1) {
			cout << "取消删除课程" << endl;
			system("pause");
			system("cls");
			return;
		} else {
			for (NodePosi(studentInfo) temp = this->stuList.first() ; temp != stuList.last()->suc ; temp = temp->suc) {
				temp->data.delSubject(sub);
			}
			this->RequiredSubjects.erase(find(RequiredSubjects.begin(), RequiredSubjects.end(), sub));
			cout << "删除成功" << endl;
		}
	}
}

void TeachingClass::importScores() {
	cout << "现有课程 : ";
	for (auto sub : this->RequiredSubjects) cout << sub << " ";
	cout << "\n录入哪门课的成绩？" << endl;
	double tempScore;
	string toImport;
	cin >> toImport;
	int i = 1;
	if (find(RequiredSubjects.begin(), RequiredSubjects.end(), toImport) == RequiredSubjects.end()) cout << "查无此课，请重试！" << endl;
	else {
		int i = 1;
		for (NodePosi(studentInfo) temp = stuList.first();  temp != stuList.last()->suc; temp = temp->suc) {
			cout << i++ << "/" << this->stuList.size() << " 请输入 " << temp->data.getNumber() << " " << temp->data.getName() << " 本门课的成绩 ：";
			cin >> tempScore;
			temp->data.setCertainScore(toImport, tempScore);
		}
		cout << "录入成功" << endl;
	}
}

void TeachingClass::addStudents() {
	cout << "请输入将要添加学生的数量: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		studentInfo tempInfo;
		cout << "正在添加第 " << i + 1 << " 个学生" << endl;
		int flag = 1;
		long studentNumber;
		do {
			cout << "请输入该学生的学号 : ";
			cin >> studentNumber;
			flag = find(AllStudent.begin(), AllStudent.end(), studentNumber) == AllStudent.end() ? 0 : 1;
			if (flag)
				cout << "学号重复, 请重新输入" << endl;
		} while (flag);
		AllStudent.push_back(studentNumber);
		cout << "请输入该学生的姓名 : ";
		string studentName;
		cin >> studentName;
		tempInfo.setName(studentName);
		tempInfo.setNumber(studentNumber);
		double tempScore;
		map<string, double> subjectAndScores;
		for (int i = 0; i < this->RequiredSubjects.size(); i++) {
			cout << "请输入该学生的 " << RequiredSubjects[i] << " 成绩" << endl;
			cin >> tempScore;
			subjectAndScores[RequiredSubjects[i]] = tempScore;
		}
		tempInfo.setScores(subjectAndScores);
		this->stuList.insertAsLast(tempInfo);
		cout << "第 " << i + 1 << " 个学生添加成功\n" << endl;
	}
	cout << "学生添加完毕" << endl;

}

void TeachingClass::delAStudentInTheClass(long number) {
	this->stuList.remove(this->isExist(number));
}

void TeachingClass::updateStudent(long number) {
	this->delAStudentInTheClass(number);
	long studentNumber;
	do {
		cout << "请输入学生的新学号 : ";
		cin >> studentNumber;
		if (find(AllStudent.begin(), AllStudent.end(), studentNumber) != AllStudent.end())
			cout << "学号已存在，请重新输入" << endl;
		else break;
	} while (1);
	cout << "请输入学生的新姓名 : ";
	studentInfo tempInfo;
	string studentName;
	cin >> studentName;
	tempInfo.setName(studentName);
	tempInfo.setNumber(studentNumber);
	double tempScore;
	map<string, double> subjectAndScores;
	for (int i = 0; i < this->RequiredSubjects.size(); i++) {
		cout << "请输入学生的 " << RequiredSubjects[i] << " 成绩" << endl;
		cin >> tempScore;
		subjectAndScores[RequiredSubjects[i]] = tempScore;
	}
	tempInfo.setScores(subjectAndScores);
	this->stuList.insertAsLast(tempInfo);
	AllStudent.erase(find(AllStudent.begin(), AllStudent.end(), number));
	AllStudent.push_back(studentNumber);
}

NodePosi(studentInfo) TeachingClass::isExist(long number) {
	studentInfo temp(number, "null");
	return stuList.find(temp);
}

void TeachingClass::showSingleInfo(long number) {
	NodePosi(studentInfo) temp = this->isExist(number);
	cout << "学生的班级为：" << this->clasName << endl
		<< "学生学号：" << number << endl
		<< "学生姓名：" << temp->data.getName() << endl;
	for (auto subjects : temp->data.getScores())
		cout << "学生的 " << subjects.first << " 成绩为 " << subjects.second << endl;
	for (auto subjects : temp->data.getOtherScores())
		cout << "学生的 " << subjects.first << " 成绩为 " << subjects.second << endl;
}

void TeachingClass::showClasInfo() {
	cout << this->clasName << " 成绩一览\n" << endl;
	cout << "排名\t学号\t姓名\t平均分\t";
	for (int i = 0; i < RequiredSubjects.size(); i++) cout << RequiredSubjects[i] << "\t";
	cout << endl;
	NodePosi(studentInfo) temp = this->stuList.first();
	for (int i = 1; temp != stuList.last()->suc; temp = temp->suc) {
		cout << i++ << "\t" << temp->data.getNumber() << "\t" << temp->data.getName() << "\t"
			<< temp->data.getAver() << "\t";
		for (int j = 0; j < RequiredSubjects.size(); j++) cout << temp->data.getScores()[RequiredSubjects[j]] << "\t";
		for (auto subs : temp->data.getOtherScores()) cout << subs.first << " " << subs.second << "\t";
		cout << endl;
	}
}

void TeachingClass::setSort() {
	cout << "请选择排序方式" << endl
		<< "1. 按照学号升序" << endl
		<< "2. 按照学号降序" << endl
		<< "3. 按照成绩升序" << endl
		<< "4. 按照成绩降序" << endl;
	int choose;
	cin >> choose;
	switch (choose) {
	case 1:
		this->sortByNumber();
		break;
	case 2:
		this->stuList.reverse();
		break;
	case 3:
		this->stuList.sort();
		this->stuList.reverse();
		break;
	case 4:
		this->stuList.sort();
		break;
	default: cout << "输入有误" << endl; 	break;
	}

}

void TeachingClass::TotalAndAver() {
	NodePosi(studentInfo) p = this->getFirstStus();
	for (; p->suc != NULL; p = p->suc) {
		p->data.TotalAndAver();
	}
}

void TeachingClass::sortByNumber() {
	for(NodePosi(studentInfo) head = stuList.first()->pre; head->suc != NULL; head = head->suc)
		for (NodePosi(studentInfo) p = head->suc; p->suc != NULL; p = p->suc) {
			if (head->data.getNumber() > p->data.getNumber()) {
				studentInfo temp = head->data;
				head->data = p->data;
				p->data = temp;
			}
		}
}

void TeachingClass::addSubForSingle(long number) {
	NodePosi(studentInfo) p = this->isExist(number);
		p->data.addSubject();
}

void TeachingClass::delSubForSingle(long number) {
	this->isExist(number)->data.delSubject();
}
