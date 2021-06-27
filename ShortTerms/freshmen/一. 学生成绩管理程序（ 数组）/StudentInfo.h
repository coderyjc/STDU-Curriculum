#include<iostream>
using namespace std;

class StudentInfo {
public:

    //---------------constructors-------------------- 
    StudentInfo() {
        this->m_name = "null";
        this->m_number = "null";
        this->m_rank = 0;
        this->m_totalScore = 0;
        this->m_averageScore = 0;
        this->m_klass = 0;
    }

    StudentInfo(string number, string name, double* score) {
        this->m_name = name;
        this->m_score[0] = score[0];
        this->m_score[1] = score[1];
        this->m_score[2] = score[2];
        this->m_number = number;
    }

    //-----------operator=------------------

    void operator=(StudentInfo s) {
        setAll(s.getKlass(), s.getRank(), s.getName(), s.getNumber(), s.getScore(), s.getTotalScore(), s.getAverageScore());
    }

    //-----------setters and getters------------------
    int getKlass() {return this->m_klass;}
    string getNumber() {return m_number;}
    string getName() {return m_name;}
    double* getScore() {return m_score;}
    double getTotalScore() { return this->m_totalScore; }
    double getAverageScore() { return this->m_averageScore; }
    double getRank() { return this->m_rank; }
    void setNumber(string number) {this->m_number = number;}
    void setName(string name) {this->m_name = name;}
    void setKlass(int k) {this->m_klass = k;}
    void setScore(double* score) {for (int i = 0; i < 3; i++) m_score[i] = score[i];}
    void setTotal(double t) { this->m_totalScore = t; }
    void setAver(double a) { this->m_averageScore = a; }
    void setRank(int r) { this->m_rank = r; }
    void setAll(int klas, int rank, string name, string number, double* score, double total = 0, double aver = 0) {
        this->m_klass = klas;
        this->m_name = name;
        this->m_rank = rank;
        this->m_number = number;
        this->m_score[0] = score[0];
        this->m_score[1] = score[1];
        this->m_score[2] = score[2];
        this->m_totalScore = total;
        this->m_averageScore = aver;
    }
    
    //------------------other functions-------------------------

    void showSingleInfo() {
        cout << "班级：" << this->m_klass << endl
            << "姓名：" << this->m_name << endl
            << "学号：" << this->m_number << endl
            << "成绩（语文，数学，英语）：" << m_score[0] << " " << m_score[1] << " " << m_score[2] << endl
            << "排名：" << this->m_rank << endl;
    }

private:
    int m_klass;
    string m_number;
    string m_name;
    double m_score[3];

    int m_rank;
    double m_totalScore;
    double m_averageScore;
};
