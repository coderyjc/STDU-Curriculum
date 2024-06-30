#include"TeachingClasses.h"
#include<numeric>
#include<algorithm>
#include<functional>

void TeachingClasses::addNewSubjects() {
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
			if (find(subjects.begin(), subjects.end(), subjectName) != subjects.end()) {
				cout << "�γ��Ѵ���, ����������" << endl;
				flag = 1;
			} else flag = 0;
		} while (flag);
		this->subjects.push_back(subjectName);
		cout << "�� " << i + 1 << " ���γ���ӳɹ�\n" << endl;
	}
	cout << "�γ�������" << endl;
}

void TeachingClasses::calculateTotalScore() {
	if (this->subjects.size() == 0) return;
	map<string, StudentInfo>::iterator it;
	double sum = 0;
	for (it = stuMap.begin(); it != stuMap.end(); it++) {
		if ((*it).second.getScores().size() == 0) return;
		for (int i = 0; i < this->subjects.size(); i++) sum += (*it).second.getScores()[subjects[i]];
		(*it).second.setTotalScore(sum);
		(*it).second.setAverScore(sum / this->subjects.size());
		sum = 0;
	}
}

void TeachingClasses::addStudentsForTheClass() {
	cout << "�����뽫Ҫ���ѧ��������: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		StudentInfo tempInfo;
		cout << "������ӵ� " << i + 1 << " ��ѧ��" << endl;
		int flag = 1;
		string studentNumber;
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
		for (int i = 0; i < this->subjects.size(); i++) {
			cout << "�������ѧ���� " << subjects[i] << " �ɼ�" << endl;
			cin >> tempScore;
			subjectAndScores[subjects[i]] = tempScore;
		}
		tempInfo.setScores(subjectAndScores);
		this->stuMap.insert(make_pair(studentNumber, tempInfo));
		cout << "�� " << i + 1 << " ��ѧ����ӳɹ�\n" << endl;
	}
	cout << "ѧ��������" << endl;
}

void TeachingClasses::showSingleInfo(string number) {
	cout << "ѧ���İ༶Ϊ��" << this->className << endl
		<< "ѧ��ѧ�ţ�" << number << endl
		<< "ѧ��������" << this->stuMap[number].getName() << endl;
	for (auto subjects : this->stuMap[number].getScores())
		cout << "ѧ����" << subjects.first << "�ɼ�Ϊ" << subjects.second << endl;
}

void TeachingClasses::orderedStudentScore() {
	this->calculateTotalScore();
	cout << "��ָ���������: " << endl
		<< "1.����ѧ������" << endl
		<< "2.�����ܳɼ�����" << endl
		<< "����������ѡ�� :";
	int choose = 0;
	cin >> choose;
	cout << "��ָ��������: " << endl
		<< "1. ����" << endl
		<< "2. ����" << endl
		<< "����������ѡ�� :";
	int choose2 = 0;
	cin >> choose2;
	if (choose == 1) {
		if (choose2 == 1) this->sortOrder = ASCENDING_NUMBER;
		else this->sortOrder = DECENDING_NUMBER;
	}
	 else {
		if (choose2 == 1) this->sortOrder = ASCENDING_SCORE;
		else this->sortOrder = DECENGING_SCORE;
	}
	cout << "�Ƿ������鿴�ɼ���(��:1/��:0) ��" << endl;
	cin >> choose;
	if (choose) this->printStudentInfo();
	else return;
}

