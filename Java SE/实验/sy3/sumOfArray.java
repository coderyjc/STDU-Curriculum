import java.util.*;

public class sumOfArray {

    public static void main(String[] args) {
        int sum = 0;
        System.out.println("矩阵中的元素为 ：");

        Random r = new Random();
        int arr[][] = new int[3][3];
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                arr[i][j] = r.nextInt(100);
                sum += arr[i][j];
                System.out.print( arr[i][j] + " ");
            }
            System.out.println("");
        }

        System.out.println("矩阵中所有元素的和为 " + sum);

    }
}

