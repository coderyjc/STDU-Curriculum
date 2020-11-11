package UI;

import Components.BackgroundPanel;
import Components.BookTableComponent;
import Domain.User;
import Utils.RealPath;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class LibraryBodyFrame {

    private JFrame jf = new JFrame();

    final int WIDTH = 1200;
    final int HEIGHT = 800;

    public void initUI(User user) throws IOException {
        jf.setTitle("欢迎 " + user.getUserName());
        jf.setBounds((Toolkit.getDefaultToolkit().getScreenSize().width - WIDTH)/2, (Toolkit.getDefaultToolkit().getScreenSize().height - HEIGHT)/2, WIDTH, HEIGHT);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        BackgroundPanel bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("manage.png"))));
        bgp.setBounds(0, 0, WIDTH, HEIGHT);

        //设置分割面板
//        JSplitPane sp = new JSplitPane();

        //支持连续布局
//        sp.setContinuousLayout(true);
//        sp.setDividerLocation(150);
//        sp.setDividerSize(7);

        //分割面板右侧布局
//        sp.setRightComponent(new BookTableComponent(jf));

//        jf.add(sp);

        bgp.add(new BookTableComponent(jf));

        jf.add(bgp);
        jf.setResizable(false);
        jf.setVisible(true);
    }

}
