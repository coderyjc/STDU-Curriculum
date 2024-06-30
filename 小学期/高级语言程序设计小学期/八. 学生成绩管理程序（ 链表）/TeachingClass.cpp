#include "TeachingClass.h"

TeachingClass::TeachingClass() {
	clasName = "null";
}

TeachingClass::~TeachingClass() {
}

TeachingClass::TeachingClass(string name) {
	this->clasName = name;
}

void TeachingClass::setSubjects(vector<string> subs) {
	this->RequiredSubjects = subs;
}

vector<string> TeachingClass::getRequiredSubs() {
	return this->RequiredSubjects;
}

NodePosi(studentInfo) TeachingClass::getFirstStus() {
	return this->stuList.first();
}

int TeachingClass::getNumberOfStu() {
	return this->stuList.size();
}

void TeachingClass::insertStudent(studentInfo stu) {
	this->stuList.insertAsLast(stu);
}

void TeachingClass::addNewSubjects() {
	cout << "�����뽫Ҫ��ӿγ̵�����: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "������ӵ� " << i + 1 << " ���γ�" << endl;
		string subjectName;
		int flag = 1;
		do {
			cout << "������ÿγ̵����� : ";
			cin >> subjectName;
			if (find(RequiredSubjects.begin(), RequiredSubjects.end(), subjectName) != RequiredSubjects.end()) {
				cout << "�γ��Ѵ���, ����������" << endl;
				flag = 1;
			} else flag = 0;
		} while (flag);
		this->RequiredSubjects.push_back(subjectName);
		cout << "�� " << i + 1 << " ���γ���ӳɹ�\n" << endl;
	}
	cout << "�γ�������" << endl;

}

void TeachingClass::delSubject() {
	cout << "���ڵĿγ��У�";
	for (auto sub : this->RequiredSubjects) cout << sub << " ";
	cout << "\n�����뽫Ҫȡ���γ̵����ƣ�";
	string sub;
	cin >> sub;
	if (find(RequiredSubjects.begin(), RequiredSubjects.end(), sub) == RequiredSubjects.end()) {
		cout << "���޴˿γ�" << endl;
		return;
	} else {
		cout << "ɾ���γ̵�ͬʱҲ��ɾ������ѧ���ÿγ̵ĳɼ� ! �Ƿ������(��:1/��:0)" << endl;
		int choose;
		cin >> choose;
		if (choose != 1) {
			cout << "ȡ��ɾ���γ�" << endl;
			system("pause");
			system("cls");
			return;
		} else {
			for (NodePosi(studentInfo) temp = this->stuList.first() ; temp != stuList.last()->suc ; temp = temp->suc) {
				temp->data.delSubject(sub);
			}
			this->RequiredSubjects.erase(find(RequiredSubjects.begin(), RequiredSubjects.end(), sub));
			cout << "ɾ���ɹ�" << endl;
		}
	}
}

void TeachingClass::importScores() {
	cout << "���пγ� : ";
	for (auto sub : this->RequiredSubjects) cout << sub << " ";
	cout << "\n¼�����ſεĳɼ���" << endl;
	double tempScore;
	string toImport;
	cin >> toImport;
	int i = 1;
	if (find(RequiredSubjects.begin(), RequiredSubjects.end(), toImport) == RequiredSubjects.end()) cout << "���޴˿Σ������ԣ�" << endl;
	else {
		int i = 1;
		for (NodePosi(studentInfo) temp = stuList.first();  temp != stuList.last()->suc; temp = temp->suc) {
			cout << i++ << "/" << this->stuList.size() << " ������ " << temp->data.getNumber() << " " << temp->data.getName() << " ���ſεĳɼ� ��";
			cin >> tempScore;
			temp->data.setCertainScore(toImport, tempScore);
		}
		cout << "¼��ɹ�" << endl;
	}
}

void TeachingClass::addStudents() {
	cout << "�����뽫Ҫ���ѧ��������: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		studentInfo tempInfo;
		cout << "������ӵ� " << i + 1 << " ��ѧ��" << endl;
		int flag = 1;
		long studentNumber;
		do {
			cout << "�������ѧ����ѧ�� : ";
			cin >> studentNumber;
			flag = find(AllStudent.begin(), AllStudent.end(), studentNumber) == AllStudent.end() ? 0 : 1;
			if (flag)
				cout << "ѧ���ظ�, ����������" << endl;
		} while (flag);
		AllStudent.push_back(studentNumber);
		cout << "�������ѧ�������� : ";
		string studentName;
		cin >> studentName;
		tempInfo.setName(studentName);
		tempInfo.setNumber(studentNumber);
		double tempScore;
		map<string, double> subjectAndScores;
		for (int i = 0; i < this->RequiredSubjects.size(); i++) {
			cout << "�������ѧ���� " << RequiredSubjects[i] << " �ɼ�" << endl;
			cin >> tempScore;
			subjectAndScores[RequiredSubjects[i]] = tempScore;
		}
		tempInfo.setScores(subjectAndScores);
		this->stuList.insertAsLast(tempInfo);
		cout << "�� " << i + 1 << " ��ѧ����ӳɹ�\n" << endl;
	}
	cout << "ѧ��������" << endl;

}

