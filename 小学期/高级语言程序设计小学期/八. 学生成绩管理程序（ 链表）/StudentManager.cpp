#include "StudentManager.h"
#include<fstream>
#include<algorithm>

StudentManager::StudentManager() {
	filePath = "studentInfo.txt";
	account = 0;
}

void StudentManager::Login() {
	this->autoImport("studentInfo.txt");
	int flag = 0;
	long number;
	long password;
	do {
		system("cls");
		cout << "-----------------ѧ����Ϣ����ϵͳv1.5-------------------" << endl
			<< "\n\t\t��ָ����¼�˻�����" << endl
			<< "\n\t\t1. root\n"
			<< "\n\t\t2. ѧ��\n" << endl
			<< "\n\t\t0. �˳�\n" << endl
			<< "\n\t��ѡ�� ";
		do {
			cin >> this->account;
			if (0 > this->account || 3 < account) {
				cout << "�����������������룡" << endl;
				flag = 1;
			} else flag = 0;
		} while (flag);
		if (this->account == 0) return;
		switch (account) {
		case 1: this->showRootMenu(); break;
		case 2:
			this->autoImport(filePath);
			cout << "\n������ѧ�� :";
			cin >> number;
			if (find(AllStudent.begin(), AllStudent.end(), number) == AllStudent.end()) {
				cout << "ϵͳ�в����ڴ�ѧ��" << endl;
				system("pause");
				system("cls");
				break;
			} else {
				nowAct = this->isExist(number);
				cout << "���������루Ĭ��Ϊ123456����";
				cin >> password;
				if (password == 123456) {
					cout << "��½�ɹ�" << endl;
					system("cls");
					this->showStuMenu();					
				}
				else
					cout << "�������" << endl;
			}
			break;
		case 0:return;
		default: cout << "���������˳�" << endl; break;
		}
	} while (1);
}


void StudentManager::showRootMenu() {
	system("cls");
	int choose;
	do {
		cout << "-----------------ѧ����Ϣ����ϵͳv1.5--ROOTģʽ------------------\n" << endl;
		cout << "�ļ�������1. ����ѧ����Ϣ\t2.������Ϣ�ļ�\t\t3. ���ļ�\n" << endl
			<< "�༶������4. ���Ӱ༶\t\t5. Ϊĳ�༶����\t\t6. Ϊĳ�༶�˿�\n" << endl
			<< "\t  7. ¼��༶ѧ���ɼ�\t8. ��ʾ�༶�ɼ��� \t9. ɾ���༶\n " << endl
			<< "ѧ��������10. ����ѧ��\t\t11. ����ѧ����Ϣ\t12. ����ѧ����Ϣ\n" << endl
			<< "\t  13. ɾ��ѧ����Ϣ\t14. ����ѧ��ѡ��\t15. ����ѧ���˿�\n" << endl
			<< "ȫ�ֲ�����16. ��ʾ�꼶������\t17. �����������\n" << endl
			<< "����������18. ָ���ɼ�������ʽ\n\n0. ������һ��\n" << endl
			<< "��ѡ����еĲ�����";
		cin >> choose;
		switch (choose) {
		case 1:this->importFiles(); break;
		case 2:this->createFile(); break;
		case 3:this->saveFile(); break;
		case 4:this->addClass(); autoSaveFile(); break;
		case 5:this->addSubjectForClass();  autoSaveFile(); break;
		case 6:this->delSubjectForClass(); autoSaveFile(); break;
		case 7:this->setScoresForClass(); autoSaveFile(); break;
		case 8:this->showClasInfo(); break;
		case 9:this->delClass(); autoSaveFile(); break;
		case 10:this->addStudent(); autoSaveFile(); break;
		case 11:this->updateStudent(); autoSaveFile(); break;
		case 12:this->findStudent(); break;
		case 13:this->delStudent(); autoSaveFile(); break;
		case 14:this->addSubForSingle(); autoSaveFile(); break;
		case 15:this->delClasForSingle(); autoSaveFile(); break;
		case 16:this->showGradeInfo(); break;
		case 17:this->clear(); break;
		case 18:this->setOrder(); break;
		case 0: break;
		default: 
			cout << "����������������" << endl; 
			system("cls");
			break;
		}
	} while (choose);
}


