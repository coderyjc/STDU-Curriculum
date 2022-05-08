
/*******************************************
*
* Author: Yan Jingcun
*
* DateTime: 2022-4-18 11:40
*
* Description: 存储管理动态分区分配及回收算法
*
*******************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

// 存储空间分配成功
#define ALLOCATE_SUCCESS 1
// 内存不足
#define OVERFLOW_ERROR -1

// 空闲区 地址升序排序
#define FREE_ADD_ASC_SORT 1
// 空闲区内存空间大小升序排序
#define FREE_MEM_ASC_SORT 2
// 分配区 地址升序排序
#define ALLO_ADD_ASC_SORT 3

// 最先适应算法
#define FIRST_FIT_ALGORITHM 1
// 最优适应算法
#define BEST_FIT_ALGORITHM 2
// 内存分配
#define MEMORY_ALLOCATE 1
// 内存回收
#define MEMORY_RECOVERY 2

// check 的结果 - 在块内
#define CHECK_STATUS_INBLOCK 1
// check 的结果 - 跨越块
#define CHECK_STATUS_CROSS 2
// check 的结果 - 访问越界(未找到地址)
#define CHECK_STATUS_VIOLATE -1

typedef struct Node {

	Node() {
		this->adr = 0;
		this->size = 0;
		this->next = NULL;
	}

	Node(int ad, int size, Node* n = NULL) {
		this->adr = ad;
		this->size = size;
		this->next = n;
	}

	// 分区首地址
	int adr;

	// 分区大小
	int size;

	// 指向下一个分区的指针
	Node* next;

}Node;

// 空闲区队列首指针
Node* head1 = NULL;

// 指向释放区 node 结构的指针
Node* back1 = NULL;

// 指向申请的内存分区 node 结构的指针
Node* assign = NULL;

// 用户申请的内存大小
int allocate = 0;

// 释放区的首地址
int release_add = 0;

// 释放区的大小
int release_size = 0;

// 进行的操作
int operation = 0;

// 分配的算法
int recoverAlgorithm = 0;



// 谓词 地址升序排序
bool compareAddressAsc(Node a, Node b) {
	return a.adr < b.adr;
}
// 谓词 内存升序排序
bool compareMemoryAsc(Node a, Node b) {
	return a.size < b.size;
}

/// 
/// 对链表进行排序
/// 
int sortList(int method) {

	Node* temp = NULL;
	vector<Node> v;
	if (FREE_ADD_ASC_SORT == method) {
		// 空闲区地址升序排序
		temp = head1;
		// 使用vector自带的排序
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
			temp = temp->next;
		}
		sort(v.begin(), v.end(), compareAddressAsc);
		// 排序之后再放回原来的链表
		temp = head1;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // 排序完成
	}
	else if (FREE_MEM_ASC_SORT == method) {
		// 空闲区内存空间大小升序排序
		temp = head1;
		// 使用vector自带的排序
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
			temp = temp->next;
		}
		sort(v.begin(), v.end(), compareMemoryAsc);
		// 排序之后再放回原来的链表
		temp = head1;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // 排序完成
	}
	else if (ALLO_ADD_ASC_SORT == method) {
		// 分配区地址升序排序
		temp = assign;
		// 使用vector自带的排序
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
			temp = temp->next;
		}
		sort(v.begin(), v.end(), compareAddressAsc);
		// 排序之后再放回原来的链表
		temp = assign;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // 排序完成
	}
	return 0;
}

/// check 检查释放块的有效性
///		也就是检查释放块的区域是不是在已经分配的块内
int check() {
	if (release_add < 0 || release_size < 0 || release_add + release_size > 32767) return CHECK_STATUS_VIOLATE;

	// 回收的首地址（包含）
	int begin_address = release_add;
	// 回收的尾地址（包含）
	int end_address = release_add + release_size - 1;
	// 在回收的时候，如果回收的空间跨没有跨越空白块，就是0，跨越空白块就是1，为1非法
	int flag = 0;

	// 检查
	Node* temp = assign;
	// 定位释放首地址所在的块
	while (temp) {
		if (begin_address >= temp->adr && begin_address < temp->adr + temp->size) break;
		temp = temp->next;
	}
	// 此时temp指向将要释放的区域所在的块
	// 在同一个块中
	if (temp && (end_address <= temp->adr + temp->size)) return CHECK_STATUS_INBLOCK;
	// 跨域了块，但是没有跨越空白块
	while (temp && temp->next) {
		if (temp->adr + temp->size == temp->next->adr) {
			// 两个块是相连的, 说明没有跨越空白块
			if (end_address >= temp->adr && end_address < temp->next->adr + temp->next->size) {
				// 尾地址在下一个块中
				return CHECK_STATUS_CROSS;
			}
		}
		else {
			// 两个块不相连，直接返回冲突
			return CHECK_STATUS_VIOLATE;
		}
		temp = temp->next;
	}

	// 直接返回冲突
	return CHECK_STATUS_VIOLATE;
}

/// 
/// First Fit Algorithm
/// 
/// *连接方式
///		空闲分区以 [地址] 递增的次序连接
/// *查找方式:
///		分配内存时, 从链首开始顺序查找
/// *条件:
///		找到大小能够满足的 [第一个] 空闲分区
int assignment1() {

	// 指向空闲分区的首地址
	Node* temp = head1;

	// 寻找大小正好满足的空间
	Node* satisfy = NULL;
	// 前一个块
	Node* preHead = head1;
	// 分配的起始地址
	int start_address = 0;
	while (temp && !satisfy) {
		if (temp->size >= allocate) {
			satisfy = temp;
			break;
		}
		preHead = temp;
		temp = temp->next;
	}
	// 如果没找到，satisfy就是空的
	// 如果找到了，satisfy就指向刚好满足的空闲空间节点
	if (satisfy) {
		// 记录满足的起始地址
		start_address = satisfy->adr;
		// 处理空闲链表
		if (allocate < satisfy->size) {
			// 块内分配，改变当前的节点
			satisfy->adr = satisfy->adr + allocate;
			satisfy->size = satisfy->size - allocate;
		}
		else {
			// 临界分配，完整分配一个块，需要删除当前满足的指定块
			if (satisfy == head1) {
				// 第一个块就是完全满足的块，直接改变head的指向
				head1 = head1->next;
				delete satisfy;
			}
			else {
				// 后续块是满足的块，删除并改变指向
				preHead->next = satisfy->next;
				delete satisfy;
			}
		}
		// 处理分配链表
		temp = assign;
		// 分配链表为空
		if (!assign) assign = new Node(0, allocate, NULL);
		else if (start_address + allocate <= temp->adr) {
			// 插入到第一个的前面
			assign = new Node(start_address, allocate, assign);
		}
		else {
			// 插入的后面的位置
			while (temp->next) {
				if (start_address >= temp->adr + temp->size && start_address + allocate <= temp->next->adr) break;
				temp = temp->next;
			}
			// 此时新分配的节点一定会插入到temp的后面
			temp->next = new Node(start_address, allocate, temp->next);
		}
		return ALLOCATE_SUCCESS;
	}
	else {
		return OVERFLOW_ERROR;
	}

	return ALLOCATE_SUCCESS;
}

/// Best Fit Algorithm
/// 
/// *连接方式
///		空闲分区以 [容量] 递增的次序连接
/// *查找方式:
///		分配内存时, 从链首开始顺序查找
/// *条件:
///		找到大小能够满足的 [最小的] 空闲分区
int assignment2() {

	Node* temp = head1;
	Node* preNode = NULL;
	Node* satisfy = NULL;
	Node* satisfy_pre = NULL;

	// 寻找能够找到的最小的空闲分区
	while (temp) {
		if (temp->size >= allocate) {
			if (satisfy && temp->size < satisfy->size) {
				// 当前分区满足且小于已有分区
				satisfy = temp;
				satisfy_pre = preNode;
			}
			else if (!satisfy) {
				satisfy = temp;
				satisfy_pre = preNode;
			}
		}
		// 当前分区不满足条件
		preNode = temp;
		temp = temp->next;
	}
	// 结束的时候，如果satisfy为空，就代表没找到合适的空间
	if (satisfy) {
		// 记录满足的起始地址
		int start_address = satisfy->adr;
		// 处理空闲链表
		if (allocate < satisfy->size) {
			// 块内分配，改变当前的节点
			satisfy->adr = satisfy->adr + allocate;
			satisfy->size = satisfy->size - allocate;
		}
		else {
			// 临界分配，完整分配一个块，需要删除当前满足的指定块
			if (satisfy == head1) {
				// 第一个块就是完全满足的块，直接改变head的指向
				head1 = head1->next;
				delete satisfy;
			}
			else {
				// 后续块是满足的块，删除并改变指向
				satisfy_pre->next = satisfy->next;
				delete satisfy;
			}
		}
		// 处理分配链表
		temp = assign;
		// 分配链表为空
		if (!assign) assign = new Node(0, allocate, NULL);
		else if (start_address + allocate <= temp->adr) {
			// 插入到第一个的前面
			assign = new Node(start_address, allocate, assign);
		}
		else {
			// 插入的后面的位置
			while (temp->next) {
				if (start_address >= temp->adr + temp->size && start_address + allocate <= temp->next->adr) break;
				temp = temp->next;
			}
			// 此时新分配的节点一定会插入到temp的后面
			temp->next = new Node(start_address, allocate, temp->next);
		}
		return ALLOCATE_SUCCESS;
	}
	else {
		return OVERFLOW_ERROR;
	}

	return 0;
}

/// 回收算法
/// 
/// *provided:
///		assign 指向已经分配的内存node的指针
///		head1 空闲区队列的首指针
/// 
int acceptment() {
	int checkStatus = check();

	// 地址访问冲突
	if (checkStatus == CHECK_STATUS_VIOLATE) {
		cout << "\t地址访问冲突，首地址:" << release_add <<
			"; 尾地址:" << release_add + release_size - 1
			<< "; 大小:" << release_size << endl;
		return -1;
	}

	// 块内回收
	if (checkStatus == CHECK_STATUS_INBLOCK) {
		// 分配链表多一个节点，或者不多
		Node* temp = assign;
		// 定位释放的首地址所在的块
		while (temp) {
			if (release_add >= temp->adr && release_add < temp->adr + temp->size) break;
			temp = temp->next;
		}
		// 创建 释放之后 靠后的节点
		Node* newNode = new Node(release_add + release_size, temp->adr + temp->size - release_add - release_size, temp->next);
		// 原来的节点变成释放之后考前的节点
		temp->size = release_add - temp->adr;
		temp->next = newNode;
		// 添加空闲节点
	}

	// 跨越块回收
	if (checkStatus == CHECK_STATUS_CROSS) {
		// 找到头尾所在的块以定位要释放的块
		// 回收的首地址（包含）
		int begin_address = release_add;
		// 回收的尾地址（包含）
		int end_address = release_add + release_size - 1;
		// 首地址所在块
		Node* preNode = NULL;
		// 尾地址所在块
		Node* nextNode = NULL;
		// 寻找首尾地址所在块
		Node* temp = assign;
		// 定位首位地址所在的块
		while (temp) {
			if (begin_address >= temp->adr && begin_address < temp->adr + temp->size) preNode = temp;
			if (end_address >= temp->adr && end_address < temp->adr + temp->size) nextNode = temp;
			temp = temp->next;
		} // 已经定位好首位地址所在的块
		// 在回收的时候顺便清理节点
		temp = preNode;
		while (temp->next != nextNode) {
			Node* t = temp->next;
			temp->next = t->next;
			delete t;
		}
		// 修改 preNode 和 nextNode 的信息, 保留两个节点
		preNode->size = begin_address - preNode->adr;
		nextNode->size = nextNode->adr + nextNode->size - end_address - 1;
		nextNode->adr = end_address + 1;
		// 如果有大小为0的已分配节点，会在下面删除
		// 添加空闲节点
	}

	// 空闲链表也多一个节点, 这个时候插入的节点一定至少正好位于空白处，亦或是刚好填充
	// 创建空闲块
	Node* newNode = new Node(release_add, release_size, NULL);
	// 在空闲链表中寻找位置插入
	Node* preNode = head1; // 前置指针（不为空）
	Node* temp = head1->next; // 后置指针（可能为空）
	if (temp == NULL) {
		// 这时候说明要添加的空闲区在第一个位置
		newNode->next = head1;
		head1 = newNode;
	}
	// 要添加的空闲区不在第一个位置，
	// 寻找合适位置，preNode指向合适位置的前一个节点，temp指向合适位置的后一个节点
	while (temp) {
		// 判断条件为新节点的尾地址小于temp的首地址
		if (newNode->adr >= preNode->adr + preNode->size && newNode->adr + newNode->size <= temp->adr) {
			// 插入节点
			preNode->next = newNode;
			newNode->next = temp;
		}
		temp = temp->next;
		preNode = preNode->next;
	}

	// 分配区域空白分配区域删除
	while (assign && assign->size == 0) {
		Node* dlt = assign;
		assign = assign->next;
		delete dlt;
	}
	if (assign) {
		temp = assign->next;
		preNode = assign;
		while (temp) {
			if (temp->size == 0) {
				preNode->next = temp->next;
			}
			preNode = temp;
			temp = temp->next;
		}
	}

	// 空闲链表空闲分区合并
	temp = head1;
	while (temp && temp->next) {
		if (temp->adr + temp->size == temp->next->adr) {
			// 当前空闲块扩容
			temp->size = temp->size + temp->next->size;
			Node* p = temp->next;
			temp->next = p->next;
			delete p;
		}
		temp = temp->next;
	}

	return 0;
}

// 打印空闲区队列
int print() {
	if (recoverAlgorithm == BEST_FIT_ALGORITHM) {
		sortList(FREE_MEM_ASC_SORT);
	}
	else {
		sortList(FREE_ADD_ASC_SORT);
	}

	// 空闲区队列的大小
	Node* temp = head1;

	printf("\n\t--------空闲区队列--------\n\t编号\t首址\t终址\t大小\n");

	int i = 0;
	while (temp) {
		printf("\t%-5d\t%-5d\t%-5d\t%-5d\n",
			i++, temp->adr, temp->adr + temp->size - 1, temp->size);
		temp = temp->next;
	}

	// debug 

	printf("\n\t--------分配区 队列--------\n\t编号\t首址\t终址\t大小\n");

	temp = assign;
	i = 0;
	while (temp) {
		printf("\t%-5d\t%-5d\t%-5d\t%-5d\n",
			i++, temp->adr, temp->adr + temp->size - 1, temp->size);
		temp = temp->next;
	}

	return 0;
}

int main() {

	// 初始化
	head1 = new Node(0, 32767);
	// 程序状态
	int status;

	while (1) {

		cout << "\n\t分配算法: 1. First Fit. 2. Best Fit 其他.退出 --> ";
		cin >> recoverAlgorithm;
		cout << "\t分配 or 回收 1. 分配. 2. 回收 --> ";
		cin >> operation;
		if (operation == 1) {
			// 分配
			cout << "\t申请区的大小--->";
			cin >> allocate;
			if (recoverAlgorithm == FIRST_FIT_ALGORITHM) {
				status = assignment1();
			}
			else if (recoverAlgorithm == BEST_FIT_ALGORITHM) {
				status = assignment2();
			}
		}
		else if (operation == 2) {
			// 回收
			cout << "\t释放区域的首地址和大小 --->";
			cin >> release_add >> release_size;
			status = acceptment();
		}
		if (status == OVERFLOW_ERROR) {
			cout << "\t！！！分配失败！！！" << endl;
		}
		else {
			print();
		}
	}

	return 0;
}