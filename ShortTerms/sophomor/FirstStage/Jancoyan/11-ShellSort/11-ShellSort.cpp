//
// Created by Administrator on 2021/6/30.
//

#include <iostream>

using namespace std;

void shell_sort(int num[], int n, int sortType);
void printNums(int num[], int n);

/*
 * 11、希尔排序
 * 输入：待排序数据序列
 * 功能要求：输出每步骤的步长和排序情况；希望能进行排序方向的选择（从大到小或从小到大）
 */
int main(){

    int n; // 一共多少数组

    cout << "How Many Numbers ? ";
    cin >> n;

    int sortType; // 正序还是倒序？
    cout << "0: Positive; 1: Nagtive?";
    cin >> sortType;
    if(sortType != 0 && sortType != 1){
        cout << "ERROR" << endl;
        return 0;
    }

    int* num = new int[n];
    for (int i = 0; i < n; ++i) {
        cout << i +1  << " : ";
        cin >> num[i];
    }

    shell_sort(num, n, sortType);

    cout << "排序后：" << endl;
    for (int i = 0; i < n; ++i) {
        cout << num[i] << " ";
    }

    return 0;
}


void shell_sort(int num[], int n, int sortType){

    // 分组
    for (int gap = n / 2; gap > 0; gap/= 2) {
        cout << "当前步长：" << gap << endl;
        // 步长每次减为原来的一半
        for (int i = 0; i < gap; ++i) {
            // 组间循环
            for (int j = i + gap; j < n; j += gap) {
                // 组内直接插入排序
                if (sortType == 0) {
                    // 升序排列
                    if (num[j] < num[j - gap]) {
                        // j 位置上比较小，应该插入到前面去
                        int temp = num[j];
                        // j 的初始值为 i + gap，所以 k 不可能下溢
                        int k = j - gap;
                        // k 最小的初始值为这一组的第一个数
                        while (k >= 0 && num[k] > temp) {
                            // 前移
                            num[k + gap] = num[k];
                            k -= gap;
                        }
                        // 插入
                        num[k + gap] = temp;
                    }
                } else {
                    // 降序排列
                    if (num[j] > num[j - gap]) {
                        // j 位置上比较大，应该插入到前面去
                        int temp = num[j];
                        // j 的初始值为 i + gap，所以 k 不可能下溢
                        int k = j - gap;
                        // k 最小的初始值为这一组的第一个数
                        while (k >= 0 && num[k] < temp) {
                            // 前移
                            num[k + gap] = num[k];
                            k -= gap;
                        }
                        // 插入
                        num[k + gap] = temp;
                    }
                }
            }
            // 打印排序情况
            printNums(num, n);
        }
    }

}


void printNums(int num[], int n){
    cout << "排序情况：" ;
    for (int i = 0; i < n; ++i) {
        cout << num[i] << " ";
    }
}