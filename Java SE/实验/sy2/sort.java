import java.util.Comparator;
import java.util.Random;
import java.util.Arrays;

public class sort{
    public static void main(String[] args){
        Random r = new Random();
        Integer[] numbers = new Integer[10];
        for(int i = 0; i < 10; i ++)
            numbers[i] = r.nextInt(100);
        Arrays.sort(numbers, new Comparator<Integer>() {
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        for (int i : numbers) {
            System.out.print(i + " ");
        }
    }
}
