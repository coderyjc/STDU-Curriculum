#include<iostream>
#include<vector>

using namespace std;

// 进程数量
#define M 5
// 资源数量
#define N 3

// 系统可用的资源数
int AVAILABLE[N] = { 2, 3, 3 };
// M 个进程对 N 类资源最大资源需求量
int MAX[M][N] = { {5, 5, 10},{5, 3, 6},{4,0,11},{4,2,5},{4,2,4} };
// M 个进程已经得到 N 类资源的资源量
int ALLOCATION[M][N] = { {3,2,3},{4,0,3},{4,0,5},{2,0,4},{3,1,4} };
// M 个进程还需要 N 类资源的资源量
int NEED[M][N] = {};
// M个进程是否已经运行结束
int COMPELETE[M] = { 0 };

// 计算需求矩阵
void calculateNeed() {
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < N; j++) {
			NEED[i][j] = MAX[i][j] - ALLOCATION[i][j];
			if (NEED[i][j] < 0) NEED[i][j] = 0;
		}
	}
}

// 检查分配状态
int checkStatus(int process, int* require) {
	calculateNeed();
	for (int i = 0; i < N; i++) if (require[i] > AVAILABLE[i]) return 0;
	for (int i = 0; i < N; i++) {
		AVAILABLE[i] -= require[i];
		ALLOCATION[process][i] += require[i];
	}
	// 判断进程是否结束
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

// 打印最大需求矩阵
void printMax() {
	cout << "---[资源需求量]---" << endl;
	cout << "进程号\t资源1\t资源2\t资源3" << endl;
	for (int i = 0; i < M; i++) {
		cout << i << "\t";
		for (int j = 0; j < N; j++) {
			cout << MAX[i][j] << "\t";
		}
		cout << endl;
	}
}

// 打印已经分配的矩阵
void printAllocation() {
	cout << "---[已经分配的资源数量]---" << endl;
	cout << "进程号\t资源1\t资源2\t资源3" << endl;
	for (int i = 0; i < M; i++) {
		cout << i << "\t";
		for (int j = 0; j < N; j++) {
			cout << ALLOCATION[i][j] << "\t";
		}
		cout << endl;
	}
}

// 打印还需要分配的矩阵
void printNeed() {
	calculateNeed();
	cout << "---[还需要的资源数量]---" << endl;
	cout << "进程号\t资源1\t资源2\t资源3\t是否结束" << endl;
	for (int i = 0; i < M; i++) {
		cout << i << "\t";
		for (int j = 0; j < N; j++) {
			cout << NEED[i][j] << "\t";
		}
		cout << COMPELETE[i];
		cout << endl;
	}
}

// 打印系统剩余的资源
void printAvailable() {
	for (int i = 0; i < N; i++)
		cout << "资源" << i << ":" << AVAILABLE[i];
	cout << endl;
}

// 发出请求, 请求资源
void request() {

	int process = -1;
	int* require = new int[N];

	cout << "输入请求资源的进程(0-" << M - 1 << "): >";
	cin >> process;
	if (process < 0 || process >= M) {
		cout << "输入错误, 请重试" << endl;
		return;
	}
	cout << "输入该进程需要的资源数量, 用空格隔开>";
	for (int i = 0; i < N; i++) cin >> require[i];
	int status = checkStatus(process, require);
	if (status) {
		cout << "资源分配成功" << endl;
	}
	else {
		cout << "资源分配失败, 资源不足" << endl;
	}
}

// 计算安全序列
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
	cout << "\n\n一种可能的安全序列: ";
	for (int i = 0; i < M; i++) {
		cout << queue[i] << " ";
	}
	cout << endl;
}


int main() {
	int choose = 0;
	cout << "银行家算法模拟" << endl
		<< "1.输出可能的安全序列." << endl
		<< "2.尝试分配资源." << endl;
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