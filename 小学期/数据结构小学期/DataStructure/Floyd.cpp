//#include <iostream>
//#include<vector>
//
//#define MAX 999999
//
//using namespace std;
//
//// 打印矩阵
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
//// 寻路
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
//// 打印最终结果
//void printResult(vector<vector<int>> graph, vector<vector<int>> path, int n) {
//	cout << "两点" << "\t两点之间的距离" << "\t两点之间的路径" << endl;
//	for (int i = 0; i < n; i++) {
//		for (int j = 0; j < n; j++) {
//			if (i == j) continue;
//			cout << i + 1 << "&" << j + 1 << "\t";
//
//			if (graph[i][j] == MAX) cout << "∞\t\t";
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
//	// 输入节点
//	// 以邻接矩阵的形式存储有向图
//
//	int n, e;
//	cout << "输入顶点数和边数: ";
//	cin >> n >> e;
//
//	vector<int> temp(n, MAX);
//	// 图
//	vector<vector<int>> graph(n, temp);
//	// 路径
//	vector<vector<int>> path(n, temp);
//
//	// 建立邻接矩阵
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (i == j) graph[i][j] = 0;
//		}
//	}
//
//	cout << "初始化完成" << endl;
//
//	int start, end, rank;
//	for (int i = 0; i < e; ++i) {
//		cout << "输入第" << i + 1 << "条边的起点、终点、权值" << endl;
//		cin >> start >> end >> rank;
//		graph[start - 1][end - 1] = rank;
//	}
//
//	cout << "输入完成" << endl;
//
//	// 建立路径数组 
//	for (int i = 0; i < n; ++i) {
//		for (int j = 0; j < n; ++j) {
//			if (graph[i][j] < MAX)  // ij 之间有弧，j 的前驱为 i
//				path[i][j] = i;
//			else path[i][j] = -1;  // ij 之间没有弧，j 没有前驱
//		}
//	}
//
//	// 弗洛伊德算法：
//	for (int k = 0; k < n; ++k) {
//		// i 控制经过的顶点, i 应该是作为中间值存在
//		for (int i = 0; i < n; ++i) {
//			// 起点
//			for (int j = 0; j < n; ++j) {
//				// 终点
//				if (graph[i][j] > graph[i][k] + graph[k][j]) {
//					graph[i][j] = graph[i][k] + graph[k][j];
//					path[i][j] = path[k][j];
//				}
//			}
//		}
//	}
//
//	// 输出
//	cout << "最短路径矩阵为：" << endl;
//	printGraph(graph, n);
//	cout << "路径矩阵为：" << endl;
//	printGraph(path, n);
//	cout << "各边之间的最短路径长度和路径为：" << endl;
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