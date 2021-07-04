#include<iostream>
#include<vector>

#define MAX 99999

using namespace std;

void dijkstra(vector<vector<int>> graph, int n, int v0);

void printPath(int v0, int v, int* path);

// 打印矩阵
void printGraph(vector<vector<int>> graph, int n) {
    cout << "----------------" << endl;
    for (int j = 0; j < n; ++j) {
        for (int k = 0; k < n; ++k) {
            cout << graph[j][k] << "\t";
        }
        cout << endl;
    }
}

int main() {
    // 输入节点
    // 以邻接矩阵的形式存储有向图

    int n, e;
    cout << "输入顶点数和边数: ";
    cin >> n >> e;

    vector<int> temp(n, MAX);
    // 图
    vector<vector<int>> graph(n, temp);
    // 路径
    vector<vector<int>> path(n, temp);

    // 建立邻接矩阵
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) graph[i][j] = 0;
        }
    }

    cout << "初始化完成" << endl;

    int start, end, rank;
    for (int i = 0; i < e; ++i) {
        cout << "输入第" << i + 1 << "条边的起点、终点、权值" << endl;
        cin >> start >> end >> rank;
        graph[start - 1][end - 1] = rank;
    }

    cout << "输入完成" << endl;

    cout << "要计算哪个边到其他边的最短路径？";
    int v;
    cin >> v;

    // 迪杰斯特拉求最短路径
    dijkstra(graph, n, v);

	return 0;
}

void dijkstra(vector<vector<int>> graph, int n, int v0){

    // 已经选择的顶点集合
    int* selected = new int[n]; 

    // 距离
    int* distance = new int[n];

    // 路径
    int* path = new int[n];

    // 初始化
    for (int i = 0; i < n; ++i) {
        // 初始都未被选中
        selected[i] = 0;
        // update 更新距离
        distance[v0] = graph[v0][i];
        if (distance[v0] < MAX) {
            path[i] = v0; // 可达
        } else {
            path[i] = -1; // 不可达
        }
    }

    // 将 v0 加入 selected 代表已选中
    selected[v0] = 1;
    // 自可达
    distance[v0] = 0;

    // 主程序
    for (int i = 0; i < n; ++i) {
        int min = MAX;
        int v = -1;
        for (int j = 0; j < n; j++) {
            if (!selected[j] && distance[j] < min) { 
                // 未被选中且可达
                v = j;
                min = distance[j];
            }
        }
        selected[v] = 1; // 选中这个点
        for (int j = 0; j < n; j++) {
            if ( !selected[j] && ( distance[v] + graph[v][j] < distance[j] ) ) {
                distance[j] = distance[v] + graph[v][j];
                path[j] = v;
            }
        }
    }

    cout << "目标点\t" << "距离\t" << "路径" << endl;
    for (int i = 0; i < n; i++) {
        if (i == v0) continue;
        // 输出相关数据
        cout << i << "\t" << distance[i] << "\t";
        printPath(v0, i, path);
    }

    // 释放内存
    delete[] path;
    delete[] selected;
    delete[] distance;
}

void printPath(int v0, int v, int* path){
    if (path[v] == v0) {
        cout << v0 << "\t" << v << "\t";
    } else {
        printPath(v0, path[v], path);
        cout << v << "\t";
    }
}


/*
4 8
1 2 2
1 3 6
1 4 4
2 3 3
3 1 7
3 4 1
4 1 5
4 3 12
*/