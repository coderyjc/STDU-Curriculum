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

	void addNewSubjects(); //��ӿγ�

	void delSubject(); //ɾ���γ�

	void importScores(); //¼��ɼ�

	void addStudents(); //����ѧ��

	void delAStudentInTheClass(long number); //ɾ��ѧ��

	void updateStudent(long number); //����ѧ��

	NodePosi(studentInfo) isExist(long number); //ѧ���Ƿ����

	void addSubForSingle(long number); //Ϊһ��ѧ����ӿγ�

	void delSubForSingle(long number); //Ϊһ��ѧ��ȡ���γ�

	void showSingleInfo(long number); //չʾһ��ѧ������Ϣ

	void showClasInfo(); //ֱ����ʾ�༶��ĳɼ���

	void setSort(); //ָ������ʽ

	void TotalAndAver(); //�ֺܷ�ƽ����

	void sortByNumber(); //����ѧ������

private:

	string clasName;
	vector<string> RequiredSubjects;
	myList<studentInfo> stuList;
};