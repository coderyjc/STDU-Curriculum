#include "StudentManager.h"
#include<algorithm>
#include<fstream>
#include<sstream>

void StudentManager::importFiles() {
	system("cls");
	cout << ">���ڵ���ѧ���ļ�<" << endl
		<< "��ѡ�����ļ���������ʽ: " << endl
		<< "1. ѧ������" << endl
		<< "2. ѧ�� ѧ������" << endl
		<< "3. �����򵼳�����" << endl
		<< "\nע��:����ѧ��Ĭ����һ���༶\nѧ��Ĭ��Ϊ1/2/3...�Դ�����\n�������õ��ģ���Щ�������޸�\n" << endl
		<< "����������ѡ��: " << endl;
	int choose;
	cin >> choose;
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
	ifs.close();
	switch (choose) {
	case 1: this->readFile01(path); break;
	case 2: this->readFile02(path); break;
	case 3: this->readFile03(path); break;
	default:cout << "�������������½���" << endl; return;
	}
	system("pause");
	system("cls");
}

void StudentManager::readFile01(string fileName) {
	//Student List
	ifstream ifs(fileName, ios::in);
	string name;
	int i = 1;
	cout << "������ѧ�����ڰ༶: " << endl;
	string clas;
	cin >> clas;
	if (this->m_Classes.find(clas) != m_Classes.end()) {
		cout << "�༶�Ѵ��ڣ�������" << endl;
		return;
	}
	while (!ifs.eof()) {
		ifs >> name;
		string temp = to_string(i);
		this->m_Classes[clas].addStudentsForTheClass(name, temp);
		AllStudent.push_back(temp);
		i++;
	}
	this->m_Classes[clas].setClassName(clas);
	cout << "�ļ���ȡ�ɹ�" << endl;
	ifs.close();
}

void StudentManager::readFile02(string fileName) {
	//number and name
	ifstream ifs(fileName, ios::in);
	string name;
	string number;
	cout << "������ѧ�����ڰ༶: " << endl;
	string clas;
	cin >> clas;
	if (this->m_Classes.find(clas) != m_Classes.end()) {
		cout << "�༶�Ѵ��ڣ�������" << endl;
		return;
	}
	while (!ifs.eof()) {
		ifs >> number >> name;
		AllStudent.push_back(number);
		this->m_Classes[clas].addStudentsForTheClass(name, number);
	}
	this->m_Classes[clas].setClassName(clas);
	ifs.close();
	cout << "�ļ���ȡ�ɹ�" << endl;
}	

void StudentManager::readFile03(string fileName) {
	//default
	ifstream ifs(fileName, ios::in);
	string clasName;
	int subNum;
	do {
		ifs >> clasName >> subNum;
		TeachingClasses temp;
		string subs;
		for (int i = 0; i < subNum; i++) {
			ifs >> subs;
			temp.simplyAddSubjects(subs);
		}
		int totalStud;
		ifs >> totalStud;
		string stuTempNum, stuTempName;
		double tempScore;
		map<string, double> stuTempScores;
		for (int i = 0; i < totalStud; i++) {
			ifs >> stuTempNum >> stuTempName;
			AllStudent.push_back(stuTempNum);
			for (int i = 0; i < subNum; i++) {
				ifs >> tempScore;
				stuTempScores[temp.getsubjects()[i]] = tempScore;
			}
			StudentInfo s(stuTempName, stuTempNum, stuTempScores);
			temp.addStudentsForTheClass(make_pair(stuTempNum, s));
		}
		this->m_Classes.insert(make_pair(clasName, temp));
	} while (!ifs.eof());
	ifs.close();
	cout << "�ļ���ȡ�ɹ�" << endl;
}

void StudentManager::saveFiles() {
	system("cls");
	cout << ">���ڱ����ļ�<" << endl
		<< "����ǰ���ļ�����·��Ϊ��" << this->filePath << endl
		<< "�Ƿ�Ҫ�����ļ�����·����(��:1/��:0)" << endl;
	int choose;
	cin >> choose;
	if (choose == 1) {
		cout << "�������ļ�����·��:";
		cin >> this->filePath;
	} else cout << "����·��δ����" << endl;
	ofstream ofs(filePath, ios::trunc);
	for (auto klass : this->m_Classes) {
		vector<string> subs = klass.second.getsubjects();
		map<string, StudentInfo> stus = klass.second.getStudents();
		ofs << klass.first << '\t' << subs.size() << '\t';
		for (int i = 0; i < subs.size(); i++) ofs << subs[i] << '\t';
		ofs << klass.second.getStudents().size() << endl;
		for (auto student : stus) {
			ofs << student.first << '\t'
				<< student.second.getName() << '\t';
			map<string, double> scores = student.second.getScores();
			for (int i = 0; i < subs.size(); i++) {
				ofs << scores[subs[i]] << '\t';
			}
			ofs << endl;
		}
	}
	ofs.close();
	cout << "�ļ�����ɹ�" << endl;
	system("pause");
	system("cls");
}

