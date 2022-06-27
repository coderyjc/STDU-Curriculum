#include<iostream>
#include<vector>

using namespace std;

// 指令地址的个数为20
#define IC 20

// 页面的大小初始为1K
unsigned int pageSize = 1024;

// 指令地址序列
int addresses[IC];


/// 产生指令地址流
/// 产生需要访问的地址顺序
/// 50%的指令是顺序执行的, 25%是均匀分散在前边, 25%均匀分散在后面
void generateAddress() {
	
}

/// 先进先出
int FIFO() {
	return 0;
}

/// 最近最少使用
int LRU() {
	return 0;
}



/// 打印页表
void printPageTable() {

}



int main() {
	return 0;
}