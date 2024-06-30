import java.util.*;

public class maxValue {

    public static void main(String[] args) {

        int i, j;//根据你的需要可添加变量
        //声明arr是一个二维数组，行数是3，列数未知。
        Object[][] arr = new Object[3][];
        // arr每一行是变长的，元素个数为3、4、5
        for (i = 0; i < 3; i++)    //提示：用new关键字分配内存
            arr[i] = new Object[i + 3];

        for (i = 0; i < 3; i++)        // 为arr赋值
            for (j = 0; j < arr[i].length; j++) {
                Random ran = new Random();
                float x = ran.nextFloat();
                arr[i][j] = (int) (x * 100 + 1);
            }

        //补充你的代码，找到最大值，及其所在下标
        int col = 0;
        int row = 0;
        int max = (int) arr[0][0];

        for (i = 0; i < 3; i++)
            for (j = 0; j < arr[i].length; j++)
                if (max < (int) arr[i][j]) {
                    max = (int) arr[i][j];
                    col = i;
                    row = j;
                }

        //补充你的代码，按矩阵形式输出该二维矩阵
        for (i = 0; i < 3; i++) {
            for (j = 0; j < arr[i].length; j++)
                System.out.print(arr[i][j] + " ");
            System.out.println("");
        }
        //补充你的代码，输出最大值及其下标
        System.out.println("最大值为" + max + "\n下标为 " + col + " " + row);

    }
}

