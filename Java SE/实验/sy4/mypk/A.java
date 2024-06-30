package mypk;

public class A{
    public void print(String s){
        B b1 = new B();
        System.out.println(b1.addString(s));
    }
}

class B{
    String addString(String s){
        return "-----------" + s + "--------------";
    }
}