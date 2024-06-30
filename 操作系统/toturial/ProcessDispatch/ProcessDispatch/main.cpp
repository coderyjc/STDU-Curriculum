/*********************************************
*
*	Author: Yan Jingcun
*	Date: 2022.04.05
*	Time: 13:10
*	Description: ģ�����ȼ����Ⱥ�ʱ��Ƭ��ת�����㷨
*
**********************************************/

#include<stdlib.h>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


// ���̴�������̬
#define RUN_STATE 0

// ���̴��ھ���̬/�ȴ�״̬
#define WAIT_STATE 1

// ���̴������״̬
#define FINISH_STATE 2

// ��ǰ�㷨������, Ҳ�����ȼ����������ʱ��Ƭ������
#define PRIORITY_ALGORITHM 1

// ��ǰ�㷨������, Ҳ��ʱ��Ƭ��ת�����ʱ��Ƭ������
#define ROLL_ALGORITHM 2

// ��ǰʹ�õ��㷨, Ҳ��Ϊ��ǰ�㷨ʹ��ʱ��Ƭ������
int current_dispatch_algorithm = 1;

// ʱ��Ƭ��ת�㷨�е�ʱ��Ƭ��С
int time_slice = 2;

// ��ǰ��CPU��ʱ��
int runTime = 0;

/// <summary>
/// ���̿��ƿ�
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

	// ���̱�ʶ��
	string p_name = "null";

	// ����������/ÿ����ת��ʱ��Ƭ��(��Ϊ����2)
	int p_priority = 0;

	// �����ۼ�ռ�õ�CPUʱ��Ƭ��
	int p_cputime = 0;

	// ���̵���ɻ���Ҫ��ʱ��Ƭ��
	int p_needtime = 50;

	// ����״̬
	int p_status = WAIT_STATE;

	// ����ָ��
	PCB* next = NULL;

}PCB;

// ��ǰ���н���ָ��
PCB* p_run = NULL;
// ��������ͷָ��
PCB* p_ready = NULL;
// �������е�βָ��
PCB* p_tail = NULL;
// ��ɶ���ͷָ��
PCB* p_finish = NULL;




