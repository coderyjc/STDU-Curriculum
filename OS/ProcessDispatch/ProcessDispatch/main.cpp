/*********************************************
*
*	Author: Yan Jingcun
*	Date: 2022.04.05
*	Time: 13:10
*	Description: 模拟优先级调度和时间片轮转调度算法
*
**********************************************/

#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


// 进程处于运行态
#define RUN_STATE 0

// 进程处于就绪态/等待状态
#define WAIT_STATE 1

// 进程处于完成状态
#define FINISH_STATE 2

// 当前算法的名称, 也是优先级调度所需的时间片的数量
#define PRIORITY_ALGORITHM 1

// 当前算法的名称, 也是时间片轮转所需的时间片的数量
#define ROLL_ALGORITHM 2

// 当前使用的算法, 也作为当前算法使用时间片的数量
int current_dispatch_algorithm = 1;

// 时间片轮转算法中的时间片大小
int time_slice = 2;

// 当前的CPU总时间
int runTime = 0;

/// <summary>
/// 进程控制块
/// </summary>
typedef struct PCB {

	PCB() {}

	PCB(string name, int prio, int cputime, int needtime, int status, PCB* nxt) {
		this->p_name = name;
		this->p_cputime = cputime;
		this->next = nxt;
		this->p_needtime = needtime;
		this->p_priority = prio;
		this->p_status = status;
	}

	// 进程标识符
	string p_name = "null";

	// 进程优先数/每次轮转的时间片数(设为常数2)
	int p_priority = 0;

	// 进程累计占用的CPU时间片数
	int p_cputime = 0;

	// 进程到完成还需要的时间片数
	int p_needtime = 50;

	// 进程状态
	int p_status = WAIT_STATE;

	// 链表指针
	PCB* next = NULL;

}PCB;

// 当前运行进程指针
PCB* p_run = NULL;
// 就绪队列头指针
PCB* p_ready = NULL;
// 就绪队列的尾指针
PCB* p_tail = NULL;
// 完成队列头指针
PCB* p_finish = NULL;




/// <summary>
/// 在优先数算法中，将尚未完成的 PCB 按优先数顺序插入到就绪队列中
/// </summary>
/// <returns>正常返回0</returns>
int insert1() {
	PCB* temp = p_ready;

	if (NULL == p_ready) {
		// 在最后一个进程运行的时候, ready是空的, 但run不是空的
		p_ready = p_run;
	}
	else if (p_run->p_priority <= temp->p_priority) {
		// 按照优先级插入
		p_run->next = p_ready;
		p_ready = p_run;
	}
	else {
		// 按照优先级插入
		while (temp->next && (temp->p_priority < p_run->p_priority)) temp = temp->next;
		p_run->next = temp->next;
		temp->next = p_run;
	}
	if (NULL != p_tail->next) p_tail = p_tail->next;
	if (FINISH_STATE != p_run->p_status) p_run->p_status = RUN_STATE;
	else p_run->p_status = WAIT_STATE;
	p_run = NULL;
	return 0;
}

/// <summary>
/// 在轮转法中，将尚未完成的 PCB 按优先数顺序插入到就绪队列 中； 
/// </summary>
/// <returns></returns>
int insert2() {
	// 直接放到队尾
	if (NULL != p_tail->next) p_tail = p_tail->next;
	p_tail->next = p_run;
	p_tail = p_run; // 后移
	p_run = NULL;
	p_tail->next = NULL;
	p_ready->p_status = RUN_STATE; //对头运行
	return 0;
}

/// <summary>
/// 调度就绪队列的第一个进程投入运行；
/// </summary>
/// <returns>正常返回0</returns>
int firstIn() {
	// cout << p_run->p_name << " ";
	// cout << runTime << " ";

	// 运行一个cpu时间
	if (current_dispatch_algorithm == PRIORITY_ALGORITHM) {
		// 优先级调度
		p_run->p_priority += 1;
		p_run->p_cputime += 1;
		p_run->p_needtime -= 1;
		runTime += 1;
	}
	else if (current_dispatch_algorithm == ROLL_ALGORITHM) {
		// 轮询
		if (p_run->p_needtime == 1) {
			p_run->p_needtime -= 1;
			p_run->p_cputime += 1;
			runTime += 1;
		}
		else {
			p_run->p_needtime -= time_slice;
			p_run->p_cputime += time_slice;
			runTime += time_slice;
		}
	}
	// 判断有没有运行结束
	if (0 == p_run->p_needtime) {
		// 运行完了, 插入完成队列
		p_run->p_status = FINISH_STATE;
		if (NULL == p_finish) {
			p_finish = p_run;
			p_run->next = NULL;
			p_run = NULL;
		}
		else {
			PCB* temp = p_finish;
			while (temp->next) temp = temp->next;
			temp->next = p_run;
			p_run->next = NULL;
			p_run = NULL;
		}
	}
	else {
		// 没有运行完, 就插入到就绪队列
		current_dispatch_algorithm == PRIORITY_ALGORITHM ? insert1() : insert2();
	}
	// 进程开始执行的时间
	// cout << runTime << "\n";
	return 0;
}

