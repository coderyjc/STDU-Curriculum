/**
 * 核心: 在填数之前进行元素的加减，来避免 元素的重复填入 和 坐标的过度增加。
 * 
 **/


#include<iostream>
#include<string>

using namespace std;

int main() {

	int n;
	cin >> n;

	int a[20][20];
	int x = 0, y = n - 1, tot = 1;
	memset(a, 0, sizeof(a));
	a[x][y] = 1;
	while (tot < n * n) {
		while (x + 1 < n && !a[x + 1][y]) a[++x][y] = ++tot;
		while (y - 1 >= 0 && !a[x][y - 1]) a[x][--y] = ++tot;
		while (x - 1 >= 0 && !a[x - 1][y]) a[--x][y] = ++tot;
		while (y + 1 < n && !a[x][y + 1]) a[x][++y] = ++tot;
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	return 0;
}