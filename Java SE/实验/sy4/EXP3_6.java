class EXP3_6{

    public static void main(String[] args) {
        Power p = new Power();
        p.ff2(10, 10);
        System.out.println("方法调用后 x = " + p.x + ", y = " + p.y);
    }
}

class Power{
    int x = 10, y = 10;
    void ff2(int passX, int passY) {
        System.out.println("初始时 x = " + x + ", y = " + y);
        x = passX * passX;
        y = passY * passY;
        System.out.println("方法调用中  x = " + x + ",y = " + y);
    }
}