void StudentManager::showStuMenu() {
	int choose;
	do {
		cout << "-----------------ѧ����Ϣ����ϵͳv1.5--ѧ��ģʽ------------------\n" << endl;
		cout << "1. ��ʾ�༶�ɼ���\n " << endl
			<< "2. �鿴ѧ����Ϣ\n" << endl
			<< "3. ѡ��\n" << endl
			<< "4. �˿�\n" << endl
			<< "0. ������һ��\n" << endl
			<< "��ѡ����еĲ�����";
		cin >> choose;
		switch (choose) {
		case 1:this->showClasInfo(); break;
		case 2:this->findStudent(); break;
		case 3:this->addSubForSingle(nowAct->data.getNumber()); break;
		case 4:this->delClasForSingle(nowAct->data.getNumber()); break;
		case 0:this->Login(); break;
		default: cout << "����������������"; break;
		}
	} while (choose);
}


void StudentManager::importFiles() {
	system("cls");
	cout << ">���ڵ���ѧ���ļ�<" << endl
		<< "��ѡ�����ļ���������ʽ: " << endl
		<< "1. ѧ������" << endl
		<< "2. ѧ�� ѧ������" << endl
		<< "3. �����򵼳�����" << endl
		<< "0. ������һ��" << endl
		<< "\nע��:����ѧ��Ĭ����һ���༶\nѧ��Ĭ��Ϊ1/2/3...�Դ�����\n�������õ��ģ���Щ�������޸�\n" << endl
		<< "����������ѡ��: " << endl;
	int choose;
	cin >> choose;
	if (choose == 0) {
		system("cls");
		return;
	}
	cout << "�������ļ����ڵ�����·��:";
	string path;
	cin >> path;
	ifstream ifs(path, ios::in);
	if (!ifs) {
		cout << "�ļ���ʧ�ܣ�ȷ�Ϻ���������: " << endl;
		cin >> path;
		ifs.open(path, ios::in);
		if (!ifs) {
			cout << "����������󣬳����˳�" << endl;
			system("cls");
			return;
		}
	}

	cout << "�Ƿ񽫸�·����Ϊ�ļ�Ĭ�ϱ����·��(��:1/��:0) ��" << endl;
	int isPath = 0;
	cin >> isPath;
	if (isPath == 1) this->filePath = path;
	else if (isPath == 0) cout << "δ����ΪĬ�ϱ���·��" << endl;
	else cout << "��������Ĭ�ϱ���·������Ϊ�ó���ͬĿ¼�µ�studentInfo.txt" << endl;

	string tempName;
	long tempNumber;
	string tempClassName;
	int flag = 1;


	TeachingClass tempClass(tempClassName);

	switch (choose) {
	case 1:
		do {
			cout << "��������Щѧ�����ڵİ༶��";
			cin >> tempClassName;
			if (m_Classes.find(tempClassName) == m_Classes.end()) flag = 0;
			else cout << "�༶�ظ�������������" << endl;
		} while (flag);
		for (int i = 1; !ifs.eof(); i++) {
			ifs >> tempName;
			AllStudent.push_back(i);
			studentInfo temp(tempClassName, i, tempName);
			tempClass.insertStudent(temp);
		}
		m_Classes.insert(make_pair(tempClassName, tempClass));
		break;
	case 2:
		do {
			cout << "��������Щѧ�����ڵİ༶��";
			cin >> tempClassName;
			if (m_Classes.find(tempClassName) == m_Classes.end()) flag = 0;
			else cout << "�༶�ظ�������������" << endl;
		} while (flag);
		for (int i = 1; !ifs.eof(); i++) {
			ifs >> tempNumber >> tempName;
			AllStudent.push_back(tempNumber);
			studentInfo temp(tempClassName, tempNumber, tempName);
			tempClass.insertStudent(temp);
		}
		m_Classes.insert(make_pair(tempClassName, tempClass));
		break;
	case 3: this->autoImport(path);	break;
	}
	ifs.close();
	cout << "�ļ�����ɹ���" << endl;
	system("pause");
 	system("cls");
}