void TeachingClass::delAStudentInTheClass(long number) {
	this->stuList.remove(this->isExist(number));
}

void TeachingClass::updateStudent(long number) {
	this->delAStudentInTheClass(number);
	long studentNumber;
	do {
		cout << "������ѧ������ѧ�� : ";
		cin >> studentNumber;
		if (find(AllStudent.begin(), AllStudent.end(), studentNumber) != AllStudent.end())
			cout << "ѧ���Ѵ��ڣ�����������" << endl;
		else break;
	} while (1);
	cout << "������ѧ���������� : ";
	studentInfo tempInfo;
	string studentName;
	cin >> studentName;
	tempInfo.setName(studentName);
	tempInfo.setNumber(studentNumber);
	double tempScore;
	map<string, double> subjectAndScores;
	for (int i = 0; i < this->RequiredSubjects.size(); i++) {
		cout << "������ѧ���� " << RequiredSubjects[i] << " �ɼ�" << endl;
		cin >> tempScore;
		subjectAndScores[RequiredSubjects[i]] = tempScore;
	}
	tempInfo.setScores(subjectAndScores);
	this->stuList.insertAsLast(tempInfo);
	AllStudent.erase(find(AllStudent.begin(), AllStudent.end(), number));
	AllStudent.push_back(studentNumber);
}

NodePosi(studentInfo) TeachingClass::isExist(long number) {
	studentInfo temp(number, "null");
	return stuList.find(temp);
}

void TeachingClass::showSingleInfo(long number) {
	NodePosi(studentInfo) temp = this->isExist(number);
	cout << "ѧ���İ༶Ϊ��" << this->clasName << endl
		<< "ѧ��ѧ�ţ�" << number << endl
		<< "ѧ��������" << temp->data.getName() << endl;
	for (auto subjects : temp->data.getScores())
		cout << "ѧ���� " << subjects.first << " �ɼ�Ϊ " << subjects.second << endl;
	for (auto subjects : temp->data.getOtherScores())
		cout << "ѧ���� " << subjects.first << " �ɼ�Ϊ " << subjects.second << endl;
}

void TeachingClass::showClasInfo() {
	cout << this->clasName << " �ɼ�һ��\n" << endl;
	cout << "����\tѧ��\t����\tƽ����\t";
	for (int i = 0; i < RequiredSubjects.size(); i++) cout << RequiredSubjects[i] << "\t";
	cout << endl;
	NodePosi(studentInfo) temp = this->stuList.first();
	for (int i = 1; temp != stuList.last()->suc; temp = temp->suc) {
		cout << i++ << "\t" << temp->data.getNumber() << "\t" << temp->data.getName() << "\t"
			<< temp->data.getAver() << "\t";
		for (int j = 0; j < RequiredSubjects.size(); j++) cout << temp->data.getScores()[RequiredSubjects[j]] << "\t";
		for (auto subs : temp->data.getOtherScores()) cout << subs.first << " " << subs.second << "\t";
		cout << endl;
	}
}

void TeachingClass::setSort() {
	cout << "��ѡ������ʽ" << endl
		<< "1. ����ѧ������" << endl
		<< "2. ����ѧ�Ž���" << endl
		<< "3. ���ճɼ�����" << endl
		<< "4. ���ճɼ�����" << endl;
	int choose;
	cin >> choose;
	switch (choose) {
	case 1:
		this->sortByNumber();
		break;
	case 2:
		this->stuList.reverse();
		break;
	case 3:
		this->stuList.sort();
		this->stuList.reverse();
		break;
	case 4:
		this->stuList.sort();
		break;
	default: cout << "��������" << endl; 	break;
	}

}

void TeachingClass::TotalAndAver() {
	NodePosi(studentInfo) p = this->getFirstStus();
	for (; p->suc != NULL; p = p->suc) {
		p->data.TotalAndAver();
	}
}

void TeachingClass::sortByNumber() {
	for(NodePosi(studentInfo) head = stuList.first()->pre; head->suc != NULL; head = head->suc)
		for (NodePosi(studentInfo) p = head->suc; p->suc != NULL; p = p->suc) {
			if (head->data.getNumber() > p->data.getNumber()) {
				studentInfo temp = head->data;
				head->data = p->data;
				p->data = temp;
			}
		}
}

void TeachingClass::addSubForSingle(long number) {
	NodePosi(studentInfo) p = this->isExist(number);
		p->data.addSubject();
}

void TeachingClass::delSubForSingle(long number) {
	this->isExist(number)->data.delSubject();
}