void TeachingClasses::printStudentInfo() {
	cout << this->className << "ѧ��һ��" << endl;
	this->calculateTotalScore();
	vector<pair<string, StudentInfo>> toSort(this->stuMap.begin(), this->stuMap.end());
	switch (this->sortOrder) {
	case ASCENDING_NUMBER:
			sort(toSort.begin(), toSort.end(), sortByNumber());
			break;
	case DECENDING_NUMBER:
			sort(toSort.begin(), toSort.end(), sortByNumber());
			reverse(toSort.begin(), toSort.end());
			break;
	case ASCENDING_SCORE:
			sort(toSort.begin(), toSort.end(), sortByScore());
			break;
	case DECENGING_SCORE:
			sort(toSort.begin(), toSort.end(), sortByScore());
			reverse(toSort.begin(), toSort.end());
			break;
	default: break;
	}
	vector<pair<string, StudentInfo>>::iterator it;
	int i = 1;
		cout << "����\t" << "ѧ��\t" << "����\t";
		for (int j = 0; j < this->subjects.size(); j++) cout << this->subjects[j] << "\t";
		cout << "ƽ����" << endl;
	for (it = toSort.begin(); it != toSort.end();it++) {
		cout << i++ << "\t" << (*it).second.getNumber() << "\t" << (*it).second.getName() << "\t";
		for (int j = 0; j < this->subjects.size(); j++)
			cout << (*it).second.getScores()[subjects[j]] << "\t";
		cout << (*it).second.getAverScore() << endl;
	}
}

void TeachingClasses::delASubject() {
	cout << "���ڵĿγ��У�";
	for (auto sub : this->subjects) cout << sub << " ";
	cout << "\n�����뽫Ҫȡ���γ̵����ƣ�";
	string sub;
	cin >> sub;
	if (find(subjects.begin(), subjects.end(), sub) == subjects.end()) {
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
		}
		else {
			map<string, StudentInfo>::iterator it;			
			for (it = stuMap.begin(); it != stuMap.end(); it++) {
				(*it).second.delSubject(sub);
			}
			this->subjects.erase(find(subjects.begin(), subjects.end(), sub));
			cout << "ɾ���ɹ�" << endl;
		}
	}
}

void TeachingClasses::importScores() {
	cout << "���пγ� : ";
	for (auto sub : this->subjects) cout << sub << " ";
	cout << "¼�����ſεĳɼ���" << endl;
	double temp;
	string toImport;
	cin >> toImport;
	int i = 1;
	if (find(subjects.begin(), subjects.end(), toImport) == subjects.end())cout << "���޴˿Σ������ԣ�" << endl;
	else {
		map<string, StudentInfo>::iterator it = this->stuMap.begin();
		for (; it != stuMap.end(); it++) {
			cout << i++ << "/" << this->stuMap.size() << " ������ " << (*it).first << " " << (*it).second.getName() << " ���ſεĳɼ� ��";
			cin >> temp;
			(*it).second.setCertainScore(toImport, temp);
		}
		cout << "¼��ɹ�" << endl;
	}
}

void TeachingClasses::updateAStudentInTheClass(string number) {
	this->delAStudentInTheClass(number);
	string studentNumber;
	do {
		cout << "�������ѧ������ѧ�� : ";
		cin >> studentNumber;
		if (find(AllStudent.begin(), AllStudent.end(), studentNumber) != AllStudent.end())
			cout << "ѧ���Ѵ��ڣ�����������" << endl;
		else break;
	} while (1);
	cout << "�������ѧ���������� : ";
	StudentInfo tempInfo;
	string studentName;
	cin >> studentName;
	tempInfo.setName(studentName);
	tempInfo.setNumber(studentNumber);
	double tempScore;
	map<string, double> subjectAndScores;
	for (int i = 0; i < this->subjects.size(); i++) {
		cout << "�������ѧ���� " << subjects[i] << " �ɼ�" << endl;
		cin >> tempScore;
		subjectAndScores[subjects[i]] = tempScore;
	}
	tempInfo.setScores(subjectAndScores);
	this->stuMap.insert(make_pair(studentNumber, tempInfo));
	AllStudent.erase(find(AllStudent.begin(), AllStudent.end(), number));
	AllStudent.push_back(studentNumber);
}

void TeachingClasses::addStudentsForTheClass(string name, string number) {
	StudentInfo s(name, number);
	this->stuMap.insert(make_pair(number, s));
	return;
}

void TeachingClasses::addStudentsForTheClass(pair<string, StudentInfo> p) {
	this->stuMap.insert(p);
}

void TeachingClasses::delAStudentInTheClass(string tobeDel) {
	this->stuMap.erase(stuMap.find(tobeDel));
}