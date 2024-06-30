#include<iostream>
#include<vector>

using namespace std;

// ��������
#define M 5
// ��Դ����
#define N 3

// ϵͳ���õ���Դ��
int AVAILABLE[N] = { 2, 3, 3 };
// M �����̶� N ����Դ�����Դ������
int MAX[M][N] = { {5, 5, 10},{5, 3, 6},{4,0,11},{4,2,5},{4,2,4} };
// M �������Ѿ��õ� N ����Դ����Դ��
int ALLOCATION[M][N] = { {3,2,3},{4,0,3},{4,0,5},{2,0,4},{3,1,4} };
// M �����̻���Ҫ N ����Դ����Դ��
int NEED[M][N] = {};
// M�������Ƿ��Ѿ����н���
int COMPELETE[M] = { 0 };

// �����������
void calculateNeed() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
			if (NEED[i][j] < 0) NEED[i][j] = 0;
		}
	}
}

// ������״̬
int checkStatus(int process, int* require) {
	calculateNeed();
	for (int i = 0; i < N; i++) if (require[i] > AVAILABLE[i]) return 0;
	for (int i = 0; i < N; i++) {
		AVAILABLE[i] -= require[i];
		ALLOCATION[process][i] += require[i];
	}
	// �жϽ����Ƿ����
	int flag = 2;
	calculateNeed();
	for (int i = 0; i < N; i++) {
		if (NEED[process][i] != 0) {
			flag = 1;
			break;
		}
	}
	if (flag == 2) {
		COMPELETE[process] = 1;
		for (int i = 0; i < N; i++) {
			AVAILABLE[i] += ALLOCATION[process][i];
		}
	}
	return flag;
}

// ��ӡ����������
void printMax() {
	cout << "---[��Դ������]---" << endl;
	cout << "���̺�\t��Դ1\t��Դ2\t��Դ3" << endl;
	for (int i = 0; i < M; i++) {
		cout << i << "\t";
		for (int j = 0; j < N; j++) {
			cout << MAX[i][j] << "\t";
		}
		cout << endl;
	}
}

// ��ӡ�Ѿ�����ľ���
void printAllocation() {
	cout << "---[�Ѿ��������Դ����]---" << endl;
	cout << "���̺�\t��Դ1\t��Դ2\t��Դ3" << endl;
	for (int i = 0; i < M; i++) {
		cout << i << "\t";
		for (int j = 0; j < N; j++) {
			cout << ALLOCATION[i][j] << "\t";
		}
		cout << endl;
	}
}

// ��ӡ����Ҫ����ľ���
void printNeed() {
	calculateNeed();
	cout << "---[����Ҫ����Դ����]---" << endl;
	cout << "���̺�\t��Դ1\t��Դ2\t��Դ3\t�Ƿ����" << endl;
	for (int i = 0; i < M; i++) {
		cout << i << "\t";
		for (int j = 0; j < N; j++) {
			cout << NEED[i][j] << "\t";
		}
		cout << COMPELETE[i];
		cout << endl;
	}
}

// ��ӡϵͳʣ�����Դ
void printAvailable() {
	for (int i = 0; i < N; i++)
		cout << "��Դ" << i << ":" << AVAILABLE[i];
	cout << endl;
}

// ��������, ������Դ
void request() {

	int process = -1;
	int* require = new int[N];

	cout << "����������Դ�Ľ���(0-" << M - 1 << "): >";
	cin >> process;
	if (process < 0 || process >= M) {
		cout << "�������, ������" << endl;
		return;
	}
	cout << "����ý�����Ҫ����Դ����, �ÿո����>";
	for (int i = 0; i < N; i++) cin >> require[i];
	int status = checkStatus(process, require);
	if (status) {
		cout << "��Դ����ɹ�" << endl;
	}
	else {
		cout << "��Դ����ʧ��, ��Դ����" << endl;
	}
}

// ���㰲ȫ����
void safeSequence() {
	calculateNeed();
	vector<int> complete;
	vector<int> queue;
	for (int i = 0; i < M; i++) complete.push_back(i);
	int flag = 1;
	while (complete.size() > 0) {
		for (int i = 0; i < complete.size(); i++){
			if (checkStatus(complete[i], NEED[complete[i]])) {
				queue.push_back(complete[i]);
				complete.erase(complete.begin() + i);
				break;
			}
		}
	}
	cout << "\n\nһ�ֿ��ܵİ�ȫ����: ";
	for (int i = 0; i < M; i++) {
		cout << queue[i] << " ";
	}
	cout << endl;
}


int main() {
	int choose = 0;
	cout << "���м��㷨ģ��" << endl
		<< "1.������ܵİ�ȫ����." << endl
		<< "2.���Է�����Դ." << endl;
	cin >> choose;
	printMax();
	if (choose == 1) {
		printAllocation();
		printNeed();
		printAvailable();
		safeSequence();
	}
	else {
		while (1) {
			printAllocation();
			printNeed();
			printAvailable();
			request();
		}
	}
	return 0;
}