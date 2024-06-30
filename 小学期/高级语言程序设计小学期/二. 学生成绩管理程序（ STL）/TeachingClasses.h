#pragma once
#include<map>
#include<vector>
#include<iostream>
#include"StudentInfo.h"
using namespace std;

enum sortOrder{
	ASCENDING_NUMBER = 1,
	DECENDING_NUMBER,
	ASCENDING_SCORE,
	DECENGING_SCORE
};

class TeachingClasses {
public:
	//---------Constructors and Destructors-----------

	TeachingClasses() { this->sortOrder = 0; };

	~TeachingClasses() {}

	//---------------GETTERS---------------------

	int getSortOrder() { return this->sortOrder; }
	string getClassName() { return this->className; }
	vector<string> getsubjects() { return this->subjects; }
	map<string, StudentInfo> getStudents() { return this->stuMap; }

	//--------------SETTERS-----------------------

	void setClassName(string name) { this->className = name; }
	void setSortOrder(int order) { this->sortOrder = order; }

	//--------------------------------------------
	
	void showSingleInfo(string number); //���ѧ��Ϊnumber��ѧ������Ϣ

	void orderedStudentScore(); //ָ���������
	void printStudentInfo(); //��ӡȫ����Ϣ

	void calculateTotalScore(); //����ȫ��ѧ�����ֺܷ�ƽ����

	void delAStudentInTheClass(string newStudent); //ɾ������ѧ��ΪsewStudent��ѧ��
	void updateAStudentInTheClass(string number); //����ѧ��Ϊnumber��ѧ������Ϣ

	void addNewSubjects(); //������ѧ��
	void delASubject(); //ɾ��ѧ��
	void importScores(); //¼��ѧ��ĳ�ſεĳɼ�
	void simplyAddSubjects(string sub) { this->subjects.push_back(sub); }

	void addStudentsForTheClass(); //Ϊ�˰༶����һ��ѧ��
	void addStudentsForTheClass(string name, string number);//Ϊ�˰༶����һ��ѧ��
	void addStudentsForTheClass(pair<string, StudentInfo> p);//Ϊ�˰༶����һ��ѧ��

	class sortByNumber {
	public:
		bool operator()(pair<string, StudentInfo> p1, pair<string, StudentInfo> p2) {
			return p1.second.getNumber() < p2.second.getNumber();
		}
	};

	class sortByScore {
	public:
		bool operator()(pair<string, StudentInfo> p1, pair<string, StudentInfo> p2) {
			return p1.second.getTotalScore() < p2.second.getTotalScore();
		}
	};

private:
	string className;
	vector<string> subjects; // subjects' name
	map<string, StudentInfo> stuMap; // students'number and Student information
	int sortOrder;
};