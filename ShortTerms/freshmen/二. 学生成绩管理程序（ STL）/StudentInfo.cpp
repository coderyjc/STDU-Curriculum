#include "StudentInfo.h"

vector<string> AllStudent;

StudentInfo::StudentInfo() {
	this->m_Name = "null";
	this->m_Number = "null";
	this->m_Total = 0;
	this->m_Average = 0;
	this->rankInClass = 0;
	this->rankInGread = 0;
}

StudentInfo::StudentInfo(string name) {
	this->m_Name = name;
	this->m_Number = "null";
	this->m_Total = 0;
	this->m_Average = 0;
	this->rankInClass = 0;
	this->rankInGread = 0;
}

StudentInfo::StudentInfo(string name, string number) {
	this->m_Name = name;
	this->m_Number = number;
	this->m_Total = 0;
	this->m_Average = 0;
	this->rankInClass = 0;
	this->rankInGread = 0;
}

StudentInfo::StudentInfo(map<string, double> scores) {
	this->m_Name = "null";
	this->m_Number = "null";
	this->m_Total = 0;
	this->m_Average = 0;
	this->rankInClass = 0;
	this->rankInGread = 0;
	this->m_Scores = scores;
}

StudentInfo::StudentInfo(string name, map<string, double> scores) {
	this->m_Name = name;
	this->m_Number = "null";
	this->m_Total = 0;
	this->m_Average = 0;
	this->rankInClass = 0;
	this->rankInGread = 0;
	this->m_Scores = scores;
}

StudentInfo::StudentInfo(string name, string number, map<string, double> scores) {
	this->m_Name = name;
	this->m_Number = number;
	this->m_Total = 0;
	this->m_Average = 0;
	this->rankInClass = 0;
	this->rankInGread = 0;
	this->m_Scores = scores;
}

void StudentInfo::setCertainScore(string sub, double score) {
	if (m_Scores.find(sub) == m_Scores.end())
		this->m_Scores.insert(make_pair(sub, score));
	else this->m_Scores[sub] = score;
}

void StudentInfo::delSubject(string name) {
	this->m_Scores.erase(name);
}