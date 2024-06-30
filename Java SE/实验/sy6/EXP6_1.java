public class EXP6_1{
    public static void main(String[] arg3) {
        System.out.println("这是一个异常处理的例子\n");
        try {
        int i = 10;
        i /= 0;
        }
        catch (ArithmeticException e) {
        System.out.println("异常是："+e.getMessage());
        }
        finally {
        System.out.println("finally 语句被执行");
        }
    }
}
