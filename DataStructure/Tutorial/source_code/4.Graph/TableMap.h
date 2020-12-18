#pragma once
#include<iostream>
#include<memory>
#include<queue>
using namespace std;

class TableNode {
public:
	TableNode(int a = 0, TableNode* n = NULL, int d = 0) {
		this->adjVex = a;
		this->nextArc = n;
		this->data = d;
	}

	int data; // data field 
	int adjVex; // 邻接点
	TableNode* nextArc; // 指向vi的下一个边或者弧的节点
};

class HeadNode {
public:
	HeadNode(TableNode* n = NULL, int id = 0, int d = 0) {
		this->id = id;
		this->data = d;
		this->firstarc = n;
	}

	// vi's info
	int data;
	
	// point to the first node
	TableNode* firstarc;

	// 约定 id 为 0 的时候表示节点已经删除了
	int id;
};

class TableMap {
public:
	//----------CONSTRUCTOR------------

	TableMap();

	~TableMap();

	//---------FUNCTIONS-----------------

	// create a array map
	void init();

	// traverse the array map
	void DFSTraverse();
	void BFSTraverse();

	//insert a edge
	void insert();

	//delete a edge
	void deleteVtx();

	//get the shortest path
	void shortestPath();

	// main loop of the programe
	void mainLoop();

	//--------------FUNCTIONS

	void DFS(int edge, int visit[]);

	void layout();

private:
	HeadNode node[30];
	int size;
};

TableMap::TableMap() {
	size = 0;
	for(int i = 0; i < 30; i++) {
		// 把里面的所有的id都置为 1
		// 因为在删除的业务逻辑中，删除一个结点的方法是把 id 置为 0
		this->node[i].id = 1;
	}
}

TableMap::~TableMap() {}

void TableMap::init() {
	cout << "----------\n图的初始化" << endl
		<< "----------" << endl;

	cout << "请输入图的结点数量(不大于30)" << endl;
	cin >> this->size;
	while (this->size > 30 || this->size < 0) {
		cout << "输入结点数量有误" << endl;
		cin >> this->size;
	}
	// 设置各个节点的id
	for (int i = 0; i < this->size; i++) this->node[i].id = i + 1;
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
				cout << "--------\n输入结束\n--------" << endl;
				return;
			} else if (start > this->size || end > this->size) {
				cout << "输入错误，请重新输入" << endl;
				flag = 1;
			} else break;
		} while (flag);
		
		// 头节点的后继是空的时候, 直接指向
		if (this->node[start - 1].firstarc == NULL) {
			this->node[start - 1].firstarc = new TableNode(end - 1, NULL, rank);
		} else {
		// 头节点的后继不是空的时候, 先用指针指到最后一位，再new。
			TableNode* temp = this->node[start - 1].firstarc;
			if (temp->adjVex == end - 1) {
				cout << "------\n边重复\n------" << endl;
				continue;
			}
			while (temp && temp->nextArc) {
				temp = temp->nextArc;
				if (temp->adjVex == end - 1) {
					cout << "------\n边重复\n------" << endl;
					break;
				}
			}
			temp->nextArc = new TableNode(end - 1, NULL, rank);
		}
	}
	cout << "------------\n提示\n\n图初始化成功\n------------" << endl;
}


void TableMap::insert() {
	cout << "--------\n边的插入\n--------" << endl;
	int start = 0, end = 0, rank = 0;
	cin.clear();
	do {
		cout << "输入起点: " << endl;
		cin >> start;
		if (start <= 0 || start > this->size) {
			cout << "输入有误，请重新输入" << endl;
		} else break;
	} while (1);

	do {
		cout << "输入终点: " << endl;
		cin >> end;
		if (end <= 0 || end > this->size) {
			cout << "输入有误，请重新输入" << endl;
		} else break;
	} while (1);

	cout << "输入权值" << endl;
	cin >> rank;
	
	if (this->node[start - 1].firstarc == NULL) {
		// 这个结点还没有指向任何的边
		this->node[start - 1].firstarc = new TableNode(end - 1, NULL, rank);
	} else {
		// 这个结点有出度了
		TableNode* temp = this->node[start - 1].firstarc;
		if (temp->adjVex == end - 1) {
			cout << "--------\n边重复了\n--------" << endl;
			return;
		}
		while (temp->nextArc) {
			temp = temp->nextArc;
			if (temp->adjVex == end - 1) {
				cout << "--------\n边重复了\n--------" << endl;
				return;
			}
		}
		temp->nextArc = new TableNode(end - 1, NULL, rank);
	}
	cout << "--------\n提示\n\n插入成功\n--------" << endl;
}


void TableMap::deleteVtx() {
	cout << "--------\n结点的删除\n--------" << endl;
	cout << "请输入要删除的节点" << endl;
	int todel = 0;
	cin.clear();
	cin >> todel;
	// 输入检查
	while (todel > this->size || todel < 1 || this->node[todel - 1].id == 0) {
		cout << "结点不存在，请重新输入" << endl;
		cin >> todel;
	}
	// 进行删除
	// 对于节点来说，规定id为0的时候表示该节点不存在
	// 然后把出入这个点的所有的点都删掉
	for (int i = 0; i < this->size; i++) { // 遍历所有头节点
		TableNode* temp = this->node[i].firstarc;
		// 首元节点为 0 ，单独处理
		if (temp && (temp->adjVex == todel - 1)) {
			this->node[i].firstarc = this->node[i].firstarc->nextArc;
		}
		// 其余情况
		while (temp && temp->nextArc) {
			if (temp->nextArc->adjVex == todel - 1) {
				temp->nextArc = temp->nextArc->nextArc;
			}
			temp = temp->nextArc;
		}
	}
	// id置为 0
	this->node[todel - 1].id = 0;
	cout << "--------\n提示\n\n删除成功\n--------" << endl;
//	this->size--;
}

