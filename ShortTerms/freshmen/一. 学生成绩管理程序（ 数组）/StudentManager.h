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
		cout << "->正在创建文件<-" << endl;
		cout << "请输入文件路径：";
		cin >> this->filePath;
		ofstream ofs(filePath, ios::trunc);
		cout << "\n\t文件创建成功 !\n" << endl;
		ofs.close();
		system("pause");
		system("cls");
	}
	
	void importFile() {
		system("cls");
		cout << "->正在导入文件<-\n" << endl;
		cout << "请输入文件路径: ";
		cin >> this->filePath;
		ifstream ifs(filePath, ios::in);
		int rank, clas;
		int i = 0;
		string name ,number; 
		double score[3] = {0, 0, 0}, total, aver;
		if (!ifs) {
			cout << "\n\t文件打开失败\n" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "请选择文件中的数据类型：" << endl
			<< "1. 只有学生姓名，所有学生在同一班（班级手动输入）" << endl
			<< "2. 数据组成方式为班级 姓名" << endl
			<< "3. 数据组成方式为班级 学号 姓名 " << endl
			<< "4. 导入从本程序中保存的文件" << endl;
		int choose = 0;
		cin >> choose;
		switch(choose) {
		case 1: 
			cout << "请输入这些学生所在的班级：";
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
			cout << "\n\t导入失败\n";system("pause");system("cls");
			return;
		}
		cout << "\n\t文件读取成功 !\n" << endl;
		ifs.close();
		system("pause");
		system("cls");
	}
	
	void showAllInfo() {
		system("cls");
		if (_size == 0) {
			cout << "\n\t当前没有学生信息\n" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "\n\n------------\n|  成绩单  |\n------------\n\n";
		cout << "班级\t排名\t学号\t姓名\t语文\t数学\t英语\t总分\t平均分" << endl;
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
		cout << "->正在添加学生信息<-\n" << endl;
		int numberOfAdd = 0;
		cout << "请输入添加学生的数量 ：";
		cin >> numberOfAdd;
		while (numberOfAdd + _size > _capacity)
			this->ArrayExtension();
		string tNumber, tName;
		double tScore[3];
		int clas;
		for (int i = 0; i < numberOfAdd; i++) {
			cout << "\n开始录入第 " << i + 1 << " 位学生的信息.." << endl;
			cout << "请输入学生的学号: ";
			cin >> tNumber;
			if (findAStudent(tNumber) != -1) {
				cout << "学号重复，请检查后重新填写\n学号：";
				cin >> tNumber;
				if (findAStudent(tNumber) != -1) {
					cout << "\n\t两次重复，自动退出\n" << endl;
					system("pause");
					system("cls");
					return;
				}
			}
			cout << "请输入该生所在的班级:";
			cin >> clas;
			cout << "请输入学生的姓名:" ;
			cin >> tName;
			cout << "请输入学生的语文 数学 英语成绩，中间用空格隔开: ";
			cin >> tScore[0] >> tScore[1] >> tScore[2];
			this->stud[_size].setKlass(clas);
			this->stud[_size].setName(tName);
			this->stud[_size].setNumber(tNumber);
			this->stud[_size].setScore(tScore);
			cout << "第 " << i + 1 << " 位学生的成绩录入成功\n" << endl;
			_size++;
		}
		cout << "学生信息录入完毕.\n" << endl;
		system("pause");
		system("cls");
	}
	
	void deleteStudent() {
		system("cls");
		cout << "->正在删除学生信息<-\n" << endl;
		int flag = 0;
		int studNumber = -1;
		 do{
			cout << "请输入您想删除的学生的学号:" << endl;
			string toDeleted;
			cin >> toDeleted;
			studNumber = findAStudent(toDeleted);
			if (studNumber == -1) {
				cout << "查无此人，重新输入还是返回上一层？（重新输入：1/返回上一层：0），请输入：";
				int choose;
				cin >> choose;
				if (!choose) {
					system("pause");
					system("cls");
					return;
				} else flag = 1;
			} else flag = 0;
		 } while (flag);
		 cout << "请确认您要删除的学生的信息：" << endl;
		 this->stud[studNumber].showSingleInfo();
		 cout << "\n确认删除请按 1 ， 退出请按 0" << endl;
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
		 cout << "删除成功。" << endl;
		 		system("pause");
		system("cls");
	}
	
	void updateStudent() {
		system("cls");
		cout << "->正在更新学生信息<-" << endl;
		cout << "\n请输入您要更新的学生的学号 : ";
		string toUpdate;
		cin >> toUpdate;
		int studPosi = findAStudent(toUpdate);
		if (studPosi == -1) {
			cout << "查无此人,是否要重新输入？（是：1/否：0）:";
			int choose;
			cin >> choose;
			if (!choose) return;
			else {
				cout << "学号 ：";
				cin >> toUpdate;
			}
			studPosi = findAStudent(toUpdate);
			if (studPosi == -1) return;
		}
		cout << "请确认您要更新的学生的信息：" << endl;
		this->stud[studPosi].showSingleInfo();
		cout << "\n请输入学生的新信息\n" << endl;
		string tNumber, tName;
		double tScore[3];
		int clas;
		cout << "请输入学生所在的班级" << endl;
		cin >> clas;
		cout << "请输入学生的学号" << endl;
		cin >> tNumber;
		if (findAStudent(tNumber) != -1) {
			cout << "学号重复，请确认后再次填写。" << endl;
			cin >> tNumber;
			if (findAStudent(tNumber) != -1) {
				cout << "\n两次重复，自动退出\n" << endl;
				system("pause");
				system("cls");
				return;
			}
		}
		cout << "请输入学生的姓名" << endl;
		cin >> tName;
		cout << "请输入学生的语文 数学 英语成绩，中间用空格隔开" << endl;
		cin >> tScore[0] >> tScore[1] >> tScore[2];
		this->stud[studPosi].setKlass(clas);
		this->stud[studPosi].setName(tName);
		this->stud[studPosi].setNumber(tNumber);
		this->stud[studPosi].setScore(tScore);
		cout << "\n学生的成绩更新成功!\n" << endl;
		system("pause");
		system("cls");
	}

	void findStudentInfo() {
		system("cls");
		cout << "请输入您要查找的学生的学号：";
		string toFound;
		cin >> toFound;
		int isFound = findAStudent(toFound);
		cout << endl;
		if (isFound != -1)
			this->stud[isFound].showSingleInfo();
		else
			cout << "查无此人" << endl;
		system("pause");
		system("cls");
	}

	void sigmaScores() {
		system("cls");
		cout << "->正在计算学生总分和平均分<-" << endl;
		double total = 0.0;
		double aver = 0;
		for (int i = 0; i < _size; i++) {
			total = accumulate(stud[i].getScore(), stud[i].getScore() + 3, 0);
			aver = total / 3;
			stud[i].setTotal(total);
			stud[i].setAver(aver);
		}
		cout << "计算总分和平均分成功" << endl;
		system("pause");
		system("cls");
	}

	void sortScores() {
		system("cls");
		cout << "->正在进行学生排序<-" << endl;
		if (_size == 0) {
			cout << "暂无学生记录" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "请选择排序方式：" << endl
			<< "1. 按照班级排序\n2. 按照学号排序\n3. 按照分数排排序" << endl;
		int sortMeans1;
		cout << "请输入排序方式：";
		cin >> sortMeans1;
		cout << "请选择升降序(0:升序/1:降序)：" << endl;
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
			cout << "输入有误。" << endl; 
			break;
		} 
		cout << "排序完成" << endl;
		system("pause");
		system("cls");
	}

	void saveFile() {
		system("cls");
		cout << "->正在保存文件<-\n" << endl;
		if (this->filePath != "")
			cout << "您当前的文件保存路径为 : " << this->filePath << endl;
		cout << "\n是否更换文件保存路径 ？(是：1/否：0) ";
		int flag;
		cin >> flag;
		if (flag) {
			cout << "请输入保存文件的路径：";
			cin >> this->filePath;
		}
		ofstream ofs(this->filePath, ios::trunc);
		if (!ofs) {
			cout << "文件打开失败" << endl;
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
		cout << "文件保存成功!" << endl;
		ofs.close();
		system("pause");
		system("cls");
	}

	void insertStudent() {
		system("cls");
		cout << "->正在插入学生信息<-" << endl;
		cout << "请输入插入的形式：" << endl
			<< "1. 按学号插入" << endl
			<< "2. 按班级插入" << endl;
		int choose;
		cin >> choose;
		if (choose == 1) {
			cout << "请输入将要在其后面的学生的学号：";
			string number;
			cin >> number;
			int posi = findAStudent(number);
			if (posi == -1) {
				cout << "查无此人，请重新操作" << endl;
				system("pause");
				system("cls");
				return;
			}
			if (++_size > _capacity) ArrayExtension();
			string numberToInsert, nameToInsert;
			double scoreToInsert[3];
			int klas;
			cout << "请输入学生所在的班级" << endl;
			cin >> klas;
			cout << "请输入学生学号" << endl;
			cin >> numberToInsert;
			cout << "请输入学生姓名" << endl;
			cin >> nameToInsert;
			cout << "请输入学生成绩(语文 数学 英语成绩，中间用空格隔开)" << endl;
			cin >> scoreToInsert[0] >> scoreToInsert[1] >> scoreToInsert[2]; 
			createAStudent(klas, numberToInsert, nameToInsert, scoreToInsert, posi);
		} else if (choose == 2) {
			if (++_size > _capacity) ArrayExtension();
			string numberToInsert, nameToInsert;
			double scoreToInsert[3];
			int klas;
			cout << "请输入将学生插入的班级" << endl;
			cin >> klas;
			cout << "请输入学生学号" << endl;
			cin >> numberToInsert;
			cout << "请输入学生姓名" << endl;
			cin >> nameToInsert;
			cout << "请输入学生成绩(语文 数学 英语成绩，中间用空格隔开)" << endl;
			cin >> scoreToInsert[0] >> scoreToInsert[1] >> scoreToInsert[2];
			createAStudent(klas, numberToInsert, nameToInsert, scoreToInsert);
			sort(this->stud, this->stud + _size, SortByClass()); 
		} else {
			cout << "输入有误， 请重新进入" << endl;
			system("pause");
			system("cls");
			return;
		}
		cout << "插入学生信息成功" << endl;
		system("pause");
		system("cls");
	}
	
	//------------------Other Functions---------------
	
	void ArrayExtension(int isStart = 0) { //isStart 是不是刚打开程序
		this->_capacity *= 2;
		StudentInfo* temp = new StudentInfo[_capacity];
		if (!temp) cout << "数组扩容失败" << endl;
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
		cout << "------学生信息管理系统--------" << endl 
			<< "| 1.  创建学生信息文件       |" << endl
			<< "| 2.  从文件导入学生信息     |" << endl
			<< "| 3.  显示全部学生信息       |" << endl
			<< "| 4.  学生信息增加录入       |" << endl
			<< "| 5.  删除一位学生信息       |" << endl
			<< "| 6.  更新一位学生信息       |" << endl
			<< "| 7.  查找一位学生信息       |" << endl
			<< "| 8.  计算平均分和总分       |" << endl
			<< "| 9.  按学号或者总分排序     |" << endl
			<< "| 10. 导出所有学生信息到文件 |" << endl
			<< "| 11. 插入学生信息到指定位置 |" << endl
			<< "| 0.  退出系统               |" << endl
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