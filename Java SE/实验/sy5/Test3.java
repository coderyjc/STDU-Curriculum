abstract class Test3 {
    void eat(){
    }
    abstract void breth();
    abstract void sleep();
}

class SubTest extends Test3{
    @Override
    void breth() {
        System.out.println("breth.");
    }

    @Override
    void sleep() {
        System.out.println("sleep.");
    }
}

class Integration{
    public static void main(String[] args) {
        SubTest s = new SubTest();
        s.sleep();
        s.breth();
    }
}