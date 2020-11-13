package UI;

import Components.BookTableComponent;
import Domain.User;

import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import java.awt.*;

public class LibraryBodyFrame {

    private JFrame jf = new JFrame();

    final int WIDTH = 1200;
    final int HEIGHT = 800;

    public void initUI(User user) {
        jf.setTitle("欢迎 " + user.getUserName());
        jf.setBounds((Toolkit.getDefaultToolkit().getScreenSize().width - WIDTH)/2, (Toolkit.getDefaultToolkit().getScreenSize().height - HEIGHT)/2, WIDTH, HEIGHT);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        // 分割面板
        JSplitPane jsp = new JSplitPane();

        //支持连续布局
        jsp.setContinuousLayout(true);
        jsp.setDividerLocation(150);
        jsp.setDividerSize(7);

        // 左侧操作树
        DefaultMutableTreeNode root = new DefaultMutableTreeNode("图书馆管理");
//        DefaultMutableTreeNode borrowManage = new DefaultMutableTreeNode("借阅/归还");
        DefaultMutableTreeNode bookManage = new DefaultMutableTreeNode("图书管理");
        DefaultMutableTreeNode userManage = new DefaultMutableTreeNode("用户管理");
        DefaultMutableTreeNode lentManage = new DefaultMutableTreeNode("借阅管理");

//        root.add(borrowManage);
        root.add(bookManage);
        root.add(userManage);
        root.add(lentManage);

        Color color = new Color(255,255,255);
        JTree tree = new JTree(root);

        tree.setBackground(color);
        //设置当前tree默认选中图书管理
        tree.setSelectionRow(1);
        tree.addTreeSelectionListener(new TreeSelectionListener() {
            //当条目选中变化后，这个方法会执行
            @Override
            public void valueChanged(TreeSelectionEvent e) {
                //得到当前选中的结点对象
                Object lastPathComponent = e.getNewLeadSelectionPath().getLastPathComponent();

                if (userManage.equals(lastPathComponent)){
                    jsp.setRightComponent(new JLabel("这里进行用户管理..."));
                    jsp.setDividerLocation(150);
                }else if (bookManage.equals(lastPathComponent)){
                    jsp.setRightComponent(new BookTableComponent(jf, user));
                    jsp.setDividerLocation(150);
                }else{
                    jsp.setRightComponent(new JLabel("这里进行归还管理"));
                    jsp.setDividerLocation(150);
                }
            }
        });

        jsp.setLeftComponent(tree);
        jsp.setRightComponent(new BookTableComponent(jf, user));
        jf.add(jsp);
        jf.setResizable(false);
        jf.setVisible(true);
    }
}
