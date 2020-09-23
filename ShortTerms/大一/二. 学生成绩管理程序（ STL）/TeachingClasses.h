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
	
	void showSingleInfo(string number); //输出学号为number的学生的信息

	void orderedStudentScore(); //指定排序规则
	void printStudentInfo(); //打印全班信息

	void calculateTotalScore(); //计算全班学生的总分和平均分

	void delAStudentInTheClass(string newStudent); //删除本班学号为sewStudent的学生
	void updateAStudentInTheClass(string number); //更新学号为number的学生的信息

	void addNewSubjects(); //增添新学科
	void delASubject(); //删除学科
	void importScores(); //录入学生某门课的成绩
	void simplyAddSubjects(string sub) { this->subjects.push_back(sub); }

	void addStudentsForTheClass(); //为此班级增加一个学生
	void addStudentsForTheClass(string name, string number);//为此班级增加一个学生
	void addStudentsForTheClass(pair<string, StudentInfo> p);//为此班级增加一个学生

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