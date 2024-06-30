//#include <iostream>
//#include<vector>
//
//#define MAX 999999
//
//using namespace std;
//
//// ��ӡ����
//void printGraph(vector<vector<int>> graph, int n) {
//	cout << "----------------" << endl;
//	for (int j = 0; j < n; ++j) {
//		for (int k = 0; k < n; ++k) {
//			cout << graph[j][k] << "\t";
//		}
//		cout << endl;
//	}
//}
//
//// Ѱ·
//void printPath(vector<vector<int>> path, int i, int j) {
//	if (path[i][j] == i) {
//		cout << i << "\t" << j << "\t";
//		return;
//	}
//	else {
//		printPath(path, i, path[i][j]);
//		cout << j << "\t";
//	}
//}
//
//// ��ӡ���ս��
//void printResult(vector<vector<int>> graph, vector<vector<int>> path, int n) {
//	cout << "����" << "\t����֮��ľ���" << "\t����֮���·��" << endl;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			if (i == j) continue;
//			cout << i + 1 << "&" << j + 1 << "\t";
//
//			if (graph[i][j] == MAX) cout << "��\t\t";
//			else cout << graph[i][j] << "\t\t";
//
//			printPath(path, i, j);
//			cout << endl;
//		}
//	}
//}
//
//int main() {
//
//	// ����ڵ�
//	// ���ڽӾ������ʽ�洢����ͼ
//
//	int n, e;
//	cout << "���붥�����ͱ���: ";
//	cin >> n >> e;
//
//	vector<int> temp(n, MAX);
//	// ͼ
//	vector<vector<int>> graph(n, temp);
//	// ·��
//	vector<vector<int>> path(n, temp);
//
//	// �����ڽӾ���
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (i == j) graph[i][j] = 0;
//		}
//	}
//
//	cout << "��ʼ�����" << endl;
//
//	int start, end, rank;
//	for (int i = 0; i < e; ++i) {
//		cout << "�����" << i + 1 << "���ߵ���㡢�յ㡢Ȩֵ" << endl;
//		cin >> start >> end >> rank;
//		graph[start - 1][end - 1] = rank;
//	}
//
//	cout << "�������" << endl;
//
//	// ����·������ 
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (graph[i][j] < MAX)  // ij ֮���л���j ��ǰ��Ϊ i
//				path[i][j] = i;
//			else path[i][j] = -1;  // ij ֮��û�л���j û��ǰ��
//		}
//	}
//
//	// ���������㷨��
//	for (int k = 0; k < n; ++k) {
//		// i ���ƾ����Ķ���, i Ӧ������Ϊ�м�ֵ����
//		for (int i = 0; i < n; ++i) {
//			// ���
//			for (int j = 0; j < n; ++j) {
//				// �յ�
//				if (graph[i][j] > graph[i][k] + graph[k][j]) {
//					graph[i][j] = graph[i][k] + graph[k][j];
//					path[i][j] = path[k][j];
//				}
//			}
//		}
//	}
//
//	// ���
//	cout << "���·������Ϊ��" << endl;
//	printGraph(graph, n);
//	cout << "·������Ϊ��" << endl;
//	printGraph(path, n);
//	cout << "����֮������·�����Ⱥ�·��Ϊ��" << endl;
//	printResult(graph, path, n);
//}
//
//
///*
//4 8
//1 2 2
//1 3 6
//1 4 4
//2 3 3
//3 1 7
//3 4 1
//4 1 5
//4 3 12
//
//*/