void StudentManager::autoImport(string path) {
	ifstream ifs("studentInfo.txt", ios::in);
	if (!ifs) return;
	while (!ifs.eof()) {
		vector<string> tempReqSubs;
		string tempClasName;
		int numOfReqSubs;
		ifs >> tempClasName >> numOfReqSubs;
		TeachingClass tempClass(tempClasName);
		for (int i = 0; i < numOfReqSubs; i++) {
			string tempSubs;
			ifs >> tempSubs;
			tempReqSubs.push_back(tempSubs);
		}
		tempClass.setSubjects(tempReqSubs);
		int numOfStus;
		ifs >> numOfStus;
		for (int i = 0; i < numOfStus; i++) {
			long tempNumber;
			string subName;
			double subScore;
			map<string, double> tempScore;
			map<string, double> tempOther;
			string tempName;
			ifs >> tempNumber >> tempName;
			ifs >> numOfReqSubs;
			AllStudent.push_back(tempNumber);
			for (int j = 0; j < numOfReqSubs; j++) {
				ifs >> subName >> subScore;
				tempScore.insert(make_pair(subName, subScore));
			}
			int numOfOthers;
			ifs >> numOfOthers;
			for (int j = 0; j < numOfOthers; j++) {
				ifs >> subName >> subScore;
				tempOther.insert(make_pair(subName, subScore));
			}
			studentInfo tempStu(tempClasName, tempNumber, tempName, tempScore,  tempOther);
			tempClass.insertStudent(tempStu);
		}
		this->m_Classes.insert(make_pair(tempClasName, tempClass));
	}
	ifs.close();
}


void StudentManager::createFile() {
	system("cls");
	cout << "��ǰ���ļ�����λ��Ϊ��" << this->filePath << endl;
	cout << "�Ƿ�Ҫ�����ļ�λ�ã�����1/��0��";
	int choose; cin >> choose;
	if (choose == 1) {
		cout << "�������µ��ļ�����λ�ã�";
		cin >> this->filePath;
		cout << "�ļ�λ�����óɹ�" << endl;
	} else if (choose == 0) {
		cout << "δ����" << endl;
	} else cout << "��������" << endl;
	system("pause");
	system("cls");
}


