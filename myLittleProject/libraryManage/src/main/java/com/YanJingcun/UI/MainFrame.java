package com.YanJingcun.UI;

import javax.swing.*;
import java.awt.*;

public class MainFrame extends JFrame {

    //Test
    public static void main(String[] args) {
        new MainFrame();
    }

    public MainFrame(){
        initUI();
    }

    public void initUI(){

        JPanel jp_sideMenu = new JPanel();
        jp_sideMenu.setLayout(new FlowLayout()); //设置垂直流布局，使checkbox的宽度等于sideMenu的宽度



        this.setSize(1200, 700);
        this.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        this.setResizable(false);
        this.setVisible(true);
    }
}
