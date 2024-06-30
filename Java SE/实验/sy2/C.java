import java.io.*;
public class C {
    public static void main(String args[]) {
        char ch;
        System.out.println("按 1/2/3 数字键可得大奖!");
        try{
            ch = (char)System.in.read();
            //用switch-case实现，此处代码同学们实现
            switch(ch){
                case '1' :
                    System.out.println("抽中一辆汽车"); break;
                case '2' :
                    System.out.println("笔记本电脑"); break;
                case '3' :
                    System.out.println("一台冰箱");break;
                default:
                    System.out.println("没有奖品给你");
            }
        }
        catch(IOException e){}
    }
}