void StudentManager::addClass() {
	system("cls");
	cout << ">��������µĽ�ѧ��<" << endl;
	string newClassName;
	cout << "�������µĽ�ѧ������� : ";
	cin >> newClassName;
	if (this->m_Classes.size() != 0 && this->m_Classes.find(newClassName) != this->m_Classes.end()) {
		cout << "��ѧ�������ظ�������������" << endl;
		cin >> newClassName;
		if (this->m_Classes.size() != 0 && this->m_Classes.find(newClassName) != this->m_Classes.end()) {
			cout << "�����ظ����Զ��˳�" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	TeachingClass temp(newClassName);
	this->m_Classes.insert(make_pair(newClassName, temp));
	cout << "��ѧ����ӳɹ�" << endl;
	system("pause");
	system("cls");
}


void StudentManager::addSubjectForClass() {
	system("cls");
	if (!this->noClasses()) return;
	cout << ">��������µĿγ�<" << endl;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "������Ҫ��ӿγ̵Ľ�ѧ������ƣ�";
	string nameToAddStudent;
	cin >> nameToAddStudent;
	if (m_Classes.find(nameToAddStudent) == m_Classes.end()) {
		cout << "������������������" << endl; //û�ҵ�
		cin >> nameToAddStudent;
		if (m_Classes.find(nameToAddStudent) == m_Classes.end()) {
			cout << "���δ���������" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	this->m_Classes[nameToAddStudent].addNewSubjects();
	system("pause");
	system("cls");
}


void StudentManager::delSubjectForClass() {
	system("cls");
	if (!this->noClasses()) return;
	cout << ">����ȡ���γ�<" << endl;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	string ClasTobeDel;
	cout << "������Ҫȡ���γ̵İ༶: ";
	cin >> ClasTobeDel;
	if (this->m_Classes.find(ClasTobeDel) == m_Classes.end()) {
		cout << "���޴˰�" << endl;
		system("pause");
		system("cls");
		return;
	} else {
		this->m_Classes[ClasTobeDel].delSubject();
		system("pause");
		system("cls");
	}
}


void StudentManager::setScoresForClass() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">����¼��ɼ�<" << endl;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	string ClasToImport;
	cout << "������Ҫ¼��ɼ��İ༶: ";
	cin >> ClasToImport;
	if (this->m_Classes.find(ClasToImport) == m_Classes.end()) {
		cout << "���޴˰�" << endl;
		system("pause");
		system("cls");
		return;
	} else {
		this->m_Classes[ClasToImport].importScores();
		system("pause");
		system("cls");
	}

}


void StudentManager::addStudent() {
	system("cls");
	if (!this->noClasses()) return;
	cout << ">����Ϊָ����ѧ������µ�ѧ��<" << endl;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "��������Ҫ���ѧ���Ľ�ѧ������ :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClass>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "������������������" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "���δ���������" << endl;
			system("pause");
			system("cls");
			return;
		}
	} else
		(*it).second.addStudents();
	system("pause");
	system("cls");

}


void StudentManager::delStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">����ɾ��ĳѧ��<" << endl;
	cout << "��������Ҫɾ����ѧ����ѧ�ţ�";
	long numToBeDel;
	cin >> numToBeDel;
	string className;

	if (find(AllStudent.begin(), AllStudent.end(), numToBeDel) == AllStudent.end()) {
		cout << "�ܱ�Ǹ�����޴���" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (auto classes : this->m_Classes) {
		NodePosi(studentInfo) it = classes.second.isExist(numToBeDel);
		if (it) {
			cout << "��ȷ�ϸ�������Ϣ\n" << endl;
			classes.second.showSingleInfo(numToBeDel);
			className = classes.first;
		}
	}
	cout << "ȷ��ɾ��������:1/��:0����";
	int del;
	cin >> del;
	if (!del) {
		cout << "ȡ��ɾ��" << endl;
		system("pause");
		system("cls");
		return;
	} else if (del == 1) {
		this->m_Classes[className].delAStudentInTheClass(numToBeDel);
		AllStudent.erase(find(AllStudent.begin(), AllStudent.end(), numToBeDel));
		cout << "ɾ���ɹ�" << endl;
	} else cout << "��������" << endl;
	system("pause");
	system("cls");
	return;
}


void StudentManager::updateStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	if (nowAct) {
		this->m_Classes[nowAct->data.getClass()].updateStudent(nowAct->data.getNumber());
		system("pause");
		system("cls");
		return;
	}
	cout << ">���ڸ���ĳѧ��<" << endl;
	cout << "��������Ҫ���µ�ѧ����ѧ�ţ�";
	long numToBeUp;
	cin >> numToBeUp;
	string className;

	if (find(AllStudent.begin(), AllStudent.end(), numToBeUp) == AllStudent.end()) {
		cout << "�ܱ�Ǹ�����޴���" << endl;
		system("pause");
		system("cls");
		return;
	}

	for (auto classes : this->m_Classes) {
		NodePosi(studentInfo) it = classes.second.isExist(numToBeUp);
		if (it) {
			cout << "��ȷ�ϸ�������Ϣ\n" << endl;
			classes.second.showSingleInfo(numToBeUp);
			className = classes.first;
		}
	}
	this->m_Classes[className].updateStudent(numToBeUp);
	cout << "���³ɹ�" << endl;
	system("pause");
	system("cls");
	return;
}

