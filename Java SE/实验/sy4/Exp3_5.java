import java.math.BigInteger;

class Exp3_5{
    public static void main(String[] args){
        int x = 10,y = 1;
        //调用方法ff1(x,y);
        Exp3_5 e = new Exp3_5();
        e.ff1(x, y);
        //输出x，y的值
        System.out.println("x = " + x + "  y = " + y);
    }
    void ff1(int x,int y){
        //补充代码
        BigInteger rst = BigInteger.valueOf(x);
        BigInteger big_x = BigInteger.valueOf(x);
        for(; y >= 1; y--){
            rst = rst.multiply(big_x);
        }
        System.out.println( "乘方之后的结果为 ：" + rst);
    }
}
