public class EXP6_2{
    public static void main(String[] args) {
        System.out.println("这是一个异常处理的例子\n");
        try {
            int i= 10;
            i /= 0;
        }
        catch (IndexOutOfBoundsException e) {
            System.out.println("异常是："+e.getMessage());
        }
        finally {
            System.out.println("finally 语句被执行");
        }  
    }
}
