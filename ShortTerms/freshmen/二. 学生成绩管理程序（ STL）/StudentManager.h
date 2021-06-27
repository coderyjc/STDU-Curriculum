#pragma once
#include"TeachingClasses.h"

class StudentManager {
public:

	//-----------------Constructor and destructor-----------------

	StudentManager() {
		this->filePath = "studentInfo.txt";
	}

	~StudentManager() {}
	
	//-------------------------主要功能------------------------------------

	void importFiles(); // 功能  ：从文件导入学生信息
	void readFile01(string fileName);
	void readFile02(string fileName);
	void readFile03(string fileName);

	void saveFiles(); // 功能 ：存档

	void addNewTeachingClasses(); // 功能  ：增加新的教学班

	void addNewSubjectsForTeachingClasses(); // 功能  ：为教学班增加新的课程

	void delSubjectForClass(); // 功能  ：为某个教学班取消某课程

	void addNewStudentForATeachingClass(); // 功能  ：为指定班添加学生

	void printSingleClassInfo(); // 功能  ： 显示出某教学班全部的学生成绩

	void orderedPrintSingleClassInfo(); // 功能 ：指定某教学班的学生排序方式

	void findStudent(); // 功能 ：查找学生信息

	void deleteStudent();// 功能  ：删除学生信息

	void updateStudent();// 功能  ：更新学生信息

	void GreadRanking(); //功能  ：年级排名

	void printOverallScores(); //功能 ：年级成绩单

	void setScoresForClass(); //功能：录入某门课的成绩

	void delClass(); //功能：删除教学班

	void clear(); //功能：删库跑路

	//--------------------------------------------------

	int showMenu();

	bool noClasses(); //没有教学班的提示
	bool noStudents(); //没有学生的提示

private:
	map<string, TeachingClasses> m_Classes; //classes' name and Class
	string filePath;
};