void StudentManager::addNewTeachingClasses() {
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
	TeachingClasses temp;
	temp.setClassName(newClassName);
	this->m_Classes.insert(make_pair(newClassName, temp));
	cout << "��ѧ����ӳɹ�" << endl;
	system("pause");
	system("cls");
}

void StudentManager::addNewSubjectsForTeachingClasses() {
	system("cls");
	if (!this->noClasses()) return;
	cout << ">��������µĿγ�<" << endl;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "������Ҫ��ӿγ̵Ľ�ѧ������ƣ�";
	string nameToAddStudent;
	cin >> nameToAddStudent;
	if ( m_Classes.find(nameToAddStudent) == m_Classes.end()) {
		cout << "������������������" << endl; //û�ҵ�
		cin >> nameToAddStudent;
		if (m_Classes.find(nameToAddStudent) == m_Classes.end()) {
			cout << "���δ���������"<<endl;
			system("pause");
			system("cls");
			return;
		}
	}
	this->m_Classes[nameToAddStudent].addNewSubjects();
	system("pause");
	system("cls");
}

void StudentManager::addNewStudentForATeachingClass() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">����Ϊָ����ѧ������µ�ѧ��<" << endl;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "��������Ҫ���ѧ���Ľ�ѧ������ :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClasses>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "������������������" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "���δ���������" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else 
		(*it).second.addStudentsForTheClass();
	system("pause");
	system("cls");
}

void StudentManager::printSingleClassInfo() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "��������Ҫ��ʾ��Ϣ�Ľ�ѧ������ :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClasses>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end()) {
		cout << "������������������" << endl;
		cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "���δ���������" << endl;
			return;
		} else it = m_Classes.find(clasName);
	}
	system("cls");
	(*it).second.printStudentInfo();
	system("pause");
	system("cls");
}

void StudentManager::orderedPrintSingleClassInfo() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << "�����н�ѧ�ࣺ" << endl;
	for (auto classes : m_Classes) cout << classes.first << " ";
	cout << endl;
	cout << "��������Ҫ����Ľ�ѧ������ :";
	string clasName;
	cin >> clasName;
	map<string, TeachingClasses>::iterator it = m_Classes.find(clasName);
	if (it == m_Classes.end())  {
		cout << "������������������" << endl;
			cin >> clasName;
		if (m_Classes.find(clasName) == m_Classes.end()) {
			cout << "���δ���������" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	else (*it).second.orderedStudentScore();
	system("pause");
	system("cls");
}

void StudentManager::delSubjectForClass() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
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
	}
	else {
		this->m_Classes[ClasTobeDel].delASubject();
		system("pause");
		system("cls");
	}
}

void StudentManager::findStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">���ڲ���ָ��ѧ��<" << endl;
	cout << "��������Ҫ���ҵ�ѧ����ѧ�ţ�";
	string numToBeFound;
	cin >> numToBeFound;
	if (find(AllStudent.begin(), AllStudent.end(), numToBeFound) == AllStudent.end())
		cout << "�ܱ�Ǹ�����޴���" << endl;
	else 
		for (auto classes : this->m_Classes) {
			map<string, StudentInfo> mp = classes.second.getStudents();
			map<string, StudentInfo>::iterator it = mp.find(numToBeFound);
			if (it != mp.end()) classes.second.showSingleInfo(numToBeFound);
		}
	system("pause");
	system("cls");
}

