/**
 * @Author JingcunYan
 * @Date 15:00 2020/11/16
 * @Description
 */

package Components.Dialog;

import Components.Panel.BackgroundPanel;
import Utils.RealPath;
import Utils.ScreenUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.io.File;
import java.io.IOException;

public class AboutDialog extends JDialog {

    final int WIDTH = 400;
    final int HEIGHT = 300;

    public AboutDialog(JFrame jf, String title, boolean isModel){
        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth() - WIDTH) / 2, (ScreenUtils.getScreenHeight() - HEIGHT) / 2, WIDTH, HEIGHT);
        BackgroundPanel bgp = null;

        try {
            bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("about.png"))));
        } catch (IOException e) {
            e.printStackTrace();
        }

        Box vBox = Box.createVerticalBox();

        JLabel titleLabel = new JLabel("图书馆管理系统V1.1");
        JLabel authorLabel  = new JLabel("作者：Jingcun Yan");
        JLabel dateLabel = new JLabel("时间：2020.11.15");

        vBox.add(Box.createVerticalStrut(50));
        vBox.add(titleLabel);
        vBox.add(Box.createVerticalStrut(10));
        vBox.add(authorLabel);
        vBox.add(Box.createVerticalStrut(10));
        vBox.add(dateLabel);

        bgp.add(vBox);
        this.add(bgp);
    }

}
