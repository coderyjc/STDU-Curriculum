package Components;

import Domain.Book;
import Utils.DBUtils.DMLUtils;
import Utils.RealPath;
import Utils.ScreenUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.IOException;

public class UpdateBookDialog extends JDialog {

    final int WIDTH = 500;
    final int HEIGHT = 450;

    public UpdateBookDialog(String ISBN, JFrame jf, String title, boolean isModel, ActionListenerCallBack listener) {
        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth() - WIDTH) / 2, (ScreenUtils.getScreenHeight() - HEIGHT) / 2, WIDTH, HEIGHT);
        BackgroundPanel bgp = null;
        try {
            bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("updateBook.png"))));
        } catch (IOException e) {
            e.printStackTrace();
        }


        // 大Box，放置一行一行的 box
        Box vBox = Box.createVerticalBox();

        // 书籍的ISBN号
        Box iBox = Box.createHorizontalBox();
        JLabel iLabel = new JLabel("I S B N");
        JTextField iField = new JTextField(15);
        iBox.add(iLabel);
        iBox.add(Box.createHorizontalStrut(20));
        iBox.add(iField);
        iField.setText(ISBN);
        // 要更改的项目
        Box cBox = Box.createHorizontalBox();
        JLabel cLabel = new JLabel("要更改的项目");
        JComboBox<String> jcbItem = new JComboBox<>(new String[]{
                "书名", "价格", "作者", "库存", "简介"
        });
        cBox.add(cLabel);
        cBox.add(Box.createHorizontalStrut(20));
        cBox.add(jcbItem);

        // 更改后的值
        Box uBox = Box.createHorizontalBox();
        JLabel uLabel = new JLabel("更改后");
        JTextField uField = new JTextField(15);
        uBox.add(uLabel);
        uBox.add(Box.createHorizontalStrut(20));
        uBox.add(uField);

        //确认/返回 按钮
        Box bBox = Box.createHorizontalBox();
        JButton cButton = new JButton("确认");
        JButton lButton = new JButton("取消");
        bBox.add(cButton);
        bBox.add(Box.createHorizontalStrut(100));
        bBox.add(lButton);

        //确认
        cButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                boolean rst = false;
                Book temp = new Book(iField.getText().trim());
                int item = jcbItem.getSelectedIndex();
                switch (item){
                    //进行相关信息的更新
                    case 0 : rst = DMLUtils.updateBook(temp, "name",uField.getText().trim()); break;
                    case 1 : rst = DMLUtils.updateBook(temp, "price",uField.getText().trim()); break;
                    case 2 : rst = DMLUtils.updateBook(temp, "author",uField.getText().trim()); break;
                    case 3 : rst = DMLUtils.updateBook(temp, "stock",uField.getText().trim()); break;
                    case 4 : rst = DMLUtils.updateBook(temp, "description",uField.getText().trim()); break;
                }
                if(rst){
                    JOptionPane.showMessageDialog(jf, "修改成功");
                    listener.hasDone(null);
                }
            }
        });

        //取消
        lButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        vBox.add(Box.createVerticalStrut(100));
        vBox.add(iBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(cBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(uBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(bBox);

        Box tBox = Box.createHorizontalBox();
        tBox.add(vBox);
        tBox.add(Box.createHorizontalStrut(20));
        bgp.add(tBox);
        tBox.add(Box.createHorizontalStrut(20));
        this.add(bgp);
    }
}