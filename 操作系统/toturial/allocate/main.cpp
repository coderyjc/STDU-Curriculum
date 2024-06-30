
/*******************************************
*
* Author: Yan Jingcun
*
* DateTime: 2022-4-18 11:40
*
* Description: �洢����̬�������估�����㷨
*
*******************************************/

#include<cstdio>
#include<vector>
#include<algorithm>
#include<iostream>

using namespace std;

// �洢�ռ����ɹ�
#define ALLOCATE_SUCCESS 1
// �ڴ治��
#define OVERFLOW_ERROR -1

// ������ ��ַ��������
#define FREE_ADD_ASC_SORT 1
// �������ڴ�ռ��С��������
#define FREE_MEM_ASC_SORT 2
// ������ ��ַ��������
#define ALLO_ADD_ASC_SORT 3

// ������Ӧ�㷨
#define FIRST_FIT_ALGORITHM 1
// ������Ӧ�㷨
#define BEST_FIT_ALGORITHM 2
// �ڴ����
#define MEMORY_ALLOCATE 1
// �ڴ����
#define MEMORY_RECOVERY 2

// check �Ľ�� - �ڿ���
#define CHECK_STATUS_INBLOCK 1
// check �Ľ�� - ��Խ��
#define CHECK_STATUS_CROSS 2
// check �Ľ�� - ����Խ��(δ�ҵ���ַ)
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

	// �����׵�ַ
	int adr;

	// ������С
	int size;

	// ָ����һ��������ָ��
	Node* next;

}Node;

// ������������ָ��
Node* head1 = NULL;

// ָ���ͷ��� node �ṹ��ָ��
Node* back1 = NULL;

// ָ��������ڴ���� node �ṹ��ָ��
Node* assign = NULL;

// �û�������ڴ��С
int allocate = 0;

// �ͷ������׵�ַ
int release_add = 0;

// �ͷ����Ĵ�С
int release_size = 0;

// ���еĲ���
int operation = 0;

// ������㷨
int recoverAlgorithm = 0;



// ν�� ��ַ��������
bool compareAddressAsc(Node a, Node b) {
	return a.adr < b.adr;
}
// ν�� �ڴ���������
bool compareMemoryAsc(Node a, Node b) {
	return a.size < b.size;
}

/// 
/// �������������
/// 
int sortList(int method) {

	Node* temp = NULL;
	vector<Node> v;
	if (FREE_ADD_ASC_SORT == method) {
		// ��������ַ��������
		temp = head1;
		// ʹ��vector�Դ�������
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
			temp = temp->next;
		}
		sort(v.begin(), v.end(), compareAddressAsc);
		// ����֮���ٷŻ�ԭ��������
		temp = head1;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // �������
	}
	else if (FREE_MEM_ASC_SORT == method) {
		// �������ڴ�ռ��С��������
		temp = head1;
		// ʹ��vector�Դ�������
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
			temp = temp->next;
		}
		sort(v.begin(), v.end(), compareMemoryAsc);
		// ����֮���ٷŻ�ԭ��������
		temp = head1;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // �������
	}
	else if (ALLO_ADD_ASC_SORT == method) {
		// ��������ַ��������
		temp = assign;
		// ʹ��vector�Դ�������
		while (temp) {
			v.push_back(Node(temp->adr, temp->size, temp->next));
			temp = temp->next;
		}
		sort(v.begin(), v.end(), compareAddressAsc);
		// ����֮���ٷŻ�ԭ��������
		temp = assign;
		for (int i = 0; temp; i++) {
			temp->adr = v[i].adr;
			temp->size = v[i].size;
			temp->next = v[i].next;
			temp = temp->next;
		} // �������
	}
	return 0;
}

