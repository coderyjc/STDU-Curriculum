#include "studentInfo.h"


vector<long> AllStudent;

studentInfo::studentInfo() {
	this->m_class = "null";
	this->m_Number = 0;
	this->m_Name = "null";
	this->m_Total = 0.0;
	this->m_Aver = 0.0;
}

studentInfo::studentInfo(string name) {
	this->m_class = "null";
	this->m_Number = 0;
	this->m_Name = name;
	this->m_Total = 0.0;
	this->m_Aver = 0.0;
}

studentInfo::studentInfo(long number, string name) {
	this->m_class = "null";
	this->m_Number = number;
	this->m_Name = name;
	this->m_Total = 0.0;
	this->m_Aver = 0.0;
}

studentInfo::studentInfo(const studentInfo& s) {
	this->m_class = s.m_class;
	this->m_Number = s.m_Number;
	this->m_Name = s.m_Name;
	this->m_Total = s.m_Total;
	this->m_Scores = s.m_Scores;
	this->other_Scores = s.other_Scores;
	this->m_Aver = s.m_Aver;
}

studentInfo::studentInfo(string klass, long number, string name) {
	this->m_class = klass;
	this->m_Number = number;
	this->m_Name = name;
	this->m_Total = 0.0;
	this->m_Aver = 0.0;
}

studentInfo::studentInfo(string klass, long number, string name, map<string, double> Scores) {
	this->m_class = klass;
	this->m_Number = number;
	this->m_Name = name;
	this->m_Scores = Scores;
	this->m_Total = 0.0;
	this->m_Aver = 0.0;
}

studentInfo::studentInfo(string klass, long number, string name, map<string, double> Scores, map<string, double> other) {
	this->m_class = klass;
	this->m_Number = number;
	this->m_Name = name;
	this->m_Scores = Scores;
	this->other_Scores = other;
	this->m_Total = 0.0;
	this->m_Aver = 0.0;
}

studentInfo::studentInfo(string klass, string name) {
	this->m_class = klass;
	this->m_Number = 0;
	this->m_Name = name;
	this->m_Total = 0.0;
	this->m_Aver = 0.0;
}

studentInfo::~studentInfo() {
}

void studentInfo::setNumber(long number) {
	this->m_Number = number;
}

void studentInfo::setName(string name) {
	this->m_Name = name;
}

void studentInfo::setClass(string klass) {
	this->m_class = klass;
}

void studentInfo::setAver(double aver) {
	this->m_Aver = aver;
}

string studentInfo::getClass() {
	return this->m_class;
}

long studentInfo::getNumber() {
	return this->m_Number;
}

string studentInfo::getName() {
	return this->m_Name;
}

double studentInfo::getAver() {
	return this->m_Aver;
}

double studentInfo::getTotal() {
	return this->m_Total;
}

map<string, double> studentInfo::getScores() {
	return this->m_Scores;
}

map<string, double> studentInfo::getOtherScores() {
	return this->other_Scores;
}

void studentInfo::showSingleInfo() {
	cout << "学生个人信息为: " << endl
		<< "姓名：" << this->m_Name << endl
		<< "学号：" << this->m_Number << endl
		<< "班级：" << this->m_class << endl;
	map<string, double>::iterator it;
	for (it = m_Scores.begin(); it != m_Scores.end(); it++) {
		cout << "学生的 " << (*it).first << " 成绩为 " << (*it).second << endl;
	}
}

void studentInfo::setTotal() {
	map<string, double>::iterator it;
	double sum = 0;
	for (it = this->m_Scores.begin(); it != m_Scores.end(); it++) {
		sum += (*it).second;
	}
	m_Aver = sum / this->m_Scores.size();
}

void studentInfo::setScores(map<string, double> scores) {
	this->m_Scores = scores;
}

void studentInfo::addScores(string name, double score) {
	this->other_Scores[name] = score;
}

void studentInfo::delSubject(string name) {
	this->m_Scores.erase(name);
}

void studentInfo::delSubject() {
	cout << "现有课程：" << endl;
	cout << "班级公有课 "; for (auto sub : this->m_Scores) cout << sub.first << " "; cout << endl;
	cout << "个人选修课 ";  for (auto sub : this->other_Scores) cout << sub.first << " ";
	cout << endl;
	int flag = 1;
	string name;
	do {
		cout << "请输入想删除的课程：";
		cin >> name;
		if (m_Scores.find(name) != m_Scores.end()) {
			cout << "不允许删除班级共有的必修课程" << endl;
			return;
		}
		if (other_Scores.find(name) != other_Scores.end()) {
			other_Scores.erase(name);
			cout << "删除成功" << endl;
			flag = 0;
		}
		else {
			cout << "没有找到这个课程" << endl;
			flag = 1;
		}
	} while (flag);
}

void studentInfo::addSubject() {
	int flag = 1;
	string name;
	do {
		cout << "请输入想增加的课程：";
		cin >> name;
		if (m_Scores.find(name) != m_Scores.end() || other_Scores.find(name) != other_Scores.end())
			cout << "课程已存在，请重新输入" << endl;
		else flag = 0;
	} while (flag);
	cout << "请输入这门课的成绩 ";
	double score;
	cin >> score;
	this->addScores(name, score);
}

void studentInfo::setCertainScore(string sub, double score) {
	if (m_Scores.find(sub) == m_Scores.end())
		this->m_Scores.insert(make_pair(sub, score));
	else this->m_Scores[sub] = score;
}

void studentInfo::TotalAndAver() {
	double sum = 0;
	for (auto sub : m_Scores)
		sum += sub.second;
	for (auto sub : other_Scores)
		sum += sub.second;
	this->m_Total = sum;
	if ((!m_Scores.size()) && (!other_Scores.size()))
		this->m_Aver = 0;
	else this->m_Aver = sum / (m_Scores.size() + other_Scores.size());
}
