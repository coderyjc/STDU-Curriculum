#pragma once
#include"TeachingClasses.h"

class StudentManager {
public:

	//-----------------Constructor and destructor-----------------

	StudentManager() {
		this->filePath = "studentInfo.txt";
	}

	~StudentManager() {}
	
	//-------------------------��Ҫ����------------------------------------

	void importFiles(); // ����  �����ļ�����ѧ����Ϣ
	void readFile01(string fileName);
	void readFile02(string fileName);
	void readFile03(string fileName);

	void saveFiles(); // ���� ���浵

	void addNewTeachingClasses(); // ����  �������µĽ�ѧ��

	void addNewSubjectsForTeachingClasses(); // ����  ��Ϊ��ѧ�������µĿγ�

	void delSubjectForClass(); // ����  ��Ϊĳ����ѧ��ȡ��ĳ�γ�

	void addNewStudentForATeachingClass(); // ����  ��Ϊָ�������ѧ��

	void printSingleClassInfo(); // ����  �� ��ʾ��ĳ��ѧ��ȫ����ѧ���ɼ�

	void orderedPrintSingleClassInfo(); // ���� ��ָ��ĳ��ѧ���ѧ������ʽ

	void findStudent(); // ���� ������ѧ����Ϣ

	void deleteStudent();// ����  ��ɾ��ѧ����Ϣ

	void updateStudent();// ����  ������ѧ����Ϣ

	void GreadRanking(); //����  ���꼶����

	void printOverallScores(); //���� ���꼶�ɼ���

	void setScoresForClass(); //���ܣ�¼��ĳ�ſεĳɼ�

	void delClass(); //���ܣ�ɾ����ѧ��

	void clear(); //���ܣ�ɾ����·

	//--------------------------------------------------

	int showMenu();

	bool noClasses(); //û�н�ѧ�����ʾ
	bool noStudents(); //û��ѧ������ʾ

private:
	map<string, TeachingClasses> m_Classes; //classes' name and Class
	string filePath;
};