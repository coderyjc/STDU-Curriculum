package Components;

import Utils.RealPath;
import Utils.ScreenUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class AddBookDialog extends JDialog {

    final int WIDTH = 500;
    final int HEIGHT = 750;

    public AddBookDialog(JFrame jf, String title, boolean isModel, ActionListenerCallBack listener) {
        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth()-WIDTH)/2,(ScreenUtils.getScreenHeight()-HEIGHT)/2,WIDTH,HEIGHT);
        BackgroundPanel bgp = null;
        try {
            bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("addbook.png"))));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 垂直的箱子，存放label和textField
        Box vBox = Box.createVerticalBox();

        // 书籍名称
        Box nBox = Box.createHorizontalBox();
        JLabel nLabel = new JLabel("书籍名称");
        JTextField nField = new JTextField(15);
        nBox.add(nLabel);
        nBox.add(Box.createHorizontalStrut(20));
        nBox.add(nField);

        // 书籍作者
        Box aBox = Box.createHorizontalBox();
        JLabel aLabel = new JLabel("书籍作者");
        JTextField aField = new JTextField(15);

        aBox.add(aLabel);
        aBox.add(Box.createHorizontalStrut(20));
        aBox.add(aField);

        //价格
        Box pBox = Box.createHorizontalBox();
        JLabel pLabel = new JLabel("书籍价格");
        JTextField pField = new JTextField(15);

        pBox.add(pLabel);
        pBox.add(Box.createHorizontalStrut(20));
        pBox.add(pField);

        //库存
        Box sBox = Box.createHorizontalBox();
        JLabel sLabel = new JLabel("书籍库存");
        JTextField sField = new JTextField(15);

        sBox.add(sLabel);
        sBox.add(Box.createHorizontalStrut(20));
        sBox.add(sField);

        //简介
        Box dBox = Box.createHorizontalBox();
        JLabel dLabel = new JLabel("书籍简介");
        JTextField dFiled = new JTextField(15);

        dBox.add(dLabel);
        dBox.add(Box.createHorizontalStrut(20));
        dBox.add(dFiled);

        //按钮
        Box bBox = Box.createHorizontalBox();
        JButton addButton = new JButton("添加");
        JButton backButton = new JButton("返回");

        bBox.add(addButton);
        bBox.add(Box.createHorizontalStrut(100));
        bBox.add(backButton);

        //监听按钮
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

            }
        });

        // 返回按钮，直接关闭这个窗口
        backButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        vBox.add(Box.createVerticalStrut(100));
        vBox.add(nBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(aBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(pBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(sBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(dBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(bBox);

        //为了左右有间距，在vBox外层封装一个水平的Box，添加间隔
        Box hBox = Box.createHorizontalBox();
        hBox.add(Box.createHorizontalStrut(20));
        hBox.add(vBox);
        hBox.add(Box.createHorizontalStrut(20));

        bgp.add(hBox);
        this.add(bgp);
    }

}
