import java.util.Random;

public class bubbleSort{
    public static void main(String[] args){
        Random r = new Random();
        Integer[] numbers = new Integer[10];
        for(int i = 0; i < 10; i ++)
            numbers[i] = r.nextInt(100);
        for(int i = 0; i < 10; i++){
            for(int j = 1; j < 10 - i; j++){
                if(numbers[j - 1] < numbers[j]){
                    Integer t = numbers[j - 1];
                    numbers[j - 1] = numbers[j];
                    numbers[j] = t;
                }
            }
        }
        for (int i : numbers) {
            System.out.print(i + " ");
        }
    }
}
