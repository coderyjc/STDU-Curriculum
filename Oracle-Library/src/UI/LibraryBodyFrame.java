package UI;

import Components.*;
import Components.Dialog.AboutDialog;
import Components.Dialog.ChangePwdDialog;
import Domain.User;

import javax.swing.*;
import javax.swing.event.TreeSelectionEvent;
import javax.swing.event.TreeSelectionListener;
import javax.swing.tree.DefaultMutableTreeNode;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * @author Jingcun Yan
 */
public class LibraryBodyFrame {

    private final JFrame jf = new JFrame();

    final int WIDTH = 1400;
    final int HEIGHT = 800;

    public void initUI(User user) {
        jf.setTitle("欢迎你，" + user.getUserName());
        jf.setBounds((Toolkit.getDefaultToolkit().getScreenSize().width - WIDTH)/2, (Toolkit.getDefaultToolkit().getScreenSize().height - HEIGHT)/2, WIDTH, HEIGHT);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

        // 菜单栏
        JMenuBar menuBar = new JMenuBar();
        menuBar.setBackground(new Color(238, 238, 238));
        JMenu jMenu = new JMenu("设置");
        JMenuItem m3 = new JMenuItem("修改密码");
        JMenuItem m1 = new JMenuItem("切换账号");
        JMenuItem m2 = new JMenuItem("退出程序");

        // 切换账号监听
        m1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    new LoginFrame().initUI();
                    jf.dispose();
                } catch (Exception ex) {
                    ex.printStackTrace();
                }
            }
        });

        // 退出程序监听
        m2.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                System.exit(0);
            }
        });

        // 修改密码监听
        m3.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 修改密码
                new ChangePwdDialog(user, jf, "修改密码", true, new ActionListenerCallBack() {
                    // 回调函数，执行成功的情况下调用
                    @Override
                    public void hasDone(Object obj) {
                        try {
                            new LoginFrame().initUI();
                        } catch (Exception exception) {
                            exception.printStackTrace();
                        }
                        jf.dispose();
                    }
                });
            }
        });

        jMenu.add(m3);
        jMenu.add(m1);
        jMenu.add(m2);
        menuBar.add(jMenu);

        JMenuItem aboutMenu = new JMenuItem("关于");
        jMenu.add(aboutMenu);
        aboutMenu.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new AboutDialog(jf, "关于", true).setVisible(true);
            }
        });

        // 添加到frame中
        jf.setJMenuBar(menuBar);

        // 分割面板
        JSplitPane jsp = new JSplitPane();

        //支持连续布局
        jsp.setContinuousLayout(true);
        jsp.setDividerLocation(150);
        jsp.setDividerSize(7);

        // 左侧操作树
        DefaultMutableTreeNode root = new DefaultMutableTreeNode("图书馆管理");
        DefaultMutableTreeNode bookManage = new DefaultMutableTreeNode("所有图书");
        root.add(bookManage);
        DefaultMutableTreeNode guessYouLike = new DefaultMutableTreeNode("图书推荐");
        root.add(guessYouLike);
        DefaultMutableTreeNode userManage = new DefaultMutableTreeNode("用户管理");
        DefaultMutableTreeNode recordManage = new DefaultMutableTreeNode("借还记录");
        if(user.getUserType() == 0) {
            root.add(userManage);
            root.add(recordManage);
        }

        DefaultMutableTreeNode lentManage = new DefaultMutableTreeNode("借阅管理");
        root.add(lentManage);

        Color color = new Color(255,255,255);
        JTree tree = new JTree(root);

        tree.setBackground(color);
        //设置当前tree默认选中图书管理
        tree.setSelectionRow(2);
        tree.addTreeSelectionListener(new TreeSelectionListener() {
            //当条目选中变化后，这个方法会执行
            @Override
            public void valueChanged(TreeSelectionEvent e) {
                //得到当前选中的结点对象
                Object lastPathComponent = e.getNewLeadSelectionPath().getLastPathComponent();

                if (userManage.equals(lastPathComponent)){
                    jsp.setRightComponent(new UserTableComponent(jf, user));
                    jsp.setDividerLocation(150);
                }
                if (bookManage.equals(lastPathComponent)){
                    jsp.setRightComponent(new BookTableComponent(jf, user));
                    jsp.setDividerLocation(150);
                }
                if(lentManage.equals(lastPathComponent)){
                    jsp.setRightComponent(new BorrowTableComponent(jf, user));
                    jsp.setDividerLocation(150);
                }
                if (recordManage.equals(lastPathComponent)){
                    jsp.setRightComponent(new RecordComponent(jf, user));
                    jsp.setDividerLocation(150);
                }
                if(guessYouLike.equals(lastPathComponent)){
                    jsp.setRightComponent(new GuessYouLikeComponent(jf, user));
                    jsp.setDividerLocation(150);
                }
            }
        });

        // 左右的栏目显示
        jsp.setLeftComponent(tree);
        jsp.setRightComponent(new BookTableComponent(jf, user));

        jf.add(jsp);
        jf.setResizable(false);
        jf.setVisible(true);
    }
}
