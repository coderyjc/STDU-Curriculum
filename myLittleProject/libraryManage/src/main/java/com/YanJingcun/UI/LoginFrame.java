package com.YanJingcun.UI;

import javax.swing.*;
import java.awt.*;

public class LoginFrame extends JFrame {

    public LoginFrame(){
        initUI();
    }

    void initUI(){

        this.setTitle("Login");
        this.setLayout(null);
        JLabel lbBg = new JLabel(new ImageIcon());
        lbBg.setBounds(0, 0, 600, 700);
        this.add(lbBg);

        JLabel jl_name = new JLabel("Name");
        JLabel jl_pwd = new JLabel("Password");
        JLabel jl_userType = new JLabel("Type");
        JPasswordField jpf_pwd = new JPasswordField();
        JTextField jt_name = new JTextField();
        JComboBox<String> jcb_userType = new JComboBox<>(new String[]
                {"1.UnderGraduate", "2.Graduate", "3.Doctoral Student",
                "4.Post Doctor", "5.Teacher"});
        JButton jb_signIn = new JButton("Sign In");
        JButton jb_signUp = new JButton("Sign Up");

        jl_name.setBounds(100, 180, 100, 40);
        jl_name.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jl_name);
        jt_name.setBounds(240, 180, 250, 40);
        jt_name.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jt_name);
        jl_pwd.setBounds(55, 250, 150, 40);
        jl_pwd.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jl_pwd);
        jpf_pwd.setBounds(240, 250, 250, 40);
        jpf_pwd.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jpf_pwd);
        jl_userType.setBounds(100, 320, 100, 40);
        jl_userType.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jl_userType);
        jcb_userType.setBounds(240, 320, 250, 40);
        jcb_userType.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jcb_userType);
        jb_signIn.setBounds(130, 400, 150, 40);
        jb_signIn.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jb_signUp);
        jb_signUp.setBounds(330, 400, 150, 40);
        jb_signUp.setFont(new Font(null, Font.PLAIN, 25));
        this.add(jb_signIn);

        this.setSize(new Dimension(600, 700));
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.setVisible(true);
        this.setLocationRelativeTo(null);
        this.setResizable(false);
    }

    public static void main(String[] args) {
        new LoginFrame();
    }
}
