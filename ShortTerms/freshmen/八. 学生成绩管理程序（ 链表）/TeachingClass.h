#pragma once

#include"studentInfo.h"
#include"myList.h"

class TeachingClass {
public:
	TeachingClass();
	~TeachingClass();
	TeachingClass(string name);

public:
	void setSubjects(vector<string> subs);


	vector<string> getRequiredSubs();
	NodePosi(studentInfo) getFirstStus();
	int getNumberOfStu();
	void insertStudent(studentInfo stu);

public:

	void addNewSubjects(); //添加课程

	void delSubject(); //删除课程

	void importScores(); //录入成绩

	void addStudents(); //增加学生

	void delAStudentInTheClass(long number); //删除学生

	void updateStudent(long number); //更新学生

	NodePosi(studentInfo) isExist(long number); //学生是否存在

	void addSubForSingle(long number); //为一个学生添加课程

	void delSubForSingle(long number); //为一个学生取消课程

	void showSingleInfo(long number); //展示一个学生的信息

	void showClasInfo(); //直接显示班级里的成绩单

	void setSort(); //指定排序方式

	void TotalAndAver(); //总分和平均分

	void sortByNumber(); //按照学号排序

private:

	string clasName;
	vector<string> RequiredSubjects;
	myList<studentInfo> stuList;
};