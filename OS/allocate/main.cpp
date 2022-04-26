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

// 最先适应算法
#define FIRST_FIT_ALGORITHM 1
// 最优适应算法
#define BEST_FIT_ALGORITHM 2
// 内存分配
#define MEMORY_ALLOCATE 1
// 内存回收
#define MEMORY_RECOVERY 2

// 空闲区 地址升序排序
#define FREE_ADD_ASC_SORT 1
// 空闲区内存空间大小升序排序
#define FREE_MEM_ASC_SORT 2
// 分配区 地址升序排序
#define ALLO_ADD_ASC_SORT 3

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
char operation = 0;

// 使用的算法
char recoverAlgorithm = 0;

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
/// 
/// *provided: 
///		release_add 释放区域的首地址
///		release_size 要释放区域的大小
///		assign 已经使用的空间, 这个空间应该以[地址升序]排列, 
///			   以便要释放的区域跨越两个节点的时候能够顺利处理
///		head1 空闲队列的指针
/// 

int check() {

	// assign 应该以地址升序的方式排列, 
	// 以便要释放的区域跨越两个节点的时候能够顺利处理
	sortList(ALLO_ADD_ASC_SORT);

	// 检查
	Node* temp = assign;
	while (temp) {
		if (release_add >= temp->adr && release_add < temp->adr + temp->size) {
			// 释放区地址在当前块内
			if (release_add + release_size <= temp->size) {
				// 没有跨越块(节点)
				return CHECK_STATUS_INBLOCK;
			}
			else {
				// 跨越块(节点)
				return CHECK_STATUS_CROSS;
			}
		}
		temp = temp->next;
	}

	// 如果在此之前都没有返回, 就是目标地址未被分配, 这时候直接返回访问冲突
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
/// *provided:
///		allocate_size 需要分配的大小
int assignment1() {

	// 指向空闲分区的首地址
	Node* temp = head1;

	// 已经分配存储空间的标志
	int flag = 0;

	// 第一个空闲空间就满足
	if (temp->size >= allocate) {
		// 新空间增加节点
		if (!assign) {
			// assign 为空
			assign = new Node(0, allocate , NULL);
		}
		else {
			Node* temp = assign;
			// 移动到表的最后
			while (temp->next) temp = temp->next;
			// 为进程分配空间
			temp->next = new Node(head1->adr, allocate, NULL);
		}
		// 更新第一个空闲空间
		head1->adr = head1->adr + allocate;
		head1->size = head1->size - allocate;
		// 标志已经分配了空间
		return ALLOCATE_SUCCESS;
	}

	// 非第一个空间满足, 需要保留前一个指针
	// 
	while ((!flag) && temp->next) {

		/// 当前节点的存储区大小大于需要的存储区的大小
		/// 把当前节点的存储区域分成两部分
		/// 一部分是 [temp.addr, temp.addr + allocate_size)
		/// 即 [temp.addr, temp.addr + allocate_size - 1], 用来存储 allocate 区域
		/// 另一部分是 [temp.addr + allocate_size, temp.addr + temp.size]
		if (temp->size >= allocate) {

			// 开辟新节点
			Node* newBlock = new Node();



		}  
		temp = temp->next;
	}

	return 0;
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



	return 0;
}

/// First Fit Algorithm 回收算法
/// 
/// *provided:
///		assign 指向已经分配的内存node的指针
///		head1 空闲区队列的首指针
///		
/// 
int acceptment() {



	return 0;
}



// 打印空闲区队列
int print() {

	// 空闲区队列的大小
	Node* temp = head1;

	printf("空闲区队列\n\n\n编号\t首址\t终址\t大小\n");

	int i = 0;
	while (temp) {
		printf("%-5d\t%-5d\t%-5d\t%-5d\n", 
			i++, temp->adr, temp->adr + temp->size - 1, temp->size);
		temp = temp->next;
	}

	// debug 

	printf("分配区 队列\n\n\n编号\t首址\t终址\t大小\n");

	temp = assign;
	i = 0;
	while (temp) {
		printf("%-5d\t%-5d\t%-5d\t%-5d\n",
			i++, temp->adr, temp->adr + temp->size - 1, temp->size);
		temp = temp->next;
	}

	return 0;
}

int main() {

	// 初始化
	head1 = new Node(0, 32767);

	allocate = 500;
	assignment1();
	assignment1();
	assignment1();
	print();

	//cout << "回收算法: \n1. First Fit\n2. Best Fit\n";
	//cin >> recoverAlgorithm;

	//cout << "分配 or 回收: 1. 分配\n2. 回收\n";
	//cin >> operation;

	//while (1) {



	//}
	
	return 0;
}