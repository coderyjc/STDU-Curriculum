package UI;

import Components.Panel.BackgroundPanel;
import Domain.User;
import Utils.DBUtils.DMLUtils;
import Utils.DBUtils.DQLUtils;
import Utils.RealPath;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class SignUpFrame {
    private final JFrame jf = new JFrame("Sign Up");

    final int WIDTH = 600;
    final int HEIGHT = 700;

    public void initUI() throws IOException {
        jf.setBounds((Toolkit.getDefaultToolkit().getScreenSize().width - WIDTH)/2, (Toolkit.getDefaultToolkit().getScreenSize().height - HEIGHT)/2, WIDTH, HEIGHT);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        BackgroundPanel bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("regist.png"))));

        Box vBox = Box.createVerticalBox();

        //用户姓名
        Box nBox = Box.createHorizontalBox();
        JLabel nLabel = new JLabel("姓   名：");
        JTextField nField = new JTextField(15);

        nBox.add(nLabel);
        nBox.add(Box.createHorizontalStrut(20));
        nBox.add(nField);

        //用户名
        Box uBox = Box.createHorizontalBox();
        JLabel uLabel = new JLabel("用户ID：");
        JTextField uField = new JTextField(15);

        uBox.add(uLabel);
        uBox.add(Box.createHorizontalStrut(20));
        uBox.add(uField);

        //组装密码
        Box pBox = Box.createHorizontalBox();
        JLabel pLabel = new JLabel("密   码：");
        JTextField pField = new JTextField(15);

        pBox.add(pLabel);
        pBox.add(Box.createHorizontalStrut(20));
        pBox.add(pField);

        //确认密码
        Box pBox2 = Box.createHorizontalBox();
        JLabel pLabel2 = new JLabel("确认密码：");
        JTextField pField2 = new JTextField(15);

        pBox2.add(pLabel2);
        pBox2.add(pField2);

        //组装手机号
        Box tBox = Box.createHorizontalBox();
        JLabel tLabel = new JLabel("手机号 ：");
        JTextField tField = new JTextField(15);

        tBox.add(tLabel);
        tBox.add(Box.createHorizontalStrut(20));
        tBox.add(tField);

        //身份
        Box sBox = Box.createHorizontalBox();
        JLabel sLabel = new JLabel("  身份   ");
        JComboBox<String> sjcb = new JComboBox<>(new String[]{"1.其他人","2.本科生","3.研究生","4.教师","0.管理员"});
        sBox.add(sLabel);
        sBox.add(Box.createHorizontalStrut(20));
        sBox.add(sjcb);

        //组装性别
        Box gBox = Box.createHorizontalBox();
        JLabel gLabel = new JLabel("性    别：");
        JRadioButton maleBtn = new JRadioButton("男",true);
        JRadioButton femaleBtn = new JRadioButton("女",false);

        //实现单选的效果
        ButtonGroup bg = new ButtonGroup();
        bg.add(maleBtn);
        bg.add(femaleBtn);

        gBox.add(gLabel);
        gBox.add(Box.createHorizontalStrut(20));
        gBox.add(maleBtn);
        gBox.add(femaleBtn);
        gBox.add(Box.createHorizontalStrut(120));

        //组装按钮
        Box btnBox = Box.createHorizontalBox();
        JButton registBtn = new JButton("提交");
        registBtn.setFont(new Font(null, Font.PLAIN, 20));
        JButton backBtn = new JButton("返回");
        backBtn.setFont(new Font(null, Font.PLAIN, 20));
        btnBox.add(registBtn);
        btnBox.add(Box.createHorizontalStrut(80));
        btnBox.add(backBtn);


        registBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String userName = nField.getText().trim();
                String userId = uField.getText().trim();
                String pwd1 = pField.getText().trim();
                String pwd2 = pField2.getText().trim();
                String tel = tField.getText().trim();
                int type = sjcb.getItemCount();
                int sex = maleBtn.isSelected() ? 1 : 0;
                //异常情况处理
                //账号已存在

                if ("".equals(userName) || "".equals(userId) || "".equals(pwd1)|| "".equals(pwd2)|| "".equals(tel)){
                    JOptionPane.showMessageDialog(jf, "请全部填完之后再提交。");
                } else if (DQLUtils.isExist(new User(userId))){
                    JOptionPane.showMessageDialog(jf,"账号已存在，换一个试试吧");
                } else if (!pwd1.equals(pwd2)){ //密码不一样
                    JOptionPane.showMessageDialog(jf, "两次密码输入不一样，请检查无误后重新输入。");
                } else {
                    //向数据库中插入这条数据
                    boolean isSuc = DMLUtils.addUser(new User(userName, sex, userId, pwd1, type, tel));
                    if (isSuc){
                        JOptionPane.showMessageDialog(jf,"账号注册成功！");
                        try {
                            new LoginFrame().initUI();
                            jf.dispose();
                        } catch (Exception exception) {
                            exception.printStackTrace();
                        }
                    } else{
                        JOptionPane.showMessageDialog(jf,"遇到未知错误，请重试！");
                    }
                }
            }
        });

        backBtn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    new LoginFrame().initUI();
                } catch (Exception exception) {
                    exception.printStackTrace();
                }
                jf.dispose();
            }
        });

        vBox.add(Box.createVerticalStrut(80));
        vBox.add(nBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(uBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(pBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(pBox2);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(tBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(gBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(sBox);
        vBox.add(Box.createVerticalStrut(40));
        vBox.add(btnBox);

        bgp.add(vBox);

        jf.add(bgp);
        jf.setVisible(true);
        jf.setResizable(false);
    }
}
