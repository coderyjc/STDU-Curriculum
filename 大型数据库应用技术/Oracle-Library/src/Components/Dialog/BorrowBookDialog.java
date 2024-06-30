/**
 * @Author Jingcun Yan
 * @Date 12:32 2020/11/15
 * @Description
 */

package Components.Dialog;

import Components.Panel.BackgroundPanel;
import Domain.Book;
import Domain.User;
import Utils.DBUtils.DMLUtils;
import Utils.ScreenUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * 借书的对话框
 * @author JingcunYan
 */
public class BorrowBookDialog extends JDialog {

    final int WIDTH = 500;
    final int HEIGHT = 350;

    public BorrowBookDialog(Book book, User user, JFrame jf, String title, boolean isModel){

        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth() - WIDTH) / 2, (ScreenUtils.getScreenHeight() - HEIGHT) / 2, WIDTH, HEIGHT);
        BackgroundPanel bgp = null;
        try {
            bgp = new BackgroundPanel(ImageIO.read(getClass().getResource("/imgs/borrowBook.png")));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 整个垂直界面的箱子
        Box vBox = Box.createVerticalBox();

        // 确认的箱子
        Box conBox = Box.createHorizontalBox();
        JLabel confirmLabel = new JLabel("确定借阅" + book.getBookName() + " ? ");
        conBox.add(confirmLabel);

        // 确认按钮
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
                boolean suc = DMLUtils.borrowBook(book, user);
                if(suc){
                    JOptionPane.showMessageDialog(jf, "借阅成功");
                    DMLUtils.writeLog(user.getUserId(), book.getBookISBN(), 0);
                }else{
                    JOptionPane.showMessageDialog(jf, "借阅失败");
                }
                dispose();
            }
        });

        // 取消按钮
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
