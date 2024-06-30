public class StringTest {
    public static void main(String[] args) {

        String s1 = new String("you are a student"),s2=new String("how are you");
        if (s1.equals(s2)) {  // 判断s1与s2是否相同
            System.out.println("s1与s2相同");
        } else {
            System.out.println("s1与s2不相同");
        }

        String s3=new String("22030219851022024");
        if (s3.startsWith("220302")) {// 判断s3的前缀是否是“220302”
            System.out.println("吉林省的身份证");
        }

        String s4=new String("你"), s5 = new String("我");
        if(s4.compareTo(s5) > 0) {  // s4大于s5
            System.out.println("s4大于s5");
        } else {
            System.out.println("s4小于s5");
        }

        int position = 0;
        String path = "c:\\java\\jsp\\A.java";
        position = path.lastIndexOf('\\');        // 获取path中最后出现目录分隔符号的位置

        System.out.println("c:\\java\\jsp\\A.java中最后出现\\的位置:" + position);
        String fileName = path.substring(path.indexOf('A'), path.lastIndexOf('a') + 1); // 获取path中“A.java”子字符串

        System.out.println("c:\\java\\jsp\\A.java中含有的文件名:" + fileName);
        String s6 = new String("100"), s7 = new String("123.678");
        int n1 = Integer.parseInt(s6); // 将s6转化成int型数据
        double n2 = Double.parseDouble(s7); // 将s7转化成double型数据

        double n = n1 + n2;

        System.out.println(n);

        String s8 = new String("ABCDEF");

        char a[] = s8.toCharArray();  // 将s8存放到数组a中

        for(int i = a.length - 1; i >= 0; i--) { //【代码9】  打印 a[I]
            System.out.print(s8.charAt(i));
        }


    }
}