/// check ����ͷſ����Ч��
///		Ҳ���Ǽ���ͷſ�������ǲ������Ѿ�����Ŀ���
int check() {
	if (release_add < 0 || release_size < 0 || release_add + release_size > 32767) return CHECK_STATUS_VIOLATE;

	// ���յ��׵�ַ��������
	int begin_address = release_add;
	// ���յ�β��ַ��������
	int end_address = release_add + release_size - 1;
	// �ڻ��յ�ʱ��������յĿռ��û�п�Խ�հ׿飬����0����Խ�հ׿����1��Ϊ1�Ƿ�
	int flag = 0;

	// ���
	Node* temp = assign;
	// ��λ�ͷ��׵�ַ���ڵĿ�
	while (temp) {
		if (begin_address >= temp->adr && begin_address < temp->adr + temp->size) break;
		temp = temp->next;
	}
	// ��ʱtempָ��Ҫ�ͷŵ��������ڵĿ�
	// ��ͬһ������
	if (temp && (end_address <= temp->adr + temp->size)) return CHECK_STATUS_INBLOCK;
	// �����˿飬����û�п�Խ�հ׿�
	while (temp && temp->next) {
		if (temp->adr + temp->size == temp->next->adr) {
			// ��������������, ˵��û�п�Խ�հ׿�
			if (end_address >= temp->adr && end_address < temp->next->adr + temp->next->size) {
				// β��ַ����һ������
				return CHECK_STATUS_CROSS;
			}
		}
		else {
			// �����鲻������ֱ�ӷ��س�ͻ
			return CHECK_STATUS_VIOLATE;
		}
		temp = temp->next;
	}

	// ֱ�ӷ��س�ͻ
	return CHECK_STATUS_VIOLATE;
}

