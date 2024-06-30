import java.io.*;
public class D {
    public static void main(String args[]) {
        char ch;
        System.out.println("按 1/2/3 数字键可得大奖!");
        try{
            ch = (char)System.in.read();
            //用switch-case实现，此处代码同学们实现
            if(ch == '1')
                    System.out.println("抽中一辆汽车");
            else if(ch == '2')
                    System.out.println("笔记本电脑");
            else if(ch == '3')
                    System.out.println("一台冰箱");
            else
                    System.out.println("没有奖品给你");
        }
        catch(IOException e){}
    }
}
