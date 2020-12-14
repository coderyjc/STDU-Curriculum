#include<ctime>
#include<cstdlib>
#include<iostream>
#include"Sorts.h"
using namespace std;

/*
 因为是对数组本身进行排序，所以在每次排序之后再次排序的时候，数组本身就是有序的，
 所以要在每一次排序完毕之后再次对数组进行赋值
*/
vector<vector<int>> getData(int size) {
	srand(time(NULL));
	vector<vector<int>> allRst; // 存储所有比较的所有数据
	int* nums = new int[size];
	for (int i = 0; i < 5; i++) {
		// 一共进行5次比较
		Sorts s;
		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.bubbleSort(nums, size));

		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.insertSort(nums, size));

		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.selectionSort(nums, size));

		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		allRst.push_back(s.shellSort(nums, size));
		// 由于快排涉及到了递归，所以用了“全局变量”来存储相关的数据
		vector<int> t;
		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		s.quickSort(nums, 0, size);
		t.push_back(s.cmpOfQuickSort);
		t.push_back(s.movOfQuickSort);
		allRst.push_back(t);
		// 先清除与快排相关的数据
		t.clear();
		for (int i = 0; i < size; i++) nums[i] = rand() % 10000;
		s.heapSort(nums, size);
		t.push_back(s.cmpOfHeapSort);
		t.push_back(s.movOfHeapSort);
		allRst.push_back(t);
	} //获取所有比较的所有的5次数据

	vector<vector<int>> rst;
	int sumCmp[6] = { 0, 0, 0, 0, 0, 0 }; // 每一种比较的总的比较次数
	int sumMov[6] = { 0, 0, 0, 0, 0, 0 }; // 每一种比较的总的移动次数
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			sumCmp[j] += allRst[j + i * 5][0];
			sumMov[j] += allRst[j + i * 5][1];
		}
	}

	for (int i = 0; i < 6; i++) {
		// 每一种比较的平均比较和移动次数
		vector<int> t;
		t.push_back(sumCmp[i] / 5);
		t.push_back(sumMov[i] / 5);
		rst.push_back(t);
	}
	return rst;
}

int main() {
	srand(time(NULL));
	const string names[] = { "冒泡：", "插入：", "选择：", "希尔：", "快排：", "堆排："};
	for (int i = 100; i <= 6400; i *= 2) { // 改成10了
		cout << "样本大小: " << i << endl;
		vector<vector<int>> rst = getData(i);
		for (int i = 0; i < 6; i++) {
				cout << names[i] << "比较次数 " << rst[i][0] << " 移动次数 " << rst[i][1];
			cout << endl;
		}
		cout << endl;
	}
	return 0;
}