void StudentManager::findStudent() {
	system("cls");
	if(!this->noClasses()) return;
	if (!this->noStudents()) return;
	if (nowAct) {
		this->m_Classes[nowAct->data.getClass()].showSingleInfo(nowAct->data.getNumber());
		system("pause");
		system("cls");
		return;
	}
	cout << ">���ڲ�ѯĳѧ��<" << endl;
	cout << "��������Ҫ��ѯ��ѧ����ѧ�ţ�";
	long numToBeFound;
	cin >> numToBeFound;
	string className;

	if (find(AllStudent.begin(), AllStudent.end(), numToBeFound) == AllStudent.end()) {
		cout << "�ܱ�Ǹ�����޴���" << endl;
		system("pause");
		system("cls");
		return;
	} else 
		for (auto classes : this->m_Classes) {
			NodePosi(studentInfo) it = classes.second.isExist(numToBeFound);
			if (it) {
				cout << "��ȷ�ϸ�������Ϣ\n" << endl;
				classes.second.showSingleInfo(numToBeFound);
				className = classes.first;
			}
		}

	system("pause");
	system("cls");
	return;
}


void StudentManager::addSubForSingle(long number) {
	system("cls");
	if (number == -1) {
		cout << "������Ҫ��ӿγ̵�ѧ����ѧ�ţ�";
		cin >> number;
		if (find(AllStudent.begin(), AllStudent.end(), number) == AllStudent.end()) {
			cout << "���޴���" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		if ((*it).second.isExist(number)) {
			(*it).second.addSubForSingle(number);
			break;
		}
	}
	cout << "��ӳɹ�" << endl;
	system("pause");
	system("cls");
	return;
}


void StudentManager::delClasForSingle(long number) {
	system("cls");
	if (number == -1) {
		cout << "������Ҫȡ���γ̵�ѧ����ѧ�ţ�";
		cin >> number;
		if (find(AllStudent.begin(), AllStudent.end(), number) == AllStudent.end())
			cout << "���޴���" << endl;
	}
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		if ((*it).second.isExist(number)) {
			(*it).second.delSubForSingle(number);
			break;
		}
	}
	system("pause");
	system("cls");
	return;
}


void StudentManager::showClasInfo() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	this->TotalAndAver();
	if (nowAct) {
		this->m_Classes[nowAct->data.getClass()].showClasInfo();
		system("pause");
		system("cls");
		return;
	}
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "��������Ҫ��ʾ��Ϣ�Ľ�ѧ������ :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClass>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "������������������" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "���δ���������" << endl;
			system("pause");
			system("cls");
			return;
		} else it = m_Classes.find(clasName);
	}
	system("cls");
	(*it).second.showClasInfo();
	system("pause");
	system("cls");
	return;
}

class sortByScore {
public:
	bool operator()(studentInfo stu1, studentInfo stu2) {
		return stu1.getAver() > stu2.getAver();
	}
};

void StudentManager::showGradeInfo() {
	system("cls");
	m_Classes.erase("");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	this->TotalAndAver();
	vector<studentInfo> allStu;
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		NodePosi(studentInfo) p = (*it).second.getFirstStus();
		while (p->suc) {
			allStu.push_back(p->data);
			p = p->suc;
		}
	}
	sort(allStu.begin(), allStu.end(), sortByScore());
	cout << "����\t" << "�༶\t" << "ѧ��\t" << "����\t" << "ƽ����" << endl;
	for (int i = 0; i < allStu.size(); i++) {
		cout << i + 1 << "\t" 
			<< allStu[i].getClass() << "\t"
			<< allStu[i].getNumber() << "\t"
			<< allStu[i].getName() << "\t"
			<< allStu[i].getAver() << endl;
	}
	system("pause");
	system("cls");
	return;
}


void StudentManager::setOrder() {
	system("cls");
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "������Ҫ����İ༶��";
	string clasName;
	cin >> clasName;
	map<string, TeachingClass>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "������������������" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "���δ���������" << endl;
			system("pause");
			system("cls");
			return;
		} else it = m_Classes.find(clasName);
	}
	(*it).second.setSort();
	cout << "����ɹ�" << endl;
	system("pause");
	system("cls");
	return;
}


void StudentManager::saveFile() {
	cout << "���ڱ����ļ�" << endl;
	cout << "���ڵ��ļ�����·��Ϊ ��" << this->filePath << endl;
	cout << "�Ƿ�����ļ�����·��(��1/��0) ��";
	int choose; cin >> choose;
	if (choose == 1) {
		cout << "�������ļ�����··����";
		cin >> this->filePath;
		cout << "���óɹ�" << endl;
	} else cout << "δ�����ļ�����·��" << endl;
	this->autoSaveFile();
	cout << "�ļ�����ɹ�" << endl;
	system("pause");
	system("cls");
	return;
}

