#include"TeachingClasses.h"
#include<numeric>
#include<algorithm>
#include<functional>

void TeachingClasses::addNewSubjects() {
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
			if (find(subjects.begin(), subjects.end(), subjectName) != subjects.end()) {
				cout << "课程已存在, 请重新输入" << endl;
				flag = 1;
			} else flag = 0;
		} while (flag);
		this->subjects.push_back(subjectName);
		cout << "第 " << i + 1 << " 个课程添加成功\n" << endl;
	}
	cout << "课程添加完毕" << endl;
}

void TeachingClasses::calculateTotalScore() {
	if (this->subjects.size() == 0) return;
	map<string, StudentInfo>::iterator it;
	double sum = 0;
	for (it = stuMap.begin(); it != stuMap.end(); it++) {
		if ((*it).second.getScores().size() == 0) return;
		for (int i = 0; i < this->subjects.size(); i++) sum += (*it).second.getScores()[subjects[i]];
		(*it).second.setTotalScore(sum);
		(*it).second.setAverScore(sum / this->subjects.size());
		sum = 0;
	}
}

void TeachingClasses::addStudentsForTheClass() {
	cout << "请输入将要添加学生的数量: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		StudentInfo tempInfo;
		cout << "正在添加第 " << i + 1 << " 个学生" << endl;
		int flag = 1;
		string studentNumber;
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
		for (int i = 0; i < this->subjects.size(); i++) {
			cout << "请输入该学生的 " << subjects[i] << " 成绩" << endl;
			cin >> tempScore;
			subjectAndScores[subjects[i]] = tempScore;
		}
		tempInfo.setScores(subjectAndScores);
		this->stuMap.insert(make_pair(studentNumber, tempInfo));
		cout << "第 " << i + 1 << " 个学生添加成功\n" << endl;
	}
	cout << "学生添加完毕" << endl;
}

void TeachingClasses::showSingleInfo(string number) {
	cout << "学生的班级为：" << this->className << endl
		<< "学生学号：" << number << endl
		<< "学生姓名：" << this->stuMap[number].getName() << endl;
	for (auto subjects : this->stuMap[number].getScores())
		cout << "学生的" << subjects.first << "成绩为" << subjects.second << endl;
}

void TeachingClasses::orderedStudentScore() {
	this->calculateTotalScore();
	cout << "请指定排序规则: " << endl
		<< "1.按照学号排序" << endl
		<< "2.按照总成绩排序" << endl
		<< "请输入您的选择 :";
	int choose = 0;
	cin >> choose;
	cout << "请指定升降序: " << endl
		<< "1. 升序" << endl
		<< "2. 降序" << endl
		<< "请输入您的选择 :";
	int choose2 = 0;
	cin >> choose2;
	if (choose == 1) {
		if (choose2 == 1) this->sortOrder = ASCENDING_NUMBER;
		else this->sortOrder = DECENDING_NUMBER;
	}
	 else {
		if (choose2 == 1) this->sortOrder = ASCENDING_SCORE;
		else this->sortOrder = DECENGING_SCORE;
	}
	cout << "是否立即查看成绩单(是:1/否:0) ？" << endl;
	cin >> choose;
	if (choose) this->printStudentInfo();
	else return;
}