/// <summary>
/// 只由print函数调用,方便打印
/// </summary>
/// <param name="target">需要打印的队列的头指针</param>
void subPrint(PCB* target) {
	PCB* temp = target;
	char state[3] = { 'R', 'W', 'F' };
	do {
		cout << temp->p_name << '\t'
			<< temp->p_cputime << '\t'
			<< temp->p_needtime << "\t\t"
			<< temp->p_priority << "\t\t"
			<< state[temp->p_status] << '\n';
		temp = temp->next;
	} while (NULL != temp);
}

/// <summary>
/// 显示每执行一次后所有进程的状态及有关信息。
/// </summary>
/// <returns></returns>
int print() {
	// 输出
	cout << "name\tcputime\tneedtime\tpriority\tstate\n";
	// 尝试输出执行态
	if (NULL != p_run) subPrint(p_run);
	// 尝试输出等待态
	if (NULL != p_ready) subPrint(p_ready);
	// 尝试输出完成态
	if (NULL != p_finish) subPrint(p_finish);
	return 0;
}

/// <summary>
/// 创建新进程，并将它的 PCB 插入就绪队列
/// </summary>
/// <returns>-1异常退出, 0正常退出</returns>
int create() {
	// 信息录入
	cout << "进程名称 进程需要的cpu时间\n";
	string t_name;
	int t_needTime;
	cin >> t_name >> t_needTime;
	// 创建PCB
	PCB* temp = new PCB();
	if (NULL == temp) {
		cerr << "内存空间不足, 无法创建进程";
		return -1;
	}
	// 初始化信息
	temp->next = NULL;
	temp->p_needtime = t_needTime;
	temp->p_name = t_name;
	if (current_dispatch_algorithm == PRIORITY_ALGORITHM)
		temp->p_priority = 50 - t_needTime; // 优先级调度
	else
		temp->p_priority = time_slice; // 时间片轮询
	temp->p_cputime = 0;
	temp->p_status = WAIT_STATE;
	// 加入就绪队列
	if (NULL != p_ready) {
		p_tail->next = temp;
		p_tail = temp;
	}
	else {
		p_ready = temp;
		p_tail = temp;
	}
	// 正常创建返回0
	return 0;
}

bool cmp(PCB a, PCB b) {
	return a.p_priority < b.p_priority;
}

// 朴实无华的排序
void comparePriority() {
	PCB* temp = p_ready;
	vector<PCB> v;
	while (NULL != temp) {
		PCB t = PCB(temp->p_name, temp->p_priority, temp->p_cputime, temp->p_needtime, temp->p_status, NULL);
		v.push_back(t);
		temp = temp->next;
	}
	// 借用容器的排序(滑稽)
	sort(v.begin(), v.end(), cmp);
	temp = p_ready;
	// 复制回来
	for (int i = 0; NULL != temp; i++) {
		temp->p_cputime = v[i].p_cputime;
		temp->p_needtime = v[i].p_needtime;
		temp->p_priority = v[i].p_priority;
		temp->p_status = v[i].p_status;
		temp->p_name = v[i].p_name;
		temp = temp->next;
	}
}

/// <summary>
/// 按优先数算法调度进程
/// </summary>
/// <returns>0 表示就绪队列为空; 1表示就绪队列为空</returns>
int priSCH() {
	if (NULL == p_ready) {
		// 就绪队列为空, 表示程序已经运行完, 结束运行
		// 判断此时有没有在运行的进程
		if (NULL == p_run) return 0;
		else firstIn();
	}
	// 按照优先级重新排序
	comparePriority();
	// 选一个
	p_run = p_ready;
	p_run->p_status = RUN_STATE;
	p_ready = p_ready->next;
	// 运行
	firstIn();
	return 1;
}

// 按时间片轮转法调度进程。
int roundSCH() {
	if (NULL == p_ready) {
		// 就绪队列为空, 表示程序已经运行完, 结束运行
		// 判断此时有没有在运行的进程
		if (NULL == p_run) return 0;
		else firstIn();
	}
	// 选一个
	p_run = p_ready;
	p_ready = p_ready->next;
	// 运行
	firstIn();
	return 1;
}

int main() {
	cout << "选择调度算法";
	cout << "1.优先级调度\n2.时间片轮转调度\n其他.退出\n";
	cin >> current_dispatch_algorithm;

	if (current_dispatch_algorithm == PRIORITY_ALGORITHM) {
		for (int i = 0; i < 5; i++) create();
		// 优先级调度算法
		while (priSCH()) print();
	}
	else if (current_dispatch_algorithm == ROLL_ALGORITHM) {
		// 时间片轮转算法
		cout << "时间片大小";
		cin >> time_slice;
		for (int i = 0; i < 5; i++) create();
		while (roundSCH()) print();
	}
	else return 0;

	return 0;
}

