#pragma once
#include<memory>
#include<iostream>
#include<queue>
using namespace std;

const int maxn = 30;
const int CANNOT_REACH = 99999;

class MapNode {
public:
	// ------CONSTRUCTOR------
	MapNode() {
		m_id = 0;
	}

	MapNode(int id) {
		this->m_id = id;
	}
private:
	int m_id;
};

class ArrayMap {

public:

	//-----------CONSTRUCTORS--------------

	ArrayMap() {
		size = 0;
		for (int i = 0; i < 30; i++) for (int j = 0; j < 30; j++) this->data[i][j] = 0;
	}

	//----------DESTRUCTORS-------------
	
	~ArrayMap() {}

	//---------FUNCTIONS-----------------

	// create a array map
	void init();

	//insert a edge
	void insert();

	//delete a edge
	void deleteVtx();

	//get the shortest path
	void shortestPath();

	// main loop of the programe
	void mainLoop();

	void DFSTraverse();
	void DFS(int vtx, int visited[]);

	void BFSTraverse();

	// see the view
	void layout();

private:

	//the number of nodes;
	int size;

	//邻接矩阵，其中存储边的权值
	int data[30][30];

	//图结点
	MapNode node[30];
};

/*
测试成功
*/
void ArrayMap::init() {
	cout << "------\n初始化\n------" << endl;
	cout << "请输入图的结点数量(不大于30)" << endl;
	cin >> this->size;
	while (this->size > 30 || this->size < 0) {
		cout << "输入结点数量有误" << endl;
		cin >> this->size;
	}

	// 设置边和边上的权值
	cout << "初始化边，输入-1结束输入：" << endl;
	int start = 0, end = 0, rank = 0;
	int i = 1;
	while (1) {
		int flag = 1;
		do {
			cout << "请输入起点、终点和权值中间用空格隔开: ";
			cin >> start >> end >> rank;
			if (start < 0 || end < 0) {
				cout << "输入结束" << endl;
				return;
			} else if (start > this->size || end > this->size) {
				cout << "输入错误，请重新输入" << endl;
				flag = 1;
			} else break;
		} while (flag);
		this->data[start - 1][end - 1] = rank;
		this->data[end - 1][start - 1] = rank;
	}
	cout << "------------\n提示\n\n图初始化成功\n------------" << endl;
}


/*
测试成功
*/
void ArrayMap::insert() {
	cout << "--------\n边的添加\n--------" << endl;
	cout << "输入添加的边的起点，终点和权值: ";
	int start, end, rank;
	cin.clear();
	cin >> start >> end >> rank;
	if (start < 1 || end < 1 || start > this->size || end > this->size) {
		cout << "数组下标越界" << endl;
		exit(0);
	} else {
		this->data[start - 1][end - 1] = rank;
		this->data[end - 1][start - 1] = rank;
	}
	cout << "--------\n添加成功\n--------" << endl;
}

/*
将通往该节点的边和该节点通往的边的权置为0，这个方法是否可行？
目前认为是可行的，但是在DFS和BFS的时候可能会遇到一些麻烦
*/
void ArrayMap::deleteVtx() {
	cout << "请输入要删除的点:";
	int vertex = 0;
	cin >> vertex;
	if (vertex < 0 || vertex > this->size) {
		cout << "不存在这个点" << endl;
		exit(0);
	} else {
		for (int i = 0; i < this->size; i++) {
			this->data[vertex - 1][i] = 0;
			this->data[i][vertex - 1] = 0;
		}
	}
	this->data[vertex - 1][0] = -1;
	cout << "--------\n删除成功\n--------" << endl;
}