void TeachingClasses::printStudentInfo() {
	cout << this->className << "学生一览" << endl;
	this->calculateTotalScore();
	vector<pair<string, StudentInfo>> toSort(this->stuMap.begin(), this->stuMap.end());
	switch (this->sortOrder) {
	case ASCENDING_NUMBER:
			sort(toSort.begin(), toSort.end(), sortByNumber());
			break;
	case DECENDING_NUMBER:
			sort(toSort.begin(), toSort.end(), sortByNumber());
			reverse(toSort.begin(), toSort.end());
			break;
	case ASCENDING_SCORE:
			sort(toSort.begin(), toSort.end(), sortByScore());
			break;
	case DECENGING_SCORE:
			sort(toSort.begin(), toSort.end(), sortByScore());
			reverse(toSort.begin(), toSort.end());
			break;
	default: break;
	}
	vector<pair<string, StudentInfo>>::iterator it;
	int i = 1;
		cout << "排名\t" << "学号\t" << "姓名\t";
		for (int j = 0; j < this->subjects.size(); j++) cout << this->subjects[j] << "\t";
		cout << "平均分" << endl;
	for (it = toSort.begin(); it != toSort.end();it++) {
		cout << i++ << "\t" << (*it).second.getNumber() << "\t" << (*it).second.getName() << "\t";
		for (int j = 0; j < this->subjects.size(); j++)
			cout << (*it).second.getScores()[subjects[j]] << "\t";
		cout << (*it).second.getAverScore() << endl;
	}
}

void TeachingClasses::delASubject() {
	cout << "现在的课程有：";
	for (auto sub : this->subjects) cout << sub << " ";
	cout << "\n请输入将要取消课程的名称：";
	string sub;
	cin >> sub;
	if (find(subjects.begin(), subjects.end(), sub) == subjects.end()) {
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
		}
		else {
			map<string, StudentInfo>::iterator it;			
			for (it = stuMap.begin(); it != stuMap.end(); it++) {
				(*it).second.delSubject(sub);
			}
			this->subjects.erase(find(subjects.begin(), subjects.end(), sub));
			cout << "删除成功" << endl;
		}
	}
}

void TeachingClasses::importScores() {
	cout << "现有课程 : ";
	for (auto sub : this->subjects) cout << sub << " ";
	cout << "录入哪门课的成绩？" << endl;
	double temp;
	string toImport;
	cin >> toImport;
	int i = 1;
	if (find(subjects.begin(), subjects.end(), toImport) == subjects.end())cout << "查无此课，请重试！" << endl;
	else {
		map<string, StudentInfo>::iterator it = this->stuMap.begin();
		for (; it != stuMap.end(); it++) {
			cout << i++ << "/" << this->stuMap.size() << " 请输入 " << (*it).first << " " << (*it).second.getName() << " 本门课的成绩 ：";
			cin >> temp;
			(*it).second.setCertainScore(toImport, temp);
		}
		cout << "录入成功" << endl;
	}
}

void TeachingClasses::updateAStudentInTheClass(string number) {
	this->delAStudentInTheClass(number);
	string studentNumber;
	do {
		cout << "请输入该学生的新学号 : ";
		cin >> studentNumber;
		if (find(AllStudent.begin(), AllStudent.end(), studentNumber) != AllStudent.end())
			cout << "学号已存在，请重新输入" << endl;
		else break;
	} while (1);
	cout << "请输入该学生的新姓名 : ";
	StudentInfo tempInfo;
	string studentName;
	cin >> studentName;
	tempInfo.setName(studentName);
	tempInfo.setNumber(studentNumber);
	double tempScore;
	map<string, double> subjectAndScores;
	for (int i = 0; i < this->subjects.size(); i++) {
		cout << "请输入该学生的 " << subjects[i] << " 成绩" << endl;
		cin >> tempScore;
		subjectAndScores[subjects[i]] = tempScore;
	}
	tempInfo.setScores(subjectAndScores);
	this->stuMap.insert(make_pair(studentNumber, tempInfo));
	AllStudent.erase(find(AllStudent.begin(), AllStudent.end(), number));
	AllStudent.push_back(studentNumber);
}

void TeachingClasses::addStudentsForTheClass(string name, string number) {
	StudentInfo s(name, number);
	this->stuMap.insert(make_pair(number, s));
	return;
}

void TeachingClasses::addStudentsForTheClass(pair<string, StudentInfo> p) {
	this->stuMap.insert(p);
}

void TeachingClasses::delAStudentInTheClass(string tobeDel) {
	this->stuMap.erase(stuMap.find(tobeDel));
}