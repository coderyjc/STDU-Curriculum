package UI;

import Components.BackgroundPanel;
import Domain.User;
import Utils.DBUtils.DQLUtils;
import Utils.RealPath;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.plaf.FontUIResource;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;
import java.util.Arrays;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Map;

public class LoginFrame {

    final int WIDTH = 600;
    final int HEIGHT = 500;

    void initUI() throws Exception{
        InitGlobalFont(new Font("alias", Font.PLAIN, 20));

        JFrame jf = new JFrame("Login");
        jf.setBounds((Toolkit.getDefaultToolkit().getScreenSize().width - WIDTH)/2, (Toolkit.getDefaultToolkit().getScreenSize().height - HEIGHT)/2, WIDTH, HEIGHT);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        BackgroundPanel bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("login.png"))));
        bgp.setBounds(0, 0, WIDTH, HEIGHT);

        //Panel 中的大容器，用来存放三组控件
        Box vBox = Box.createVerticalBox();

        //登录相关的元素
        //用户名
        Box uBox = Box.createHorizontalBox();
        JLabel uLabel = new JLabel("用户ID");
        JTextField uField = new JTextField(15);
//        uLabel.setFont(new Font(null, Font.PLAIN, 20));
//        uField.setFont(new Font(null, Font.PLAIN, 20));
        uBox.add(uLabel);
        uBox.add(Box.createHorizontalStrut(20));
        uBox.add(uField);

    //密码
        Box pBox = Box.createHorizontalBox();
        JLabel pLabel = new JLabel("密    码   ");
        JPasswordField pFiled = new JPasswordField(15);
//        pLabel.setFont(new Font(null, Font.PLAIN, 20));
//        pFiled.setFont(new Font(null, Font.PLAIN, 20));
        pBox.add(pLabel);
        pBox.add(Box.createVerticalStrut(20));
        pBox.add(pFiled);

        //按钮
        Box bBox = Box.createHorizontalBox();
        JButton signIn = new JButton("登录");
        JButton signUp = new JButton("注册");
        signIn.setFont(new Font(null, Font.PLAIN, 20));
        signUp.setFont(new Font(null, Font.PLAIN, 20));
        bBox.add(signIn);
        bBox.add(Box.createHorizontalStrut(100));
        bBox.add(signUp);

        signIn.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String userId = uField.getText().trim();
                String passWord = pFiled.getText().trim();
                if(userId.equals("")||passWord.equals("")){
                    JOptionPane.showMessageDialog(jf,"用户名和密码都不能为空");
                } else {
                    // 查询数据库，看看这个用户是否存在
                    Map<String, String> user = new HashMap<>();
                    user.put("userId", userId);
                    user.put("userPwd", passWord);
                    if (DQLUtils.login(user)) { //用户存在
                        JOptionPane.showMessageDialog(jf, "登录成功！");
                        try {
                            new LibraryBodyFrame().initUI(new User(userId, passWord));
                        } catch (IOException ioException) {
                            ioException.printStackTrace();
                        }
                        //这里在用户进行登录的时候，只传进去了一个”虚拟“的用户
                        //这是一个残缺的用户，只有密码和用户名
                        //所以在执行一些操作的时候还要和数据库进行通讯查询是否有权限。
                        //【待改进】
                        jf.dispose();
                    } else { //用户不存在或者密码错误
                        JOptionPane.showMessageDialog(jf, "用户不存在或者密码错误");
                        uField.setText("");
                        pFiled.setText("");
                    }
                }
            }
        });

        signUp.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    new signUpFrame().initUI();
                } catch (IOException ioException) {
                    ioException.printStackTrace();
                }
                jf.dispose();
            }
        });

        vBox.add(Box.createVerticalStrut(110));
        vBox.add(uBox);
        vBox.add(Box.createVerticalStrut(50));
        vBox.add(pBox);
        vBox.add(Box.createVerticalStrut(80));
        vBox.add(bBox);

        bgp.add(vBox);

        jf.add(bgp);
        jf.setVisible(true);
        jf.setResizable(false);
    }

    private static void InitGlobalFont(Font font) {
        FontUIResource fontRes = new FontUIResource(font);
        for (Enumeration<Object> keys = UIManager.getDefaults().keys();
             keys.hasMoreElements(); ) {
            Object key = keys.nextElement();
            Object value = UIManager.get(key);
            if (value instanceof FontUIResource) {
                UIManager.put(key, fontRes);
            }
        }
    }

    public static void main(String[] args) {
        try {
            new LoginFrame().initUI();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
