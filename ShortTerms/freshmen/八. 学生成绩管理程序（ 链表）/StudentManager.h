#pragma once
#include"TeachingClass.h"

enum account {
	ROOT,
	MANAGER,
	STUDENT
};

class StudentManager {
public:

	StudentManager();
	~StudentManager() {}

public:

	void Login(); //登录系统

	void showRootMenu(); //显示root主界面

	void showStuMenu(); //显示学生界面

	void importFiles(); //导入学生信息

	void autoImport(string path); //自动读取文件

	void createFile(); //创建信息文件

	void addClass(); //增加班级

	void addSubjectForClass(); //为某班级开课

	void delSubjectForClass(); //为某班级退课

	void setScoresForClass(); //录入某门课的成绩

	void addStudent(); //增加学生

	void delStudent(); //删除学生

	void updateStudent(); //更新学生

	void findStudent(); //查找学生

	void addSubForSingle(long number = -1); //单个学生选课

	void delClasForSingle(long number = -1); //单个学生退课

	void showClasInfo(); //显示班级成绩单

	void showGradeInfo(); //显示年级成绩单

	void setOrder(); //指定学生排序方式

	void saveFile(); //手动存文件

	void autoSaveFile(); //自动存文件

	void delClass(); //删除班级

	void clear(); //删库跑路

	bool noClasses(); //没有教学班的提示

	bool noStudents(); //没有学生的提示

	void TotalAndAver(); //计算总成绩和平均分

	NodePosi(studentInfo) isExist(long number);

private:
	string filePath;
	map<string, TeachingClass> m_Classes; //classes' name and Class
	
private:
	NodePosi(studentInfo) nowAct;
	int account;
};