void StudentManager::deleteStudent() {
	system("cls");
	if (!this->noClasses()) return;
	if (!this->noStudents()) return;
	cout << ">����ɾ��ĳѧ��<" << endl;
	cout << "��������Ҫɾ����ѧ����ѧ�ţ�";
	string numToBeDel;
	cin >> numToBeDel;
	string className;
	if (find(AllStudent.begin(), AllStudent.end(), numToBeDel) == AllStudent.end()){
		cout << "�ܱ�Ǹ�����޴���" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (auto classes : this->m_Classes) {
		map<string, StudentInfo> mp = classes.second.getStudents();
		map<string, StudentInfo>::iterator it = mp.find(numToBeDel);
		if (it != mp.end()) {
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
	cout << ">���ڸ���ĳѧ����Ϣ<" << endl;
	system("cls");
	cout << "��������Ҫ���µ�ѧ����ѧ�ţ�";
	string numToBeFound;
	string className;
	pair<string, StudentInfo> newStudent;
	cin >> numToBeFound;
	if (find(AllStudent.begin(), AllStudent.end(), numToBeFound) == AllStudent.end()) {
		cout << "�ܱ�Ǹ�����޴���" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (auto classes : this->m_Classes) {
		map<string, StudentInfo> mp = classes.second.getStudents();
		map<string, StudentInfo>::iterator it = mp.find(numToBeFound);
		if (it != mp.end()) {
			cout << "��ȷ�ϸ�������Ϣ\n" << endl;
			classes.second.showSingleInfo(numToBeFound);
			className = classes.first;
		}
	}
	this->m_Classes[className].updateAStudentInTheClass(numToBeFound);
	cout << "���³ɹ�" << endl;
	system("pause");
	system("cls");
	return;
}

class OverallSort {
public:
	bool operator()(pair<string, StudentInfo> p1, pair<string, StudentInfo> p2) {
	return p1.second.getTotalScore() > p2.second.getTotalScore();
	}
};

void StudentManager::GreadRanking() {
	system("cls");
	vector<pair<string, StudentInfo>> allStud;
	for (auto classes : m_Classes) {
		classes.second.calculateTotalScore();
		for (auto studs : classes.second.getStudents()) {
			studs.second.setClass(classes.first);
			allStud.push_back(studs);
		}
	}
	sort(allStud.begin(), allStud.end(), OverallSort());
	cout << "����\t�༶\tѧ��\t����\tƽ����" << endl;
	for (int i = 0; i < allStud.size(); i++) {
		cout << i + 1 << "\t" << allStud[i].second.getClas() << "\t"
			<< allStud[i].second.getNumber() << "\t"
			<< allStud[i].second.getName() << "\t"
			<< allStud[i].second.getAverScore() << endl;
	}
	system("pause");
	system("cls");
}

void StudentManager::printOverallScores() {
	system("cls");
	map<string, TeachingClasses>::iterator it;
	for (it = m_Classes.begin(); it != m_Classes.end(); it++) {
		cout << (*it).first << "��ɼ���\n" << endl;
		(*it).second.printStudentInfo();
		cout << endl;
	}
	system("pause");
	system("cls");
	return;
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

int StudentManager::showMenu() {
	cout << "\t\t��ӭʹ��ѧ����Ϣ����ϵͳv1.3" << endl
		<< "------------------------------------------------------" << endl
		<< "1 . ���ļ�����ѧ����Ϣ\t\t2 . ����µĽ�ѧ��\n" << endl
		<< "3 . Ϊָ����ѧ����ӿγ�\t4 . ¼��ĳ��ѧ��ĳ�ſεĳɼ�\n" << endl
		<< "5 . Ϊָ����ѧ��ȡ���γ�\t6 . Ϊָ����ѧ�����ѧ��\n" << endl
		<< "7 . ��ʾ��ĳ��ѧ��ȫ��ѧ����Ϣ\t8. ��ָ����ѧ���ѧ����������\n" << endl
		<< "9. ����ĳѧ����Ϣ\t\t10. ɾ��ĳѧ����Ϣ\n" << endl
		<< "11. �޸�ĳѧ����Ϣ\t\t12. ����ƽ���ֶ�ѧ�������꼶����\n" << endl
		<< "13. �鿴���а༶��ѧ���ĳɼ�\t14. ��������ѧ���ĳɼ�\n" << endl
		<< "15. ɾ����ѧ��\t\t\t16. �����������\n" << endl
		<< "0 . �˳�����\n" << endl
		<< "����������ѡ��" << endl;
	int choose; cin >> choose;
	return choose;
}

bool StudentManager::noClasses() {
	if (this->m_Classes.size() == 0) {
		cout << "Ŀǰû�н�ѧ�࣬�Ƿ�������ӽ�ѧ�� �����ǣ�1/��0��" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			this->addNewTeachingClasses();
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
			this->addNewStudentForATeachingClass();
			return 1;
		} else {
			cout << "ȡ�����ѧ��" << endl;
			system("pause");
			system("cls");
			return 0;
		}
	} else return 1;
}