// 测试成功
// 最短路径
void TableMap::shortestPath() {

	// 两点之间的最短路径
	int dist[maxn][maxn]; 
	
	// 先把其他的都初始化为一个比较大的数字
	for (int i = 0; i < this->size; i++)
		for (int j = 0; j < this->size; j++)
			dist[i][j] = CANNOT_REACH;
	
	// 初始化dist路径
	for (int i = 0; i < this->size; i++) {
		TableNode* temp = this->node[i].firstarc;
		while (temp) {
			dist[i][temp->adjVex] = temp->data;
			temp = temp->nextArc;
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
	cout << "输入两点, 中间用空格隔开, 判断其最短距离: ";
	int v1 = 0, v2 = 0;
	cin.clear();

	// 输入两个结点，进行判断
	cin >> v1 >> v2;
	while (v1 < 1 || v1 > this->size || v2 < 1 || v2 > this->size || 
		   this->node[v1 - 1].id == 0 || this->node[v2 - 1].id == 0) {
		cout << "--------\n点不存在\n--------" << endl;
		return;
	}

	// 按照条件输出
	if (v1 == v2) {
		cout << "两点最短距离为 0 " << endl;
	} else if (dist[v1 - 1][v2 - 1] == CANNOT_REACH) {
		cout << "两点不可达" << endl;
	} else {
		cout << "两点最短距离为 " << dist[v1 - 1][v2 - 1] << endl;
	}
}

// 深度优先
// 测试成功
void TableMap::DFSTraverse() {
	
	cout << "------------\n深度优先遍历\n------------" << endl;

	// 已经访问过的节点
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->node[i].id != 0)
			visit[i] = 0;
		// 把已经删除的结点看成已经访问过的
		else visit[i] = 1;
	}

	// 深度优先遍历
	for (int i = 0; i < this->size; i++) {
		if (!visit[i])
			this->DFS(i, visit);
	}
	
	// 垃圾回收
	if (visit != NULL) {
		delete[] visit;
		visit = NULL;
	}
	cout << endl;
}

// 测试成功
void TableMap::DFS(int vtx, int visit[]) {
	cout << "访问结点--->" << vtx + 1 << endl;
	visit[vtx] = 1; // 访问当前结点

	//顺着当前结点向下递归访问
	TableNode* temp = this->node[vtx].firstarc;
	while (temp) {
		if (!visit[temp->adjVex]) {
			this->DFS(temp->adjVex, visit);
		}
		temp = temp->nextArc;
	}
}

// 广度优先
// 测试成功
void TableMap::BFSTraverse() {
	cout << "------------\n广度优先遍历\n------------" << endl;

	// 已经访问过的结点
	int* visit = new int[this->size];
	for (int i = 0; i < this->size; i++) {
		if (this->node[i].id != 0)
			visit[i] = 0;
		// 把已经删除的结点看成已经访问过的
		else visit[i] = 1;
	}

	// 结点队列
	queue<int> q;

	for (int i = 0; i < this->size; i++) {
		if (!visit[i]) {
			visit[i] = 1;
			cout << "访问结点--->" << i + 1 << endl;
			q.push(i);

			while (!q.empty()) {
				TableNode* temp = this->node[q.front()].firstarc;
				q.pop();
				while (temp) {
					if (!visit[temp->adjVex]) {
						cout << "访问结点--->" << temp->adjVex + 1 << endl;
						visit[temp->adjVex] = 1;
						q.push(temp->adjVex);
					}
					temp = temp->nextArc;
				}
			}
		}
	}
	cout << endl;
}

// 展示这个图的邻接表
void TableMap::layout() {
	cout << "----------\n查看邻接表\n----------" << endl;

	if (this->size == 0) {
		cout << "--------\n未初始化\n--------" << endl;
		return;
	}

	for (int i = 0; i < this->size; i++) {
		if (this->node[i].id == 0) continue;
		cout << i + 1 << " : |-> ";
		TableNode* t = this->node[i].firstarc;
		while (t) {
			cout << t->adjVex + 1 << " -> ";
			t = t->nextArc;
		}
		cout << "null" << endl;
	}
	cout << endl;
}

void TableMap::mainLoop() {

	int choose = 0;

	while (true) {
		cout << "图的邻接表存储" << endl
			<< "-----------------" << endl
			<< "1. 初始化" << endl
			<< "2. 插入边" << endl
			<< "3. 删除节点" << endl
			<< "4. 最短路径" << endl
			<< "5. 深度优先遍历" << endl
			<< "6. 广度优先遍历" << endl
			<< "7. 查看图" << endl
			<< "0. 返回上一层" << endl
			<< "----------------" << endl
			<< "输入测试的功能: " << endl
			<< "----------------" << endl;
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
