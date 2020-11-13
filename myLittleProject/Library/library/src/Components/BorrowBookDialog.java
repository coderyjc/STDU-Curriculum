package Components;

import Utils.RealPath;
import Utils.ScreenUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.io.File;
import java.io.IOException;

public class BorrowBookDialog extends JDialog {

    final int WIDTH = 500;
    final int HEIGHT = 450;

    BorrowBookDialog( JFrame jf, String title, boolean isModel){
        super(jf, title, isModel);
        this.setBounds((ScreenUtils.getScreenWidth() - WIDTH) / 2, (ScreenUtils.getScreenHeight() - HEIGHT) / 2, WIDTH, HEIGHT);
        BackgroundPanel bgp = null;
        try {
            bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("borrowBook.png"))));
        } catch (IOException e) {
            e.printStackTrace();
        }




        this.add(bgp);
        this.setVisible(true);
    }

}