/// 
/// First Fit Algorithm
/// 
/// *���ӷ�ʽ
///		���з����� [��ַ] �����Ĵ�������
/// *���ҷ�ʽ:
///		�����ڴ�ʱ, �����׿�ʼ˳�����
/// *����:
///		�ҵ���С�ܹ������ [��һ��] ���з���
int assignment1() {

	// ָ����з������׵�ַ
	Node* temp = head1;

	// Ѱ�Ҵ�С��������Ŀռ�
	Node* satisfy = NULL;
	// ǰһ����
	Node* preHead = head1;
	// �������ʼ��ַ
	int start_address = 0;
	while (temp && !satisfy) {
		if (temp->size >= allocate) {
			satisfy = temp;
			break;
		}
		preHead = temp;
		temp = temp->next;
	}
	// ���û�ҵ���satisfy���ǿյ�
	// ����ҵ��ˣ�satisfy��ָ��պ�����Ŀ��пռ�ڵ�
	if (satisfy) {
		// ��¼�������ʼ��ַ
		start_address = satisfy->adr;
		// �����������
		if (allocate < satisfy->size) {
			// ���ڷ��䣬�ı䵱ǰ�Ľڵ�
			satisfy->adr = satisfy->adr + allocate;
			satisfy->size = satisfy->size - allocate;
		}
		else {
			// �ٽ���䣬��������һ���飬��Ҫɾ����ǰ�����ָ����
			if (satisfy == head1) {
				// ��һ���������ȫ����Ŀ飬ֱ�Ӹı�head��ָ��
				head1 = head1->next;
				delete satisfy;
			}
			else {
				// ������������Ŀ飬ɾ�����ı�ָ��
				preHead->next = satisfy->next;
				delete satisfy;
			}
		}
		// �����������
		temp = assign;
		// ��������Ϊ��
		if (!assign) assign = new Node(0, allocate, NULL);
		else if (start_address + allocate <= temp->adr) {
			// ���뵽��һ����ǰ��
			assign = new Node(start_address, allocate, assign);
		}
		else {
			// ����ĺ����λ��
			while (temp->next) {
				if (start_address >= temp->adr + temp->size && start_address + allocate <= temp->next->adr) break;
				temp = temp->next;
			}
			// ��ʱ�·���Ľڵ�һ������뵽temp�ĺ���
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
/// *���ӷ�ʽ
///		���з����� [����] �����Ĵ�������
/// *���ҷ�ʽ:
///		�����ڴ�ʱ, �����׿�ʼ˳�����
/// *����:
///		�ҵ���С�ܹ������ [��С��] ���з���
int assignment2() {

	Node* temp = head1;
	Node* preNode = NULL;
	Node* satisfy = NULL;
	Node* satisfy_pre = NULL;

	// Ѱ���ܹ��ҵ�����С�Ŀ��з���
	while (temp) {
		if (temp->size >= allocate) {
			if (satisfy && temp->size < satisfy->size) {
				// ��ǰ����������С�����з���
				satisfy = temp;
				satisfy_pre = preNode;
			}
			else if (!satisfy) {
				satisfy = temp;
				satisfy_pre = preNode;
			}
		}
		// ��ǰ��������������
		preNode = temp;
		temp = temp->next;
	}
	// ������ʱ�����satisfyΪ�գ��ʹ���û�ҵ����ʵĿռ�
	if (satisfy) {
		// ��¼�������ʼ��ַ
		int start_address = satisfy->adr;
		// �����������
		if (allocate < satisfy->size) {
			// ���ڷ��䣬�ı䵱ǰ�Ľڵ�
			satisfy->adr = satisfy->adr + allocate;
			satisfy->size = satisfy->size - allocate;
		}
		else {
			// �ٽ���䣬��������һ���飬��Ҫɾ����ǰ�����ָ����
			if (satisfy == head1) {
				// ��һ���������ȫ����Ŀ飬ֱ�Ӹı�head��ָ��
				head1 = head1->next;
				delete satisfy;
			}
			else {
				// ������������Ŀ飬ɾ�����ı�ָ��
				satisfy_pre->next = satisfy->next;
				delete satisfy;
			}
		}
		// �����������
		temp = assign;
		// ��������Ϊ��
		if (!assign) assign = new Node(0, allocate, NULL);
		else if (start_address + allocate <= temp->adr) {
			// ���뵽��һ����ǰ��
			assign = new Node(start_address, allocate, assign);
		}
		else {
			// ����ĺ����λ��
			while (temp->next) {
				if (start_address >= temp->adr + temp->size && start_address + allocate <= temp->next->adr) break;
				temp = temp->next;
			}
			// ��ʱ�·���Ľڵ�һ������뵽temp�ĺ���
			temp->next = new Node(start_address, allocate, temp->next);
		}
		return ALLOCATE_SUCCESS;
	}
	else {
		return OVERFLOW_ERROR;
	}

	return 0;
}

/// �����㷨
/// 
/// *provided:
///		assign ָ���Ѿ�������ڴ�node��ָ��
///		head1 ���������е���ָ��
/// 
int acceptment() {
	int checkStatus = check();

	// ��ַ���ʳ�ͻ
	if (checkStatus == CHECK_STATUS_VIOLATE) {
		cout << "\t��ַ���ʳ�ͻ���׵�ַ:" << release_add <<
			"; β��ַ:" << release_add + release_size - 1
			<< "; ��С:" << release_size << endl;
		return -1;
	}

	// ���ڻ���
	if (checkStatus == CHECK_STATUS_INBLOCK) {
		// ���������һ���ڵ㣬���߲���
		Node* temp = assign;
		// ��λ�ͷŵ��׵�ַ���ڵĿ�
		while (temp) {
			if (release_add >= temp->adr && release_add < temp->adr + temp->size) break;
			temp = temp->next;
		}
		// ���� �ͷ�֮�� ����Ľڵ�
		Node* newNode = new Node(release_add + release_size, temp->adr + temp->size - release_add - release_size, temp->next);
		// ԭ���Ľڵ����ͷ�֮��ǰ�Ľڵ�
		temp->size = release_add - temp->adr;
		temp->next = newNode;
		// ��ӿ��нڵ�
	}

	// ��Խ�����
	if (checkStatus == CHECK_STATUS_CROSS) {
		// �ҵ�ͷβ���ڵĿ��Զ�λҪ�ͷŵĿ�
		// ���յ��׵�ַ��������
		int begin_address = release_add;
		// ���յ�β��ַ��������
		int end_address = release_add + release_size - 1;
		// �׵�ַ���ڿ�
		Node* preNode = NULL;
		// β��ַ���ڿ�
		Node* nextNode = NULL;
		// Ѱ����β��ַ���ڿ�
		Node* temp = assign;
		// ��λ��λ��ַ���ڵĿ�
		while (temp) {
			if (begin_address >= temp->adr && begin_address < temp->adr + temp->size) preNode = temp;
			if (end_address >= temp->adr && end_address < temp->adr + temp->size) nextNode = temp;
			temp = temp->next;
		} // �Ѿ���λ����λ��ַ���ڵĿ�
		// �ڻ��յ�ʱ��˳������ڵ�
		temp = preNode;
		while (temp->next != nextNode) {
			Node* t = temp->next;
			temp->next = t->next;
			delete t;
		}
		// �޸� preNode �� nextNode ����Ϣ, ���������ڵ�
		preNode->size = begin_address - preNode->adr;
		nextNode->size = nextNode->adr + nextNode->size - end_address - 1;
		nextNode->adr = end_address + 1;
		// ����д�СΪ0���ѷ���ڵ㣬��������ɾ��
		// ��ӿ��нڵ�
	}

	// ��������Ҳ��һ���ڵ�, ���ʱ�����Ľڵ�һ����������λ�ڿհ״�������Ǹպ����
	// �������п�
	Node* newNode = new Node(release_add, release_size, NULL);
	// �ڿ���������Ѱ��λ�ò���
	Node* preNode = head1; // ǰ��ָ�루��Ϊ�գ�
	Node* temp = head1->next; // ����ָ�루����Ϊ�գ�
	if (temp == NULL) {
		// ��ʱ��˵��Ҫ��ӵĿ������ڵ�һ��λ��
		newNode->next = head1;
		head1 = newNode;
	}
	// Ҫ��ӵĿ��������ڵ�һ��λ�ã�
	// Ѱ�Һ���λ�ã�preNodeָ�����λ�õ�ǰһ���ڵ㣬tempָ�����λ�õĺ�һ���ڵ�
	while (temp) {
		// �ж�����Ϊ�½ڵ��β��ַС��temp���׵�ַ
		if (newNode->adr >= preNode->adr + preNode->size && newNode->adr + newNode->size <= temp->adr) {
			// ����ڵ�
			preNode->next = newNode;
			newNode->next = temp;
		}
		temp = temp->next;
		preNode = preNode->next;
	}

	// ��������հ׷�������ɾ��
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

	// ����������з����ϲ�
	temp = head1;
	while (temp && temp->next) {
		if (temp->adr + temp->size == temp->next->adr) {
			// ��ǰ���п�����
			temp->size = temp->size + temp->next->size;
			Node* p = temp->next;
			temp->next = p->next;
			delete p;
		}
		temp = temp->next;
	}

	return 0;
}

// ��ӡ����������
int print() {
	if (recoverAlgorithm == BEST_FIT_ALGORITHM) {
		sortList(FREE_MEM_ASC_SORT);
	}
	else {
		sortList(FREE_ADD_ASC_SORT);
	}

	// ���������еĴ�С
	Node* temp = head1;

	printf("\n\t--------����������--------\n\t���\t��ַ\t��ַ\t��С\n");

	int i = 0;
	while (temp) {
		printf("\t%-5d\t%-5d\t%-5d\t%-5d\n",
			i++, temp->adr, temp->adr + temp->size - 1, temp->size);
		temp = temp->next;
	}

	// debug 

	printf("\n\t--------������ ����--------\n\t���\t��ַ\t��ַ\t��С\n");

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

	// ��ʼ��
	head1 = new Node(0, 32767);
	// ����״̬
	int status;

	while (1) {

		cout << "\n\t�����㷨: 1. First Fit. 2. Best Fit ����.�˳� --> ";
		cin >> recoverAlgorithm;
		cout << "\t���� or ���� 1. ����. 2. ���� --> ";
		cin >> operation;
		if (operation == 1) {
			// ����
			cout << "\t�������Ĵ�С--->";
			cin >> allocate;
			if (recoverAlgorithm == FIRST_FIT_ALGORITHM) {
				status = assignment1();
			}
			else if (recoverAlgorithm == BEST_FIT_ALGORITHM) {
				status = assignment2();
			}
		}
		else if (operation == 2) {
			// ����
			cout << "\t�ͷ�������׵�ַ�ʹ�С --->";
			cin >> release_add >> release_size;
			status = acceptment();
		}
		if (status == OVERFLOW_ERROR) {
			cout << "\t����������ʧ�ܣ�����" << endl;
		}
		else {
			print();
		}
	}

	return 0;
}