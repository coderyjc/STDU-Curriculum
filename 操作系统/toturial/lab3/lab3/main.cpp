#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define ALGORITHM_FIFO 1
#define ALGORITHM_LRU 2

// ָ���ַ�ĸ���Ϊ30
int IC = 50;
// ҳ����ĸ���
int pageCount = 5;
// ҳ��
int* pageTable = new int[pageCount];
// ҳ��Ĵ�С��ʼΪ1K
int pageSize = 1024;
// ָ���ַ����
int* addresses = new int[IC];
// ����Ĵ�С
int bufferSize = 3;
// �����
vector<int> pageBuffer(bufferSize);
// �����¼�� 30 * 3
vector<vector<int>> bufferRecord;
// �Ƚ��ȳ��Ķ���
queue<int> pageQ;
// LRU�ķ��ʴ���
vector<int> LRU_flag(pageCount, 0);

/// ����ָ���ַ��, ��ʼ��ҳ��
/// ������Ҫ���ʵĵ�ַ˳��
/// 50%��ָ����˳��ִ�е�, 25%�Ǿ��ȷ�ɢ��ǰ��, 25%���ȷ�ɢ�ں���
void init() {
	pageBuffer.clear();
	bufferRecord.clear();
	
	// ��ʼ�������
	static unsigned int seq = 0;
	srand(time(0) + (seq++));
	int base = 0;
	// ����ָ����
	for (int i = 0; i < IC; i++) {
		if (i < IC / 4) {
		// �ֲ���ǰ���
			addresses[i] = rand() % (pageCount * pageSize / 4);
		}
		else if (i < IC * 3 / 4) {
			// �ֲ����м��, ˳��ִ��
			addresses[i++] = pageCount * pageSize / 4 + rand() % (pageCount * pageSize / 2);
			for (; i < IC * 3 / 4; i++) {
				addresses[i] = addresses[i - 1] + 1;
			}
			i--; // 15��ʱ���һ��
			continue;
		}
		else {
		// �ֲ��ں����
			addresses[i] = pageCount * pageSize * 3 / 4 + rand() % (pageCount * pageSize / 4);
		}
	}
	// ��ʼ��ҳ��
	for (int i = 0; i < pageCount; i++)
		pageTable[i] = i;
	// ����ҳ��˳��
	int position_1 = 0, position_2 = 0, temp;
	for (int i = 0; i < pageCount; i++)
	{
		position_1 = rand() % pageCount;
		position_2 = rand() % pageCount;
		temp = pageTable[position_1];
		pageTable[position_1] = pageTable[position_2];
		pageTable[position_2] = temp;
	}
}

// �߼���ַת��Ϊ�����ַ
int logical2physical(int logicalAddress) {
	return pageTable[logicalAddress / pageSize] * pageSize + (logicalAddress % pageSize);
}

/// �Ƚ��ȳ�
int FIFO(int pageNo) {
	for (int i = 0; i < pageBuffer.size(); i++) 
		if(pageBuffer[i] == pageQ.front()) pageBuffer[i] = pageNo;
	pageQ.pop();
	pageQ.push(pageNo);
	return 0;
}

// LRU�㷨��ʱ������
void LRUIncreasment(int page) {
	for (int i = 0; i < bufferSize; i++) {
		if (i == page) {
			LRU_flag[i] = 0;
		}
		else {
			LRU_flag[i]++;
		}
	}
}

// �������ʹ��
int LRU(int pageNo) {
	int maxIndex = -1, maxCount = 0;
	for (int i = 0; i < bufferSize; i++){
		if (LRU_flag[pageBuffer[i]] > maxCount) {
			maxIndex = i;
		}
	}
	pageBuffer[maxIndex] = pageNo;
	LRU_flag[pageBuffer[maxIndex]] = 1;
	return 0;
}

// �ж�ҳ���ǲ����ڻ�������
// para   : page
// return : 1 �ڻ�������
int inBuffer(int page) {
	for (int i = 0; i < pageBuffer.size(); i++) if (page == pageBuffer[i]) return 1;
	return 0;
}

// ���е�ַ����
// return 0 ȱҳ
// 1 ����
int addressAccess(int algorithm, int logicalAddress) {

	int page = logical2physical(logicalAddress) / pageSize;
	LRUIncreasment(page);
	// ���ʶ���
	pageQ.push(page);
	// ���
	if (inBuffer(page)) {
		bufferRecord.push_back(pageBuffer);
		return 1;
	}
	if (pageBuffer.size() < 3) {
		pageBuffer.push_back(page);
	}
	else {
		// �滻
		algorithm == ALGORITHM_FIFO ? FIFO(page) : LRU(page);
	}
	bufferRecord.push_back(pageBuffer);
	return 0;
}

