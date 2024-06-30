#include"StudentInfo.h"
#include<fstream>
#include<algorithm>
#include<numeric>
#include<Windows.h>

const int DEFAULT_SIZE = 10;

class StudentManager {
public:
	//------Constructor------------------

	StudentManager() { 
		this->_size = 0;
		this->_capacity = DEFAULT_SIZE; 
		this->stud = new StudentInfo[DEFAULT_SIZE]; 
		this->filePath = "studentInfo.txt"; 
	}

	//-------destructor------------------

	~StudentManager() { 
		delete[] this->stud;
	}

	//-------------Main Function------------------
	
	void createFiles() {
		system("cls");
		cout << "->���ڴ����ļ�<-" << endl;
		cout << "�������ļ�·����";
		cin >> this->filePath;
		ofstream ofs(filePath, ios::trunc);
		cout << "\n\t�ļ������ɹ� !\n" << endl;
		ofs.close();
		system("pause");
		system("cls");
	}
	
	void importFile() {
		system("cls");
		cout << "->���ڵ����ļ�<-\n" << endl;
		cout << "�������ļ�·��: ";
		cin >> this->filePath;
		ifstream ifs(filePath, ios::in);
		int rank, clas;
		int i = 0;
		string name ,number; 
		double score[3] = {0, 0, 0}, total, aver;
		if (!ifs) {
			cout << "\n\t�ļ���ʧ��\n" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "��ѡ���ļ��е��������ͣ�" << endl
			<< "1. ֻ��ѧ������������ѧ����ͬһ�ࣨ�༶�ֶ����룩" << endl
			<< "2. ������ɷ�ʽΪ�༶ ����" << endl
			<< "3. ������ɷ�ʽΪ�༶ ѧ�� ���� " << endl
			<< "4. ����ӱ������б�����ļ�" << endl;
		int choose = 0;
		cin >> choose;
		switch(choose) {
		case 1: 
			cout << "��������Щѧ�����ڵİ༶��";
			cin >> clas;
			while (!ifs.eof()) {
				if (++_size >= _capacity)
					this->ArrayExtension();
				ifs >> name;
				stud[i].setAll(clas, 0, name, "null", score, 0, 0);
				i++;
			}
			break;
		case 2:
			while (!ifs.eof()) {
				if (++_size >= _capacity)
					this->ArrayExtension();
				ifs >> clas >> name;
				stud[i].setAll(clas, 0, name, "null", score, 0, 0);
				i++;
			}
			break;
		case 3:
			while (!ifs.eof()) {
				if (++_size >= _capacity)
					this->ArrayExtension();
				ifs >> clas >> number >> name;
				stud[i].setAll(clas, 0, name, number, score, 0, 0);
				i++;
			}
			break;
		case 4:
			for (i = 0; !ifs.eof(); i++) {
				if (++_size > _capacity) this->ArrayExtension(1);
				ifs >> clas >> rank >> number >> name >> score[0]
				>> score[1] >> score[2] >> total >> aver;
				stud[i].setAll(clas, rank, name, number, score, total, aver);
			}
			break;
		default: 
			cout << "\n\t����ʧ��\n";system("pause");system("cls");
			return;
		}
		cout << "\n\t�ļ���ȡ�ɹ� !\n" << endl;
		ifs.close();
		system("pause");
		system("cls");
	}
	
	void showAllInfo() {
		system("cls");
		if (_size == 0) {
			cout << "\n\t��ǰû��ѧ����Ϣ\n" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "\n\n------------\n|  �ɼ���  |\n------------\n\n";
		cout << "�༶\t����\tѧ��\t����\t����\t��ѧ\tӢ��\t�ܷ�\tƽ����" << endl;
		for (int i = 0; i < _size; i++) {
			cout << stud[i].getKlass() << "\t"
				<< stud[i].getRank() << "\t"
				<< stud[i].getNumber() << "\t"
				<< stud[i].getName() << "\t"
				<< stud[i].getScore()[0] << "\t"
				<< stud[i].getScore()[1] << "\t"
				<< stud[i].getScore()[2] << "\t"
				<< stud[i].getTotalScore() << "\t"
				<< stud[i].getAverageScore() << endl;
		}
		cout << endl;
		system("pause");
		system("cls");
	}
	
	void addStudent() {
		system("cls");
		cout << "->�������ѧ����Ϣ<-\n" << endl;
		int numberOfAdd = 0;
		cout << "���������ѧ�������� ��";
		cin >> numberOfAdd;
		while (numberOfAdd + _size > _capacity)
			this->ArrayExtension();
		string tNumber, tName;
		double tScore[3];
		int clas;
		for (int i = 0; i < numberOfAdd; i++) {
			cout << "\n��ʼ¼��� " << i + 1 << " λѧ������Ϣ.." << endl;
			cout << "������ѧ����ѧ��: ";
			cin >> tNumber;
			if (findAStudent(tNumber) != -1) {
				cout << "ѧ���ظ��������������д\nѧ�ţ�";
				cin >> tNumber;
				if (findAStudent(tNumber) != -1) {
					cout << "\n\t�����ظ����Զ��˳�\n" << endl;
					system("pause");
					system("cls");
					return;
				}
			}
			cout << "������������ڵİ༶:";
			cin >> clas;
			cout << "������ѧ��������:" ;
			cin >> tName;
			cout << "������ѧ�������� ��ѧ Ӣ��ɼ����м��ÿո����: ";
			cin >> tScore[0] >> tScore[1] >> tScore[2];
			this->stud[_size].setKlass(clas);
			this->stud[_size].setName(tName);
			this->stud[_size].setNumber(tNumber);
			this->stud[_size].setScore(tScore);
			cout << "�� " << i + 1 << " λѧ���ĳɼ�¼��ɹ�\n" << endl;
			_size++;
		}
		cout << "ѧ����Ϣ¼�����.\n" << endl;
		system("pause");
		system("cls");
	}
	
	void deleteStudent() {
		system("cls");
		cout << "->����ɾ��ѧ����Ϣ<-\n" << endl;
		int flag = 0;
		int studNumber = -1;
		 do{
			cout << "����������ɾ����ѧ����ѧ��:" << endl;
			string toDeleted;
			cin >> toDeleted;
			studNumber = findAStudent(toDeleted);
			if (studNumber == -1) {
				cout << "���޴��ˣ��������뻹�Ƿ�����һ�㣿���������룺1/������һ�㣺0���������룺";
				int choose;
				cin >> choose;
				if (!choose) {
					system("pause");
					system("cls");
					return;
				} else flag = 1;
			} else flag = 0;
		 } while (flag);
		 cout << "��ȷ����Ҫɾ����ѧ������Ϣ��" << endl;
		 this->stud[studNumber].showSingleInfo();
		 cout << "\nȷ��ɾ���밴 1 �� �˳��밴 0" << endl;
		 int del = 0;
		 cin >> del;
		 if (!del) {
			 system("pause");
			 system("cls");
			 return;
		 }
		 for (int i = studNumber; i <= _size; i++) {
			 stud[i] = stud[i + 1];
		 }
		 _size--;
		 cout << "ɾ���ɹ���" << endl;
		 		system("pause");
		system("cls");
	}
	
	void updateStudent() {
		system("cls");
		cout << "->���ڸ���ѧ����Ϣ<-" << endl;
		cout << "\n��������Ҫ���µ�ѧ����ѧ�� : ";
		string toUpdate;
		cin >> toUpdate;
		int studPosi = findAStudent(toUpdate);
		if (studPosi == -1) {
			cout << "���޴���,�Ƿ�Ҫ�������룿���ǣ�1/��0��:";
			int choose;
			cin >> choose;
			if (!choose) return;
			else {
				cout << "ѧ�� ��";
				cin >> toUpdate;
			}
			studPosi = findAStudent(toUpdate);
			if (studPosi == -1) return;
		}
		cout << "��ȷ����Ҫ���µ�ѧ������Ϣ��" << endl;
		this->stud[studPosi].showSingleInfo();
		cout << "\n������ѧ��������Ϣ\n" << endl;
		string tNumber, tName;
		double tScore[3];
		int clas;
		cout << "������ѧ�����ڵİ༶" << endl;
		cin >> clas;
		cout << "������ѧ����ѧ��" << endl;
		cin >> tNumber;
		if (findAStudent(tNumber) != -1) {
			cout << "ѧ���ظ�����ȷ�Ϻ��ٴ���д��" << endl;
			cin >> tNumber;
			if (findAStudent(tNumber) != -1) {
				cout << "\n�����ظ����Զ��˳�\n" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		cout << "������ѧ��������" << endl;
		cin >> tName;
		cout << "������ѧ�������� ��ѧ Ӣ��ɼ����м��ÿո����" << endl;
		cin >> tScore[0] >> tScore[1] >> tScore[2];
		this->stud[studPosi].setKlass(clas);
		this->stud[studPosi].setName(tName);
		this->stud[studPosi].setNumber(tNumber);
		this->stud[studPosi].setScore(tScore);
		cout << "\nѧ���ĳɼ����³ɹ�!\n" << endl;
		system("pause");
		system("cls");
	}

	void findStudentInfo() {
		system("cls");
		cout << "��������Ҫ���ҵ�ѧ����ѧ�ţ�";
		string toFound;
		cin >> toFound;
		int isFound = findAStudent(toFound);
		cout << endl;
		if (isFound != -1)
			this->stud[isFound].showSingleInfo();
		else
			cout << "���޴���" << endl;
		system("pause");
		system("cls");
	}

	void sigmaScores() {
		system("cls");
		cout << "->���ڼ���ѧ���ֺܷ�ƽ����<-" << endl;
		double total = 0.0;
		double aver = 0;
		for (int i = 0; i < _size; i++) {
			total = accumulate(stud[i].getScore(), stud[i].getScore() + 3, 0);
			aver = total / 3;
			stud[i].setTotal(total);
			stud[i].setAver(aver);
		}
		cout << "�����ֺܷ�ƽ���ֳɹ�" << endl;
		system("pause");
		system("cls");
	}

	void sortScores() {
		system("cls");
		cout << "->���ڽ���ѧ������<-" << endl;
		if (_size == 0) {
			cout << "����ѧ����¼" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "��ѡ������ʽ��" << endl
			<< "1. ���հ༶����\n2. ����ѧ������\n3. ���շ���������" << endl;
		int sortMeans1;
		cout << "����������ʽ��";
		cin >> sortMeans1;
		cout << "��ѡ��������(0:����/1:����)��" << endl;
		int sortMeans2;
		cin >> sortMeans2;
		switch (sortMeans1) {
		case 1:
			sort(this->stud, this->stud + _size, SortByClass()); 
			if (!sortMeans2) reverse(this->stud, this->stud + _size);
			updateRank(); 
			break;
		case 2: 
			sort(this->stud, this->stud + _size, SortByNumbers()); 
			if (!sortMeans2) reverse(this->stud, this->stud + _size);
			updateRank();
			break;
		case 3:
			sort(this->stud, this->stud + _size, SortByTotalScores()); 
			if (!sortMeans2) reverse(this->stud, this->stud + _size);
			updateRank();
			break;
		default: 
			cout << "��������" << endl; 
			break;
		} 
		cout << "�������" << endl;
		system("pause");
		system("cls");
	}

	void saveFile() {
		system("cls");
		cout << "->���ڱ����ļ�<-\n" << endl;
		if (this->filePath != "")
			cout << "����ǰ���ļ�����·��Ϊ : " << this->filePath << endl;
		cout << "\n�Ƿ�����ļ�����·�� ��(�ǣ�1/��0) ";
		int flag;
		cin >> flag;
		if (flag) {
			cout << "�����뱣���ļ���·����";
			cin >> this->filePath;
		}
		ofstream ofs(this->filePath, ios::trunc);
		if (!ofs) {
			cout << "�ļ���ʧ��" << endl;
			return;
		}
		for (int i = 0; i < _size; i++)
			ofs << stud[i].getKlass() << "\t"
			<< stud[i].getRank() << "\t"
			<< stud[i].getNumber() << "\t"
			<< stud[i].getName() << "\t"
			<< stud[i].getScore()[0] << "\t"
			<< stud[i].getScore()[1] << "\t"
			<< stud[i].getScore()[2] << "\t"
			<< stud[i].getTotalScore() << "\t"
			<< stud[i].getAverageScore() << endl;
		cout << "�ļ�����ɹ�!" << endl;
		ofs.close();
		system("pause");
		system("cls");
	}

	void insertStudent() {
		system("cls");
		cout << "->���ڲ���ѧ����Ϣ<-" << endl;
		cout << "������������ʽ��" << endl
			<< "1. ��ѧ�Ų���" << endl
			<< "2. ���༶����" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			cout << "�����뽫Ҫ��������ѧ����ѧ�ţ�";
			string number;
			cin >> number;
			int posi = findAStudent(number);
			if (posi == -1) {
				cout << "���޴��ˣ������²���" << endl;
				system("pause");
				system("cls");
				return;
			}
			if (++_size > _capacity) ArrayExtension();
			string numberToInsert, nameToInsert;
			double scoreToInsert[3];
			int klas;
			cout << "������ѧ�����ڵİ༶" << endl;
			cin >> klas;
			cout << "������ѧ��ѧ��" << endl;
			cin >> numberToInsert;
			cout << "������ѧ������" << endl;
			cin >> nameToInsert;
			cout << "������ѧ���ɼ�(���� ��ѧ Ӣ��ɼ����м��ÿո����)" << endl;
			cin >> scoreToInsert[0] >> scoreToInsert[1] >> scoreToInsert[2]; 
			createAStudent(klas, numberToInsert, nameToInsert, scoreToInsert, posi);
		} else if (choose == 2) {
			if (++_size > _capacity) ArrayExtension();
			string numberToInsert, nameToInsert;
			double scoreToInsert[3];
			int klas;
			cout << "�����뽫ѧ������İ༶" << endl;
			cin >> klas;
			cout << "������ѧ��ѧ��" << endl;
			cin >> numberToInsert;
			cout << "������ѧ������" << endl;
			cin >> nameToInsert;
			cout << "������ѧ���ɼ�(���� ��ѧ Ӣ��ɼ����м��ÿո����)" << endl;
			cin >> scoreToInsert[0] >> scoreToInsert[1] >> scoreToInsert[2];
			createAStudent(klas, numberToInsert, nameToInsert, scoreToInsert);
			sort(this->stud, this->stud + _size, SortByClass()); 
		} else {
			cout << "�������� �����½���" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "����ѧ����Ϣ�ɹ�" << endl;
		system("pause");
		system("cls");
	}
	
	//------------------Other Functions---------------
	
	void ArrayExtension(int isStart = 0) { //isStart �ǲ��Ǹմ򿪳���
		this->_capacity *= 2;
		StudentInfo* temp = new StudentInfo[_capacity];
		if (!temp) cout << "��������ʧ��" << endl;
		for (int i = 0; i < _size; i++) {
			if (isStart) break;
			temp[i] = this->stud[i];
		}
		delete[] this->stud;
		this->stud = temp;
	}

	void updateRank() {
		for (int i = 0; i < _size; i++)
			stud[i].setRank(i + 1);
	}

	int findAStudent(string number) {
		for (int i = 0; i < _size; i++) {
			if (number == stud[i].getNumber())
				return i;
		}
		return -1;
	}

	void showMenu() {
		cout << "------ѧ����Ϣ����ϵͳ--------" << endl 
			<< "| 1.  ����ѧ����Ϣ�ļ�       |" << endl
			<< "| 2.  ���ļ�����ѧ����Ϣ     |" << endl
			<< "| 3.  ��ʾȫ��ѧ����Ϣ       |" << endl
			<< "| 4.  ѧ����Ϣ����¼��       |" << endl
			<< "| 5.  ɾ��һλѧ����Ϣ       |" << endl
			<< "| 6.  ����һλѧ����Ϣ       |" << endl
			<< "| 7.  ����һλѧ����Ϣ       |" << endl
			<< "| 8.  ����ƽ���ֺ��ܷ�       |" << endl
			<< "| 9.  ��ѧ�Ż����ܷ�����     |" << endl
			<< "| 10. ��������ѧ����Ϣ���ļ� |" << endl
			<< "| 11. ����ѧ����Ϣ��ָ��λ�� |" << endl
			<< "| 0.  �˳�ϵͳ               |" << endl
			<< "------------------------------" << endl;
	}
	
	void createAStudent(int clas, string num, string name, double* score, int posi = 0) {
		for (int i = _size; i > posi; i--) {
			stud[i] = stud[i - 1];
		}
		stud[posi].setAll(clas, 0, name, num, score);
	}

	class SortByClass {
	public:
		bool operator()(StudentInfo& s1, StudentInfo& s2) {
			return s1.getKlass() > s2.getKlass();
		}
	};

	class SortByTotalScores {
	public:
		bool operator()(StudentInfo& s1, StudentInfo& s2) {
			return s1.getTotalScore() > s2.getTotalScore();
		}
	};

	class SortByNumbers {
	public:
		bool operator()(StudentInfo& s1, StudentInfo& s2) {
			return s1.getNumber() > s2.getNumber();
		}
	};

private:
	int _size;
	int _capacity;
	StudentInfo* stud;
	string filePath;
};

/*
     1001  1 A       78      98      56
      1002 1   B       45      88.5    68.5
    1003 1   C       78      98      55
*/