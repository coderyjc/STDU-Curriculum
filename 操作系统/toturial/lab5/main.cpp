#include <iostream>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// �ŵ�����
#define MAX 200
// ��������
#define COUNT 10
// ��������
vector<int> request(COUNT);
// �ʼ���ڵĴŵ���
int current;
// �����㷨��Ѱ�������Ƚ�
int findTime[4] = { 0, 0, 0, 0 };
int findCount[4] = { 0, 0, 0, 0 };


// ������������к͵�ǰ���ڵĴŵ���, ������
void generateSequence(){
    static unsigned int seq = 0;
    srand(time(0) + (seq++));
    for (int i = 0; i < COUNT; i++) {
        request[i] = rand() % MAX;
    }
    current = rand() % 50;
    cout << "��ʼλ��: " << current << "\n����˳��: ";
    for (auto i : request) cout << i << " ";
    cout << endl;
}

// �����ȷ����㷨
int FCFS() {
    int currentTemp = current;
    cout << "\n\nFCFS\nѰ��˳��: ";
    for (auto i : request) {
        findTime[0] += abs(i - currentTemp);
        findCount[0]++;
        currentTemp = i;
        cout << i << " ";
    }
    return 1;
}

// ���Ѱ��ʱ�������㷨
int SSTF() {
    vector<int> requestTemp(request);
    int currentTemp = current;
    cout << "\n\nSSTF\nѰ��˳��: ";
    while (requestTemp.size() > 0) {
        int minNumber = MAX + 1, index = -1;
        // Ѱ������ĵ���
        for (int i = 0; i < requestTemp.size(); i++) {
           if (minNumber > abs(requestTemp[i] - currentTemp)) {
                minNumber = abs(requestTemp[i] - currentTemp);
                index = i;
            }
        }
        findTime[1] += abs(requestTemp[index] - currentTemp);
        findCount[1]++;
        currentTemp = requestTemp[index];
        cout << currentTemp << " ";
        requestTemp.erase(requestTemp.begin() + index);
    }
    return 1;
}

// ɨ���㷨
int SCAN() {
    vector<int> requestTemp(request);
    sort(requestTemp.begin(), requestTemp.end());
    int currentTemp = current;
    cout << "\n\nSCAN\nѰ��˳��: ";
    // ��������������ƶ�
    int flag = 1;
    for (int i = 0; i < requestTemp.size(); i++) {
        if (flag && requestTemp[i] >= currentTemp) {
            findTime[2] += requestTemp[i] - currentTemp;
            findCount[2]++;
            currentTemp = requestTemp[i];
            cout << currentTemp << " ";
            requestTemp.erase(requestTemp.begin() + i);
            i--;
            if (i == requestTemp.size() - 1) {
               i = -1;
               flag = 0;
               cout << "[199] [0] ";
               findTime[2] += (MAX - 1 - currentTemp + MAX - 1);
               findCount[2] += 2;
               currentTemp = 0;
            }
        }
        else if (!flag) {
            findTime[2] += requestTemp[i] - currentTemp;
            findCount[2]++;
            currentTemp = requestTemp[i];
            cout << currentTemp << " ";
        }
    }
    return 1;
}

// ѭ��ɨ���㷨
int CSCAN() {
    vector<int> requestTemp(request);
    sort(requestTemp.begin(), requestTemp.end());
    int currentTemp = current;
    cout << "\n\nCSCAN\nѰ��˳��: ";
    // ��������������ƶ�
    int direction = 1;
    for (int i = 0; requestTemp.size() > 0; i += direction) {
        if (i == requestTemp.size()) {
            direction = -1;
            findTime[3] += MAX - 1 - currentTemp;
            findCount[3]++;
            currentTemp = MAX - 1;
            cout << '[' << currentTemp << "] ";
        } 
        else if(direction == 1 && requestTemp[i] >= currentTemp) {
            findTime[3] += requestTemp[i] - currentTemp;
            findCount[3]++;
            currentTemp = requestTemp[i];
            requestTemp.erase(requestTemp.begin() + i);
            cout << currentTemp << " ";
            i--;
        }
        else if(direction == -1) {
            findTime[3] += currentTemp - requestTemp[i];
            findCount[3]++;
            currentTemp = requestTemp[i];
            requestTemp.erase(requestTemp.begin() + i);
            cout << currentTemp << " ";
        }
    }
    return 1;
}

void result() {
    cout << "\n\n  �㷨\t��Ѱ��\tƽ��Ѱ��\n"
        << "  FCFS\t" << findTime[0] << '\t' << findTime[0] / findCount[0] << endl
        << "  SSTF\t" << findTime[1] << '\t' << findTime[1] / findCount[1] << endl
        << "  SCAN\t" << findTime[2] << '\t' << findTime[2] / findCount[2] << endl
        << " CSCAN\t" << findTime[3] << '\t' << findTime[3] / findCount[3] << endl;
}

int main() {
    generateSequence();
    FCFS();
    SSTF();
    SCAN();
    CSCAN();
    result();
    return 0;
}