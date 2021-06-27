#pragma once
#include<vector>
#include<map>
#include<iostream>
using namespace std;

extern vector<string> AllStudent;

class StudentInfo {
public:

	//---------------------Constructors----------------------

	StudentInfo();
	StudentInfo(string name);
	StudentInfo(string name, string number);
	StudentInfo(map<string, double> scores);
	StudentInfo(string name, map<string, double> scores);
	StudentInfo(string name, string number, map<string, double> scores);

	//--------------------Destructor-------------------------

	~StudentInfo() {}

	//--------------------SETTERS-------------------

	void setScores(map<string, double> v) { this->m_Scores = v; }
	void setNumber(string num) { this->m_Number = num; }
	void setName(string name) { this->m_Name = name; }
	void setRankInClass(int r) { this->rankInClass = r; }
	void setRankInGread(int r) { this->rankInGread = r; }
	void setTotalScore(double s) { this->m_Total = s; }
	void setAverScore(double s) { this->m_Average = s; }
	void setClass(string clas) { this->m_class = clas; }
	void setAll(map<string, double> v, string num, string name) {this->m_Scores = v; this->m_Number = num; this->m_Name = name;	}
	void setCertainScore(string sub, double score);

	//--------------------GETTERS---------------------------

	string getNumber() { return this->m_Number; }
	string getName() { return this->m_Name; }
	map<string, double> getScores() { return this->m_Scores; }
	int getRankInClass() { return this->rankInClass; }
	int getRankInGread() { return this->rankInGread; }
	double getTotalScore() { return this->m_Total; }
	double getAverScore() { return this->m_Average; }
	string getClas() { return this->m_class; }

	//--------------operators for student map--------------------------

	void delSubject(string name);

	//----------show info---------------------

	//void showSingleInfo();

private:
	string m_class;
	string m_Number;
	string m_Name; 
	int rankInClass;
	int rankInGread;
	double m_Total;
	double m_Average;
	map<string, double> m_Scores; //subjectName and its score
};