/**
 * @Author JingcunYan
 * @Date 16:26 2020/11/15
 * @Description
 */

package Components.Dialog;

import Components.Panel.BackgroundPanel;
import Domain.Book;
import Domain.User;
import Utils.DBUtils.DMLUtils;
import Utils.RealPath;
import Utils.ScreenUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class ReturnBookDialog extends JDialog {

    final int WIDTH = 500;
    final int HEIGHT = 350;

    public ReturnBookDialog(Book book, User user, JFrame jf, String title, boolean isModel){
        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth() - WIDTH) / 2, (ScreenUtils.getScreenHeight() - HEIGHT) / 2, WIDTH, HEIGHT);
        BackgroundPanel bgp = null;
        try {
            bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("returnBook.png"))));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 整个垂直界面的箱子
        Box vBox = Box.createVerticalBox();

        Box conBox = Box.createHorizontalBox();
        JLabel confirmLabel = new JLabel("确定归还" + book.getBookName() + " ? ");
        conBox.add(confirmLabel);

        Box bBox = Box.createHorizontalBox();
        JButton confirmButton = new JButton("确认");
        JButton cancelButton = new JButton("取消");
        bBox.add(confirmButton);
        bBox.add(Box.createHorizontalStrut(50));
        bBox.add(cancelButton);

        // 监听两个按钮
        confirmButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean suc = false;
                // 进行还书操作
                if(DMLUtils.returnBook(book, user)){
                    suc = true;
                }
                if(suc){
                    JOptionPane.showMessageDialog(jf, "书籍已归还");
                }else{
                    JOptionPane.showMessageDialog(jf, "还书失败");
                }
                dispose();
            }
        });

        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });


        vBox.add(Box.createVerticalStrut(60));
        vBox.add(conBox);
        vBox.add(Box.createVerticalStrut(60));
        vBox.add(bBox);

        bgp.add(vBox);
        this.add(bgp);
        this.setVisible(true);

    }

}
