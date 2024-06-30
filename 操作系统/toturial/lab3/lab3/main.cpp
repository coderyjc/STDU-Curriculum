#include<iostream>
#include<vector>
#include<queue>

using namespace std;

#define ALGORITHM_FIFO 1
#define ALGORITHM_LRU 2

// 指令地址的个数为30
int IC = 50;
// 页表项的个数
int pageCount = 5;
// 页表
int* pageTable = new int[pageCount];
// 页面的大小初始为1K
int pageSize = 1024;
// 指令地址序列
int* addresses = new int[IC];
// 缓存的大小
int bufferSize = 3;
// 缓存表
vector<int> pageBuffer(bufferSize);
// 缓存记录表 30 * 3
vector<vector<int>> bufferRecord;
// 先进先出的队列
queue<int> pageQ;
// LRU的访问次数
vector<int> LRU_flag(pageCount, 0);

/// 产生指令地址流, 初始化页表
/// 产生需要访问的地址顺序
/// 50%的指令是顺序执行的, 25%是均匀分散在前边, 25%均匀分散在后面
void init() {
	pageBuffer.clear();
	bufferRecord.clear();
	
	// 初始化随机数
	static unsigned int seq = 0;
	srand(time(0) + (seq++));
	int base = 0;
	// 产生指令流
	for (int i = 0; i < IC; i++) {
		if (i < IC / 4) {
		// 分布在前面的
			addresses[i] = rand() % (pageCount * pageSize / 4);
		}
		else if (i < IC * 3 / 4) {
			// 分布在中间的, 顺序执行
			addresses[i++] = pageCount * pageSize / 4 + rand() % (pageCount * pageSize / 2);
			for (; i < IC * 3 / 4; i++) {
				addresses[i] = addresses[i - 1] + 1;
			}
			i--; // 15的时候减一下
			continue;
		}
		else {
		// 分布在后面的
			addresses[i] = pageCount * pageSize * 3 / 4 + rand() % (pageCount * pageSize / 4);
		}
	}
	// 初始化页表
	for (int i = 0; i < pageCount; i++)
		pageTable[i] = i;
	// 打乱页表顺序
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

// 逻辑地址转换为物理地址
int logical2physical(int logicalAddress) {
	return pageTable[logicalAddress / pageSize] * pageSize + (logicalAddress % pageSize);
}

/// 先进先出
int FIFO(int pageNo) {
	for (int i = 0; i < pageBuffer.size(); i++) 
		if(pageBuffer[i] == pageQ.front()) pageBuffer[i] = pageNo;
	pageQ.pop();
	pageQ.push(pageNo);
	return 0;
}

// LRU算法的时间增加
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

// 最近最少使用
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

// 判断页号是不是在缓存区中
// para   : page
// return : 1 在缓存区中
int inBuffer(int page) {
	for (int i = 0; i < pageBuffer.size(); i++) if (page == pageBuffer[i]) return 1;
	return 0;
}

// 进行地址访问
// return 0 缺页
// 1 命中
int addressAccess(int algorithm, int logicalAddress) {

	int page = logical2physical(logicalAddress) / pageSize;
	LRUIncreasment(page);
	// 访问队列
	pageQ.push(page);
	// 查表
	if (inBuffer(page)) {
		bufferRecord.push_back(pageBuffer);
		return 1;
	}
	if (pageBuffer.size() < 3) {
		pageBuffer.push_back(page);
	}
	else {
		// 替换
		algorithm == ALGORITHM_FIFO ? FIFO(page) : LRU(page);
	}
	bufferRecord.push_back(pageBuffer);
	return 0;
}

// 打印页表
void printPageTable() {
	cout << "\n>-----Page Table-----<\nindex\tpage\n";
	for (int i = 0; i < pageCount; i++)
		cout << i << "\t" << pageTable[i] << endl;
}

// 打印逻辑地址 和 物理地址 的映射关系
void printAddress() {
	cout << ">>-------logical <--> physical-------<<" << endl;
	for (int i = 0; i < IC; i++) {
		cout << addresses[i] << "<-->" << logical2physical(addresses[i]) << '\t';
		if ((i + 1) % 3 == 0) cout << endl;
	}
}

// 打印访问表
void printAccessTable() {
	// 表头
	cout << "\n>-----访问表-----<" << endl;
	//cout << "序号\t";
	//for (int i = 0; i < IC; i++) {
	//	cout << i + 1 << "\t";
	//}
	//cout << endl;
	for (int i = 0; i < bufferSize; i++)
	{
		cout << i + 1 << "号\t";
		for (int j = 0; j < IC; j++)
		{
			if (bufferRecord[j].size() > i)
				cout << bufferRecord[j][i];
			cout << " \t";
		}
		cout << endl;
	}
}

// 自动测试
void autoTest(int print = 1) {
	int count = 0;
	// 开始测试
	// FIFO
	for (int i = 0; i < IC; i++) {
		count += 1 - addressAccess(ALGORITHM_FIFO, addresses[i]);
	}
	// 打印 buffer list
	if (print) printAccessTable();
	// 打印 缺页次数和	缺页率
	cout << "\n[FIFO 缺页次数: " << count << "]\t[缺页率: " << count * 100 / IC << "%]";

	// 清空暂存数据
	pageBuffer.clear();
	bufferRecord.resize(0);
	pageQ = queue<int>();

	count = 0;

	// LRU
	for (int i = 0; i < IC; i++) {
		count += 1 - addressAccess(ALGORITHM_LRU, addresses[i]);
	}
	// 打印 buffer list
	if (print) printAccessTable();
	// 打印 缺页次数和	缺页率
	cout << "\n[ LRU 缺页次数: " << count << "]\t[缺页率: " << count * 100 / IC << "%]";
}

// 手动测试
void test() {
	int showTable = 0;

	cout << "要访问的指令地址的个数 :>";
	cin >> IC;
	cout << "页表项的个数 :>";
	cin >> pageCount;
	cout << "页面大小 :>";
	cin >> pageSize;
	cout << "缓存区大小 :>";
	cin >> bufferSize;
	cout << "是否显示访问表1/0 :>";
	cin >> showTable;

	delete[] addresses;
	addresses = new int[IC];
	for (int i = 0; i < IC; i++) {
		cout << "输入第" << i + 1 << "个地址 :>";
		cin >> addresses[i];
	}
	delete[] pageTable;
	vector<int> LRU_flag(pageCount, 0);
	pageTable = new int[pageCount];
	// 初始化页表
	for (int i = 0; i < pageCount; i++)
		pageTable[i] = i;
	// 打乱页表顺序
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
	cout << "1.自动化测试(单次)\n2.手动测试\n>";
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