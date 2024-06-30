public class EXP3_7 {
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
