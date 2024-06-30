//
// Created by Administrator on 2021/7/1.
//

#include <iostream>

using namespace std;

void printNums(int num[], int n);

/**
 * 13、堆排序
 * 输入：待排序数据序列
 * 功能要求：输出每步骤排序情况；希望能进行排序方向的选择（从大到小或从小到大）
 */

int main(){

    int n; // 一共多少数

    cout << "How Many Numbers ? ";
    cin >> n;

//    int sortType; // 正序还是倒序？
//    cout << "0: Positive; 1: Nagtive ?";
//    cin >> sortType;
//    if(sortType != 0 && sortType != 1){
//        cout << "ERROR" << endl;
//        return 0;
//    }

    int* num = new int[n];
    for (int i = 0; i < n; ++i) {
        cout << i + 1  << " : ";
        cin >> num[i];
    }



    cout << "排序后：" << endl;
    printNums(num, n);

    return 0;
}



void printNums(int num[], int n){
    cout << "排序情况：" ;
    for (int i = 0; i < n; ++i) {
        cout << num[i] << " ";
    }
    cout << endl;
}