public class Main{

    public static void main(String[] args) {
        Complex c1 = new Complex(1, 2);
        c1.complexAdd(new Complex(3, 4));
        System.out.println(c1);
    }
}

class Complex{
    private int RealPart; //虚数的实部
    private int ImaginPart; // 虚数的虚部

    public Complex(){
        this.ImaginPart = 0;
        this.RealPart = 0;
    }

    public Complex(int r, int i) {
        RealPart = r;
        ImaginPart = i;
    }

    Complex complexAdd(Complex a){
        this.RealPart += a.RealPart;
        this.ImaginPart += a.ImaginPart;
        return this;
    }

    @Override
    public String toString() {
        return this.RealPart + " + " + this.ImaginPart + "i";
    }
}