void StudentManager::autoSaveFile() {
	ofstream ofs(filePath, ios::out);
	for (auto clas : this->m_Classes) {
		ofs << clas.first << " " << clas.second.getRequiredSubs().size() << " ";
		for (int i = 0; i < clas.second.getRequiredSubs().size(); i++) 
			ofs << clas.second.getRequiredSubs()[i] << " ";
		ofs << clas.second.getNumberOfStu() << endl;
		for (NodePosi(studentInfo) temp = clas.second.getFirstStus(); temp->suc != NULL; temp = temp->suc) {
			ofs << temp->data.getNumber() << " " << temp->data.getName() << " ";

			map<string, double> tempScore = temp->data.getScores();
			ofs << tempScore.size() << " ";
			for(map<string, double>::iterator it = tempScore.begin(); it != tempScore.end(); it++)
				ofs << (*it).first << " " << (*it).second << " ";

			map<string, double> tempScore2 = temp->data.getOtherScores();
			ofs << tempScore2.size() << " ";
			for (map<string, double>::iterator it = tempScore2.begin(); it != tempScore2.end(); it++)
				ofs << (*it).first << " " << (*it).second << " ";
			ofs << endl;
		}
	}
	ofs.close();
}


void StudentManager::delClass() {
	system("cls");
	if (!this->noClasses()) return;
	cout << "����ɾ����ѧ��" << endl;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	string ClasTobeDel;
	cout << "������Ҫɾ���İ༶: ";
	cin >> ClasTobeDel;
	if (this->m_Classes.find(ClasTobeDel) == m_Classes.end()) {
		cout << "���޴˰�" << endl;
		system("pause");
		system("cls");
		return;
	} else {
		cout << "ɾ���༶�Ὣ���е�ѧ��һ��ɾ�����Ƿ����������1/��0�� ";
		int flag; cin >> flag;
		if (flag == 1) {
			this->m_Classes.erase(this->m_Classes.find(ClasTobeDel));
			cout << "ɾ���ɹ�" << endl;
		}
	}
	system("pause");
	system("cls");

}


void StudentManager::clear() {
	system("cls");
	cout << "�����������" << endl;
	cout << "����㲢����3/11�Ľ����ǰ6λС����";
	int flag1; cin >> flag1;
	if (flag1 == 272727) {
		cout << "ȷ��ɾ����(��1/��0)" << endl;
		cin >> flag1;
		if (flag1 == 1) {
			this->m_Classes.clear();
			cout << "ɾ���ɹ�" << endl;
		} else cout << "ȡ��ɾ��" << endl;
	} else cout << "ȡ��ɾ��" << endl;
	system("pause");
	system("cls");
}


bool StudentManager::noClasses() {
	if (this->m_Classes.size() == 0) {
		cout << "Ŀǰû�н�ѧ�࣬�Ƿ�������ӽ�ѧ�� �����ǣ�1/��0��" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			this->addClass();
			return 1;
		} else {
			cout << "ȡ����ӽ�ѧ��" << endl;
			system("pause");
			system("cls");
			return 0;
		}
	} else return 1;
}

bool StudentManager::noStudents() {
	if (AllStudent.size() == 0) {
		cout << "Ŀǰû��ѧ���� �Ƿ��������ѧ�����ѧ�������ǣ�1/��0��" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			this->addStudent();
			return 1;
		} else {
			cout << "ȡ�����ѧ��" << endl;
			system("pause");
			system("cls");
			return 0;
		}
	} else return 1;
}

void StudentManager::TotalAndAver() {
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		(*it).second.TotalAndAver();
	}
}

NodePosi(studentInfo) StudentManager::isExist(long number) {
	map<string, TeachingClass>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++)
		if ((*it).second.isExist(number))
			return (*it).second.isExist(number);	
}
