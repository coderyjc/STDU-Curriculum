#include "Sorts.h"
#include<iostream>

using namespace std;

void swap(int& a, int& b) {
	int t = a;
	a = b;
	b = t;
}

vector<int> Sorts::bubbleSort(int* nums, int n) {
	int timeOfCompare = 0;
	int timeOfMove = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 1; j < n - i; j++) {
			if (timeOfCompare++, nums[j - 1] > nums[j]) {
				timeOfMove += 3;
				swap(nums[j - 1], nums[j]);
			}
		}
	}
	vector<int> rst;
	rst.push_back(timeOfCompare);
	rst.push_back(timeOfMove);
	return rst;
}

vector<int> Sorts::insertSort(int* nums, int n) {
	int timeOfCompare = 0;
	int timeOfMove = 0;
	int temp = 0;
	int i, j;
	if (n <= 2) return vector<int>();
	for(i = 1; i < n; i++){
		temp = nums[i];
		if(timeOfCompare++, nums[i] < nums[i - 1]){
			timeOfMove++;
			nums[i] = nums[i - 1];
		}
		for (j = i - 1; temp < nums[j]; j--) {
			timeOfMove++;
			nums[j + 1] = nums[j];
		}
		nums[j + 1] = temp;
	}
	vector<int> rst;
	rst.push_back(timeOfCompare);
	rst.push_back(timeOfMove);
	return rst;
}

vector<int> Sorts::selectionSort(int* nums, int n) {
	int timeOfCompare = 0;
	int timeOfMove = 0;
	int maxdir = 0;
	for (int i = 0; i < n; i++) {
		maxdir = 0;
		for (int j = 0; j < n - i; j++) {
			if (timeOfCompare++, nums[j] > nums[maxdir])
				maxdir = j;
		}
		swap(nums[maxdir], nums[n - i - 1]);
		timeOfMove += 3;
	}
	vector<int> rst;
	rst.push_back(timeOfCompare);
	rst.push_back(timeOfMove);
	return rst;
}

void Sorts::quickSort(int* nums, int first, int last) {
	int low = first;
	int high = last;
	if (low >= high) return;
	int key = nums[low];

	while (low < high) {
		while (this->cmpOfQuickSort++, low < high && nums[high] >= key) high--;
		nums[low] = nums[high];
		while (this->cmpOfQuickSort++, low < high && nums[low] <= key) low++;
		nums[high] = nums[low];
		this->movOfQuickSort += 2;
	}
	nums[low] = key;
	this->movOfQuickSort++;
	quickSort(nums, first, low - 1);
	quickSort(nums, low + 1, last);
}

vector<int> Sorts::shellSort(int* nums, int length) {
	int timeOfCompare = 0;
	int timeOfMove = 0;

	int gap;	//gap是分组的步长
	int temp;	//希尔排序是在直接插入排序的基础上实现的,所以仍然需要哨兵
	for (gap = length / 2; gap > 0; gap = gap / 2) {
		for (int i = 0; i < gap; i++) {
			for (int j = i + gap; j < length; j = j + gap) {	//单独一次的插入排序
				if (timeOfCompare++, nums[j] < nums[j - gap]) {
					temp = nums[j];	//哨兵
					int k = j - gap;
					while (timeOfCompare++, k >= 0 && nums[k] > temp) {
						nums[k + gap] = nums[k];
						k = k - gap;
						timeOfMove++;
					}
					nums[k + gap] = temp;
				}
			}
		}
	}
	vector<int> rst;
	rst.push_back(timeOfCompare);
	rst.push_back(timeOfMove);
	return rst;
}

void Sorts::heapAdjust(int* arr, int start, int end) {
	int dad = start;
	int son = dad * 2 + 1;
	while (son <= end) { 
		if (this->cmpOfHeapSort++, son + 1 <= end && arr[son] < arr[son + 1]) 
			son++;
		if (this->cmpOfHeapSort++, arr[dad] > arr[son])
			return;
		else {
			this->movOfHeapSort += 3;
			swap(arr[dad], arr[son]);
			dad = son;
			son = dad * 2 + 1;
		}
	}
}

void Sorts::heapSort(int* nums, int n) {
	for (int i = n / 2 - 1; i >= 0; i--)
		this->heapAdjust(nums, i, n - 1);
	for (int i = n - 1; i > 0; i--) {
		swap(nums[0], nums[i]);
		this->movOfHeapSort += 3; // 交换看作3次移动
		this->heapAdjust(nums, 0, i - 1);
	}
}