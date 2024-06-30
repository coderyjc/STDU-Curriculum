public class Main{
    public static void main(String[] args) {
        EXP3_7 e1 = new EXP3_7();
        e1.setData("王大力", 20);
        e1.print();

        EXP3_8 e2 = new EXP3_8("信息学院", "计算机科学与技术系");
        e2.setData("大力", 18);
        e2.print();
    }
}

class EXP3_7 {
    protected String xm; // 具有保护修饰符的成员变量
    protected int xh;
    void setData(String m, int h){ // 设置数据的方法
        xh = h;
        xm = m;
    }

    public void print() { // 输出数据的方法
        System.out.println(xm + " " + xh);
    }
}

class EXP3_8 extends EXP3_7{
    private String xy;
    private String xi;

    public EXP3_8(String xy, String xi) {
        this.xy = xy;
        this.xi = xi;
    }

    @Override
    public void print() {
        System.out.println(xm + " " + xh + " " + xy + " " + xi);
    }
}