// ��ӡҳ��
void printPageTable() {
	cout << "\n>-----Page Table-----<\nindex\tpage\n";
	for (int i = 0; i < pageCount; i++)
		cout << i << "\t" << pageTable[i] << endl;
}

// ��ӡ�߼���ַ �� �����ַ ��ӳ���ϵ
void printAddress() {
	cout << ">>-------logical <--> physical-------<<" << endl;
	for (int i = 0; i < IC; i++) {
		cout << addresses[i] << "<-->" << logical2physical(addresses[i]) << '\t';
		if ((i + 1) % 3 == 0) cout << endl;
	}
}

// ��ӡ���ʱ�
void printAccessTable() {
	// ��ͷ
	cout << "\n>-----���ʱ�-----<" << endl;
	//cout << "���\t";
	//for (int i = 0; i < IC; i++) {
	//	cout << i + 1 << "\t";
	//}
	//cout << endl;
	for (int i = 0; i < bufferSize; i++)
	{
		cout << i + 1 << "��\t";
		for (int j = 0; j < IC; j++)
		{
			if (bufferRecord[j].size() > i)
				cout << bufferRecord[j][i];
			cout << " \t";
		}
		cout << endl;
	}
}

// �Զ�����
void autoTest(int print = 1) {
	int count = 0;
	// ��ʼ����
	// FIFO
	for (int i = 0; i < IC; i++) {
		count += 1 - addressAccess(ALGORITHM_FIFO, addresses[i]);
	}
	// ��ӡ buffer list
	if (print) printAccessTable();
	// ��ӡ ȱҳ������	ȱҳ��
	cout << "\n[FIFO ȱҳ����: " << count << "]\t[ȱҳ��: " << count * 100 / IC << "%]";

	// ����ݴ�����
	pageBuffer.clear();
	bufferRecord.resize(0);
	pageQ = queue<int>();

	count = 0;

	// LRU
	for (int i = 0; i < IC; i++) {
		count += 1 - addressAccess(ALGORITHM_LRU, addresses[i]);
	}
	// ��ӡ buffer list
	if (print) printAccessTable();
	// ��ӡ ȱҳ������	ȱҳ��
	cout << "\n[ LRU ȱҳ����: " << count << "]\t[ȱҳ��: " << count * 100 / IC << "%]";
}

// �ֶ�����
void test() {
	int showTable = 0;

	cout << "Ҫ���ʵ�ָ���ַ�ĸ��� :>";
	cin >> IC;
	cout << "ҳ����ĸ��� :>";
	cin >> pageCount;
	cout << "ҳ���С :>";
	cin >> pageSize;
	cout << "��������С :>";
	cin >> bufferSize;
	cout << "�Ƿ���ʾ���ʱ�1/0 :>";
	cin >> showTable;

	delete[] addresses;
	addresses = new int[IC];
	for (int i = 0; i < IC; i++) {
		cout << "�����" << i + 1 << "����ַ :>";
		cin >> addresses[i];
	}
	delete[] pageTable;
	vector<int> LRU_flag(pageCount, 0);
	pageTable = new int[pageCount];
	// ��ʼ��ҳ��
	for (int i = 0; i < pageCount; i++)
		pageTable[i] = i;
	// ����ҳ��˳��
	int position_1 = 0, position_2 = 0, temp;
	for (int i = 0; i < pageCount; i++)
	{
		position_1 = rand() % pageCount;
		position_2 = rand() % pageCount;
		temp = pageTable[position_1];
		pageTable[position_1] = pageTable[position_2];
		pageTable[position_2] = temp;
	}
	bufferRecord = vector<vector<int>>();
	LRU_flag = vector<int>();

	autoTest();
}

int main() {

	int choose = -1;
	cout << "1.�Զ�������(����)\n2.�ֶ�����\n>";
	cin >> choose;
	if (1 == choose) {
		init();
		printAddress();
		printPageTable();
		autoTest();
	}
	else if (2 == choose) {
		test();
	}
	else if (3 == choose) {

	}

	delete[] addresses;
	delete[] pageTable;
	return 0;
}

/*
2
10
5
1024
3
1
4559
2264
4779
3298
4882
3689
4878
3355
3654
1013
3690
4297
4003
1877
1789
473
1938
1518
201
433
*/