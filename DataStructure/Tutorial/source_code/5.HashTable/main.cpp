#include<iostream>
#include<fstream>
#include<string>
using namespace std;

// 哈希表节点
class ListNode {
public:
	ListNode() {
		this->data = "";
		this->next = NULL;
	}

	ListNode(string data, ListNode* next) {
		this->data = data;
		this->next = next;
	}

	ListNode* next;
	string data;
};

string names[30];
ListNode* hashTable = new ListNode[27];

// 文件读取没有问题
void readFile() {
	string path;
	cout << "请输入文件的路径 : ";
	cin >> path;
	ifstream ifs(path, ios::in);
	if (!ifs) {
		cout << "文件路径输入错误..." << endl;
		exit(0);
	}
	for (int i = 0; i < 30; i++) {
		getline(ifs, names[i]);
	}
	ifs.close();
}

// 输入名字
void enterName() {
	int i = 1;
	while (i <= 30) {
		cout << "请输入第 " << i << " 个人的名字(" << i << "/30)" << endl;
		getline(cin, names[i - 1]);
		i++;
	}
}

// 向哈希表中插入数据
void insert(ListNode* hashtable, int posi, string data) {
	// hashtable 是哈希表， posi是要插入的位置，data是要插入的数据 
	cout << data << " - INSERT" << endl;
	if (hashtable[posi].next == NULL) {
		hashtable[posi].next = new ListNode(data, NULL);
	} else {
		ListNode* temp = hashtable[posi].next;
		while (temp->next) temp = temp->next;
		temp->next = new  ListNode(data, NULL);
	}
}

// 计算哈希码
int hashCode(string str) {
	return str[0] % 27;
}

//在哈希表中查找指定字符串，成功返回1，否则返回0
int findInHashTable(string nameToFind) {
	ListNode* temp = nullptr;
	if (!(temp = hashTable[hashCode(nameToFind)].next)) return 0;
	while (temp) {
		if (temp->data == nameToFind) {
			return 1;
		}
		temp = temp->next;
	}
	return 0;
}

int main() {
	int choose = 0;
	cout << "请选择构建姓名哈希表的方式：" << endl
		<< "1. 直接输入" << endl
		<< "2. 从文件读取" << endl
		<< "请输入选项" << endl;
	cin >> choose;
	switch (choose) {
	case 1: getchar();  enterName(); break;
	case 2: readFile(); break;
	default:
		break;
	}
	
	// 插入
	for (int i = 0; i < 30; i++) {
		cout << i + 1 << " ";
		insert(hashTable, hashCode(names[i]), names[i]);
	}
	
	cout << "数据插入成功\n哈希表构建成功" << endl;

	int find = 0;
	do {
		cout << "继续查找(1/0) ？" << endl;
		cin >> find;
		if (find == 1) {
			cout << "输入查找的姓名拼音" << endl;
			string nameToFind;
			cin >> nameToFind;
			// 开始在哈希表中查找
			if (findInHashTable(nameToFind))
				cout << "查找成功" << endl;
			else cout << "查找失败" << endl;
		} else break;
	} while (1);

	return 0;
}