public class EXP6_1{
    public static void main(String[] args) {
        try {
            System.out.println(args[10]);
        }
        catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("数组下标越界：" + e);
        }
    }
}
