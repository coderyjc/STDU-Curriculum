//
// Created by Administrator on 2021/6/30.
//

#include <iostream>

using namespace std;


void quickSort(int num[], int l, int r);
void printNums(int num[], int n);

/*12、快速排序
 * 输入：待排序数据序列
 * 功能要求：输出每步骤的枢轴选择和排序情况；希望能进行排序方向的选择（从大到小或从小到大）
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

    quickSort(num, 0, n - 1);

    cout << "排序后：" << endl;
    printNums(num, n);

    return 0;
}

/**
 * 快速排序
 * @param num 待排序数组
 * @param l 左边界，闭
 * @param r 右边界，开
 */
void quickSort(int* num, int l, int r){
    if(l >= r){
        return;
    }

    int i = l; // 左上限
    int j = r; // 右上限
    int axis = num[l]; // 枢轴变量, 默认是待排序数组最左边的数

    while (i < j){
        // 从右向左寻找第一个小于等于枢轴变量的值
        while (i < j && num[i] > axis) j--;
        // i < j 说明j 是个有效值，把 j 的值赋给 i，i++
        if(i < j) num[i++] = num[j];
        // i 大于等于 j 说明向下（向左）溢出了，这时候不做处理
        // 从右向做寻找第一个大于等于枢轴变量的值
        while (i < j && num[i] < axis) i++;
        // i < j 说明j 是个有效值，把 i 的值赋给 j，j++
        if (i < j) num[j--] = num[i];
    }
    // 循环跑完的时候 i == j
    // 这时候i所在的位置就是枢轴变量的位置
    num[i] = axis;
    // 打印当前的状态
    printNums(num, 10);
    // 递归调用
    quickSort(num, l, i - 1);
    quickSort(num, i + 1, r);
}


void printNums(int num[], int n){
    cout << "排序情况：" ;
    for (int i = 0; i < n; ++i) {
        cout << num[i] << " ";
    }
    cout << endl;
}