/// <summary>
/// ���������㷨�У�����δ��ɵ� PCB ��������˳����뵽����������
/// </summary>
/// <returns>��������0</returns>
int insert1() {
	PCB* temp = p_ready;

	if (NULL == p_ready) {
		// �����һ���������е�ʱ��, ready�ǿյ�, ��run���ǿյ�
		p_ready = p_run;
	}
	else if (p_run->p_priority <= temp->p_priority) {
		// �������ȼ�����
		p_run->next = p_ready;
		p_ready = p_run;
	}
	else {
		// �������ȼ�����
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
/// ����ת���У�����δ��ɵ� PCB ��������˳����뵽�������� �У� 
/// </summary>
/// <returns></returns>
int insert2() {
	// ֱ�ӷŵ���β
	if (NULL != p_tail->next) p_tail = p_tail->next;
	p_tail->next = p_run;
	p_tail = p_run; // ����
	p_run = NULL;
	p_tail->next = NULL;
	p_ready->p_status = RUN_STATE; //��ͷ����
	return 0;
}

/// <summary>
/// ���Ⱦ������еĵ�һ������Ͷ�����У�
/// </summary>
/// <returns>��������0</returns>
int firstIn() {
	// cout << p_run->p_name << " ";
	// cout << runTime << " ";

	// ����һ��cpuʱ��
	if (current_dispatch_algorithm == PRIORITY_ALGORITHM) {
		// ���ȼ�����
		p_run->p_priority += 1;
		p_run->p_cputime += 1;
		p_run->p_needtime -= 1;
		runTime += 1;
	}
	else if (current_dispatch_algorithm == ROLL_ALGORITHM) {
		// ��ѯ
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
	// �ж���û�����н���
	if (0 == p_run->p_needtime) {
		// ��������, ������ɶ���
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
		// û��������, �Ͳ��뵽��������
		current_dispatch_algorithm == PRIORITY_ALGORITHM ? insert1() : insert2();
	}
	// ���̿�ʼִ�е�ʱ��
	// cout << runTime << "\n";
	return 0;
}

/// <summary>
/// ֻ��print��������,�����ӡ
/// </summary>
/// <param name="target">��Ҫ��ӡ�Ķ��е�ͷָ��</param>
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
/// ��ʾÿִ��һ�κ����н��̵�״̬���й���Ϣ��
/// </summary>
/// <returns></returns>
int print() {
	// ���
	cout << "name\tcputime\tneedtime\tpriority\tstate\n";
	// �������ִ��̬
	if (NULL != p_run) subPrint(p_run);
	// ��������ȴ�̬
	if (NULL != p_ready) subPrint(p_ready);
	// ����������̬
	if (NULL != p_finish) subPrint(p_finish);
	return 0;
}

/// <summary>
/// �����½��̣��������� PCB �����������
/// </summary>
/// <returns>-1�쳣�˳�, 0�����˳�</returns>
int create() {
	// ��Ϣ¼��
	cout << "�������� ������Ҫ��cpuʱ��\n";
	string t_name;
	int t_needTime;
	cin >> t_name >> t_needTime;
	// ����PCB
	PCB* temp = new PCB();
	if (NULL == temp) {
		cerr << "�ڴ�ռ䲻��, �޷���������";
		return -1;
	}
	// ��ʼ����Ϣ
	temp->next = NULL;
	temp->p_needtime = t_needTime;
	temp->p_name = t_name;
	if (current_dispatch_algorithm == PRIORITY_ALGORITHM)
		temp->p_priority = 50 - t_needTime; // ���ȼ�����
	else
		temp->p_priority = time_slice; // ʱ��Ƭ��ѯ
	temp->p_cputime = 0;
	temp->p_status = WAIT_STATE;
	// �����������
	if (NULL != p_ready) {
		p_tail->next = temp;
		p_tail = temp;
	}
	else {
		p_ready = temp;
		p_tail = temp;
	}
	// ������������0
	return 0;
}

bool cmp(PCB a, PCB b) {
	return a.p_priority < b.p_priority;
}

// ��ʵ�޻�������
void comparePriority() {
	PCB* temp = p_ready;
	vector<PCB> v;
	while (NULL != temp) {
		PCB t = PCB(temp->p_name, temp->p_priority, temp->p_cputime, temp->p_needtime, temp->p_status, NULL);
		v.push_back(t);
		temp = temp->next;
	}
	// ��������������(����)
	sort(v.begin(), v.end(), cmp);
	temp = p_ready;
	// ���ƻ���
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
/// ���������㷨���Ƚ���
/// </summary>
/// <returns>0 ��ʾ��������Ϊ��; 1��ʾ��������Ϊ��</returns>
int priSCH() {
	if (NULL == p_ready) {
		// ��������Ϊ��, ��ʾ�����Ѿ�������, ��������
		// �жϴ�ʱ��û�������еĽ���
		if (NULL == p_run) return 0;
		else firstIn();
	}
	// �������ȼ���������
	comparePriority();
	// ѡһ��
	p_run = p_ready;
	p_run->p_status = RUN_STATE;
	p_ready = p_ready->next;
	// ����
	firstIn();
	return 1;
}

// ��ʱ��Ƭ��ת�����Ƚ��̡�
int roundSCH() {
	if (NULL == p_ready) {
		// ��������Ϊ��, ��ʾ�����Ѿ�������, ��������
		// �жϴ�ʱ��û�������еĽ���
		if (NULL == p_run) return 0;
		else firstIn();
	}
	// ѡһ��
	p_run = p_ready;
	p_ready = p_ready->next;
	// ����
	firstIn();
	return 1;
}

int main() {
	cout << "ѡ������㷨";
	cout << "1.���ȼ�����\n2.ʱ��Ƭ��ת����\n����.�˳�\n";
	cin >> current_dispatch_algorithm;

	if (current_dispatch_algorithm == PRIORITY_ALGORITHM) {
		for (int i = 0; i < 5; i++) create();
		// ���ȼ������㷨
		while (priSCH()) print();
	}
	else if (current_dispatch_algorithm == ROLL_ALGORITHM) {
		// ʱ��Ƭ��ת�㷨
		cout << "ʱ��Ƭ��С";
		cin >> time_slice;
		for (int i = 0; i < 5; i++) create();
		while (roundSCH()) print();
	}
	else return 0;

	return 0;
}

