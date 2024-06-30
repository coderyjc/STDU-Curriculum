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

	//--------------------����ֻ���ӿ�---------------------------

	void showSingleInfo();

	//--------------------������д�ӿ�--------------------------

	void delSubject(string name); //ɾ��ѧ��

	void delSubject(); //ɾ��ѧ��
	void addSubject(); //����ѧ��

	void setCertainScore(string sub, double score); //����ĳһ��Ŀ�ĳɼ�

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
