//#include<iostream>
//#include<vector>
//
//#define MAX 99999
//
//using namespace std;
//
//void dijkstra(vector<vector<int>> graph, int n, int v0);
//
//void printPath(int v0, int v, int* path);
//
//// ��ӡ����
//void printGraph(vector<vector<int>> graph, int n) {
//    cout << "----------------" << endl;
//    for (int j = 0; j < n; ++j) {
//        for (int k = 0; k < n; ++k) {
//            cout << graph[j][k] << "\t";
//        }
//        cout << endl;
//    }
//}
//
//int main() {
//    // ����ڵ�
//    // ���ڽӾ������ʽ�洢����ͼ
//
//    int n, e;
//    cout << "���붥�����ͱ���: ";
//    cin >> n >> e;
//
//    vector<int> temp(n, MAX);
//    // ͼ
//    vector<vector<int>> graph(n, temp);
//    // ·��
//    vector<vector<int>> path(n, temp);
//
//    // �����ڽӾ���
//    for (int i = 0; i < n; ++i) {
//        for (int j = 0; j < n; ++j) {
//            if (i == j) graph[i][j] = 0;
//        }
//    }
//
//    cout << "��ʼ�����" << endl;
//
//    int start, end, rank;
//    for (int i = 0; i < e; ++i) {
//        cout << "�����" << i + 1 << "���ߵ���㡢�յ㡢Ȩֵ" << endl;
//        cin >> start >> end >> rank;
//        graph[start - 1][end - 1] = rank;
//    }
//
//    cout << "�������" << endl;
//
//    cout << "Ҫ�����ĸ��ߵ������ߵ����·����";
//    int v;
//    cin >> v;
//
//    // �Ͻ�˹���������·��
//    dijkstra(graph, n, v);
//
//	return 0;
//}
//
//void dijkstra(vector<vector<int>> graph, int n, int v0){
//
//    // �Ѿ�ѡ��Ķ��㼯��
//    int* selected = new int[n]; 
//
//    // ����
//    int* distance = new int[n];
//
//    // ·��
//    int* path = new int[n];
//
//    // ��ʼ��
//    for (int i = 0; i < n; ++i) {
//        // ��ʼ��δ��ѡ��
//        selected[i] = 0;
//        // update ���¾���
//        distance[v0] = graph[v0][i];
//        if (distance[v0] < MAX) {
//            path[i] = v0; // �ɴ�
//        } else {
//            path[i] = -1; // ���ɴ�
//        }
//    }
//
//    // �� v0 ���� selected ������ѡ��
//    selected[v0] = 1;
//    // �Կɴ�
//    distance[v0] = 0;
//
//    // ������
//    for (int i = 0; i < n; ++i) {
//        int min = MAX;
//        int v = -1;
//        for (int j = 0; j < n; j++) {
//            if (!selected[j] && distance[j] < min) { 
//                // δ��ѡ���ҿɴ�
//                v = j;
//                min = distance[j];
//            }
//        }
//        selected[v] = 1; // ѡ�������
//        for (int j = 0; j < n; j++) {
//            if ( !selected[j] && ( distance[v] + graph[v][j] < distance[j] ) ) {
//                distance[j] = distance[v] + graph[v][j];
//                path[j] = v;
//            }
//        }
//    }
//
//    cout << "Ŀ���\t" << "����\t" << "·��" << endl;
//    for (int i = 0; i < n; i++) {
//        if (i == v0) continue;
//        // ����������
//        cout << i << "\t" << distance[i] << "\t";
//        printPath(v0, i, path);
//    }
//
//    // �ͷ��ڴ�
//    delete[] path;
//    delete[] selected;
//    delete[] distance;
//}
//
//void printPath(int v0, int v, int* path){
//    if (path[v] == v0) {
//        cout << v0 << "\t" << v << "\t";
//    } else {
//        printPath(v0, path[v], path);
//        cout << v << "\t";
//    }
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
//*/