#include "HashTableApp.h"
#include<fstream>
#include<string>

HashTableApp::HashTableApp() {
}

// 从文件中读取名字	
void HashTableApp::readFile() {
	string path;
	cout << "请输入文件的路径 : ";
	cin >> path;
	ifstream ifs(path, ios::in);
	if (!ifs) {
		cout << "----------------\n警告：\n\n文件路径输入错误...\n----------------" << endl;
		system("pause");
		system("cls");
		return;
	}
	for (int i = 0; i < 30; i++) {
		getline(ifs, names[i]);
	}
	ifs.close();

	for (int i = 0; i < 30; i++) {
		cout << i + 1 << " ";
		insert(hashCode(names[i]), names[i]);
	}

	cout << "----------------\n提示：\n\n哈希表构建成功\n----------------" << endl;
	system("pause");
	system("cls");
}

// 手动输入名字
void HashTableApp::enterName() {
	// 输入名字
	int i = 1;
	while (i <= 30) {
		cout << "请输入第 " << i << " 个人的名字(" << i << "/30)" << endl;
		getline(cin, names[i - 1]);
		i++;
	}

	for (int i = 0; i < 30; i++) {
		cout << i + 1 << " ";
		insert(hashCode(names[i]), names[i]);
	}

	cout << "--------------\n提示：\n\n哈希表构建成功\n--------------" << endl;
}

// 向哈希表中插入数据
void HashTableApp::insert(int posi, string data) {
	// hashtable 是哈希表， posi是要插入的位置，data是要插入的数据 
	cout << data << " - INSERT" << endl;
	if (this->hashTable[posi].next == NULL) {
		this->hashTable[posi].next = new ListNode(data, NULL);
	} else {
		ListNode* temp = this->hashTable[posi].next;
		while (temp->next) temp = temp->next;
		temp->next = new  ListNode(data, NULL);
	}
}

void HashTableApp::layout() {
	cout << "----------\n哈希表结构\n----------" << endl;
	ListNode* temp = NULL;
	for (int i = 0; i < 27; i++) {
		if(i < 10) cout << " ";
		cout << i << " : ";
		temp = this->hashTable[i].next;
		if (temp) {
			// temp 不为空，也就是说这个节点上有值
			// 遍历这个结点的后继
			while (temp) {
				cout << temp->data << " -> ";
				temp = temp->next;
			}
		} 
		// temp 为空或者有值的情况下遍历到了最后
		cout << "null " << endl;
	}
	system("pause");
	system("cls");
}

void HashTableApp::find() {
	cout << "输入查找的姓名拼音" << endl;
	string nameToFind;
	cin >> nameToFind;
	// 开始在哈希表中查找
	int success = 0;
	ListNode* temp = hashTable[hashCode(nameToFind)].next;
	while (temp) {
		if (temp->data == nameToFind) {
			success = 1;
		}
		temp = temp->next;
	}

	if (success)
		cout << "--------\n查找成功\n--------" << endl;
	else cout << "--------\n查找失败\n--------" << endl;
	system("pause");
	system("cls");
}

void HashTableApp::mainLoop() {
	int choose = 0;
	do {
		cout << "-------------------" << endl
			<< "基于hashtable的查找" << endl
			<< "-------------------" << endl
			<< "1.基于文件读取关键字" << endl
			<< "2.手动输入关键字" << endl
			<< "3.查看哈希表" << endl
			<< "4.查找关键字" << endl
			<< "0.退出" << endl
			<< "-------------------" << endl
			<< "请输入：";
		cin >> choose;
		switch (choose) {
		case 1: this->readFile(); break;
		case 2: getchar(); this->enterName(); break;
		case 3: this->layout(); break;
		case 4: this->find(); break;
		default: return;
		}
	} while (1);
}

int HashTableApp::hashCode(string str) {
	return str[0] % 27;
}