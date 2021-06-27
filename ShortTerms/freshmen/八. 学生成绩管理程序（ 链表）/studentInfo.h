#pragma once

#include<map>
#include<vector>
#include<iostream>

using namespace std;

extern vector<long> AllStudent;

class studentInfo {
public:

	//-------------Constructors and destructors--------------

	studentInfo();
	studentInfo(string name);
	studentInfo(long number, string name);
	studentInfo(string klass, long number, string name);
	studentInfo(string klass, long number, string name, map<string, double> Scores);
	studentInfo(string klass, long number, string name, map<string, double> Scores, map<string, double> other);
	studentInfo(string klass, string name);
	studentInfo(const studentInfo& s);

	~studentInfo();

	//------------------Setters and getters------------------
	void setNumber(long number);
	void setName(string name);
	void setClass(string klass);
	void setAver(double aver);
	void setTotal();
	void setScores(map<string, double> scores);
	void addScores(string name, double score);

	double getAver();
	double getTotal();
	long getNumber();
	string getName();
	string getClass();
	map<string, double> getScores();
	map<string, double> getOtherScores();

	//--------------------其他只读接口---------------------------

	void showSingleInfo();

	//--------------------其他可写接口--------------------------

	void delSubject(string name); //删除学科

	void delSubject(); //删除学科
	void addSubject(); //增加学科

	void setCertainScore(string sub, double score); //设置某一科目的成绩

	void TotalAndAver();

	//---------------------------------------------------------

	bool operator>=(studentInfo stu) {
		return this->m_Total >= stu.m_Total;
	}

	bool operator==(studentInfo stu) {
		return m_Number == stu.m_Number;
	}

private:
	string m_class;
	long m_Number;
	string m_Name;
	map<string, double> m_Scores;
	map<string, double> other_Scores;
	double m_Total;
	double m_Aver;
};