/*
佛洛伊德算法求最短路径
*/
void ArrayMap::shortestPath() {
	int dist[maxn][maxn] = {}; // 最短距离

	// 初始化最短距离矩阵
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if ((this->data[i][j] == 0 && i != j) || this->data[i][0] == -1) dist[i][j] = CANNOT_REACH;
			// data[i][0] == -1 的时候，看作这个点不存在
			else dist[i][j] = this->data[i][j];
		}
	}
	
	// 打表,即为所求
	for (int k = 0; k < this->size; k++) {
		for (int i = 0; i < this->size; i++) {
			for (int j = 0; j < this->size; j++) {
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j]; // 更新
				}
			}
		}
	}

	// 输入点两点
	cout << "输入两点, 判断其最短距离, 中间用空格隔开: ";
	int v1 = 0, v2 = 0;
	cin.clear();

	// 输入检查
	cin >> v1 >> v2;
	while (v1 < 1 || v1 > 30 || v2 < 1 || v2 > 30) {
		cout << "值不符合要求" << endl;
		cin >> v1 >> v2;
	}

	// 按照条件输出
	if (v1 == v2) {
		cout << "两点最短距离为 0 " << endl;
	} else if (dist[v1 - 1][v2 - 1] == 0 || dist[v1 - 1][v2 - 1] == CANNOT_REACH) {
		cout << "两点不可达" << endl;
	} else {
		cout << "两点最短距离为 " << dist[v1 - 1][v2 - 1] << endl;
	}
}

void ArrayMap::DFSTraverse() {
	cout << "------------\n深度优先遍历\n------------" << endl;

	// 已经遍历过的点
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->data[i][0] == -1) visit[i] = 1;
		else visit[i] = 0;
	}

	for (int i = 0; i < this->size; i++) {
		if (!visit[i])
			this->DFS(i, visit);
	}
	cout << endl;
}

void ArrayMap::DFS(int vtx, int visited[]) {
	cout << "访问节点--->" << vtx + 1 << endl;
	visited[vtx] = 1;
	for (int i = 0; i < this->size; i++) {
		if (this->data[vtx][i] != 0 && !visited[i])
			this->DFS(i, visited);
	}
}

void ArrayMap::BFSTraverse() {
	cout << "------------\n广度优先遍历\n------------" << endl;

	// 已经遍历过的点
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->data[i][0] == -1) visit[i] = 1;
		else visit[i] = 0;
	}

	// 结点队列
	queue<int> q;

	for (int i = 0; i < this->size; i++) {
		if (!visit[i]) {
			visit[i] = 1;
			cout << "访问结点--->" << i + 1 << endl;
			q.push(i);

			while (!q.empty()) {
				i = q.front();
				q.pop();
				for (int j = 0; j < this->size; j++) {
					if (this->data[i][j] != 0 && !visit[j]) {
						visit[j] = 1;
						cout << "访问结点--->" << j + 1 << endl;		
						q.push(j);
					}
				}
			}
		}
	}
	cout << endl;
}

void ArrayMap::layout() {
	if (this->size == 0) {
		cout << "----------\n图未初始化\n----------" << endl;
		return;
	}
	cout << "--------\n邻接矩阵\n--------" << endl;
	for (int i = 0; i < this->size; i++) {
		for (int j = 0; j < this->size; j++) {
			if (this->data[i][j] != 0) cout << this->data[i][j] << "\t";
			else cout << "∞\t";
		}
		cout << endl;
	}
}

void ArrayMap::mainLoop() {

	int choose = 0;

	while (true) {
		cout << "图的邻接矩阵存储" << endl
			<< "-----------------" << endl
			<< "1. 初始化" << endl // yes
			<< "2. 插入边" << endl
			<< "3. 删除节点" << endl
			<< "4. 最短路径" << endl
			<< "5. 深度优先遍历" << endl
			<< "6. 广度优先遍历" << endl
			<< "7. 查看图" << endl
			<< "0. 返回上一层" << endl
			<< "----------------" << endl
			<< "输入测试的功能: " << endl;
		cin >> choose;
		switch (choose) {
			case 1: this->init(); break;
			case 2: this->insert(); break;
			case 3: this->deleteVtx(); break;
			case 4: this->shortestPath(); break;
			case 5: this->DFSTraverse(); break;
			case 6: this->BFSTraverse(); break;
			case 7: this->layout(); break;
		default: return;
		}
		system("pause");
		system("cls");
	}
}