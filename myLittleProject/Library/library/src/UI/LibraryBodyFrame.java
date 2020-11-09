package UI;

import Components.BackgroundPanel;
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






        jf.add(bgp);
        jf.setResizable(false);
        jf.setVisible(true);
    }
}
