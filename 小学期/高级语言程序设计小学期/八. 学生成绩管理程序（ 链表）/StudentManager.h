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

	void Login(); //��¼ϵͳ

	void showRootMenu(); //��ʾroot������

	void showStuMenu(); //��ʾѧ������

	void importFiles(); //����ѧ����Ϣ

	void autoImport(string path); //�Զ���ȡ�ļ�

	void createFile(); //������Ϣ�ļ�

	void addClass(); //���Ӱ༶

	void addSubjectForClass(); //Ϊĳ�༶����

	void delSubjectForClass(); //Ϊĳ�༶�˿�

	void setScoresForClass(); //¼��ĳ�ſεĳɼ�

	void addStudent(); //����ѧ��

	void delStudent(); //ɾ��ѧ��

	void updateStudent(); //����ѧ��

	void findStudent(); //����ѧ��

	void addSubForSingle(long number = -1); //����ѧ��ѡ��

	void delClasForSingle(long number = -1); //����ѧ���˿�

	void showClasInfo(); //��ʾ�༶�ɼ���

	void showGradeInfo(); //��ʾ�꼶�ɼ���

	void setOrder(); //ָ��ѧ������ʽ

	void saveFile(); //�ֶ����ļ�

	void autoSaveFile(); //�Զ����ļ�

	void delClass(); //ɾ���༶

	void clear(); //ɾ����·

	bool noClasses(); //û�н�ѧ�����ʾ

	bool noStudents(); //û��ѧ������ʾ

	void TotalAndAver(); //�����ܳɼ���ƽ����

	NodePosi(studentInfo) isExist(long number);

private:
	string filePath;
	map<string, TeachingClass> m_Classes; //classes' name and Class
	
private:
	NodePosi(studentInfo) nowAct;
	int account;
};

