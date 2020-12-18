#pragma once
#include<vector>
using namespace std;
class Sorts {

public:

	Sorts() {
		this->cmpOfQuickSort = 0;
		this->movOfQuickSort = 0;
		this->cmpOfHeapSort = 0;
		this->movOfHeapSort = 0;
	}

	vector<int> bubbleSort(int* nums, int n); //√∞≈›≈≈–Ú

	vector<int> insertSort(int*, int); // ≤Â»Î≈≈–Ú

	vector<int> selectionSort(int*, int); // —°‘Ò≈≈–Ú

	vector<int> shellSort(int*, int); // œ£∂˚≈≈–Ú
	
	void quickSort(int*, int, int); // øÏ≈≈

	void heapSort(int*, int); // ∂—≈≈–Ú

	void heapAdjust(int*, int, int);

	void printNums(int *, int); // ¥Ú”° ˝◊È

public:
	int cmpOfQuickSort;
	int movOfQuickSort;
	int cmpOfHeapSort;
	int movOfHeapSort;
};
