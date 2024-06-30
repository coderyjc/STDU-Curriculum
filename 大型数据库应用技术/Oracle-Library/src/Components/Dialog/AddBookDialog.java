/**
 * @Author Jingcun Yan
 * @Date 12:32 2020/11/14
 * @Description
 */

package Components.Dialog;

import Components.ActionListenerCallBack;
import Components.Panel.BackgroundPanel;
import Domain.Book;
import Utils.DBUtils.DMLUtils;
import Utils.ScreenUtils;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

/**
 * 添加图书的对话框
 * @author Jingcun Yan
 */
public class AddBookDialog extends JDialog {

    final int WIDTH = 500;
    final int HEIGHT = 650;

    public AddBookDialog(JFrame jf, String title, boolean isModel, ActionListenerCallBack listener) {
        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth()-WIDTH)/2,(ScreenUtils.getScreenHeight()-HEIGHT)/2,WIDTH,HEIGHT);
        BackgroundPanel bgp = null;
        try {
            bgp = new BackgroundPanel(ImageIO.read(getClass().getResource("/imgs/addbook.png")));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 垂直的箱子，存放label和textField
        Box vBox = Box.createVerticalBox();

        // ISBN
        Box iBox = Box.createHorizontalBox();
        JLabel iLabel = new JLabel("I S B N");
        JTextField iField = new JTextField(15);
        iBox.add(iLabel);
        iBox.add(Box.createHorizontalStrut(20));
        iBox.add(iField);

        // 书籍名称
        Box nBox = Box.createHorizontalBox();
        JLabel nLabel = new JLabel("书籍名称");
        JTextField nField = new JTextField(15);
        nBox.add(nLabel);
        nBox.add(Box.createHorizontalStrut(20));
        nBox.add(nField);

        // 书籍作者
        Box aBox = Box.createHorizontalBox();
        JLabel aLabel = new JLabel("书籍作者");
        JTextField aField = new JTextField(15);

        aBox.add(aLabel);
        aBox.add(Box.createHorizontalStrut(20));
        aBox.add(aField);

        //价格
        Box pBox = Box.createHorizontalBox();
        JLabel pLabel = new JLabel("书籍价格");
        JTextField pField = new JTextField(15);

        pBox.add(pLabel);
        pBox.add(Box.createHorizontalStrut(20));
        pBox.add(pField);

        // 类型

        Box tBox = Box.createHorizontalBox();
        JLabel tLabel = new JLabel("书籍类型");
        JComboBox<String> tComboBox = new JComboBox<>(new String[]{
                "IT", "小说", "心理学", "古籍", "医学", "生活", "传记"
        });

        tBox.add(tLabel);
        tBox.add(Box.createHorizontalStrut(20));
        tBox.add(tComboBox);

        //按钮
        Box bBox = Box.createHorizontalBox();
        JButton addButton = new JButton("添加");
        JButton backButton = new JButton("返回");

        bBox.add(addButton);
        bBox.add(Box.createHorizontalStrut(100));
        bBox.add(backButton);

        //监听按钮
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                if("".equals(nField.getText()) || "".equals(pField.getText()) || "".equals(iField.getText())
                        || "".equals(aField.getText())){
                    JOptionPane.showMessageDialog(jf, "请把表格填完整！");
                    return;
                }

                boolean result = DMLUtils.addBook(new Book(
                        iField.getText().trim(),
                        nField.getText().trim(),
                        Double.parseDouble( pField.getText().trim()),
                        aField.getText().trim(),
                        0,
                        String.valueOf(tComboBox.getSelectedIndex() + 1)
                ));

                if (result) {
                    JOptionPane.showMessageDialog(jf, "添加成功");
                    nField.setText("");
                    iField.setText("");
                    pField.setText("");
                    aField.setText("");
                    listener.hasDone(null);
                } else {
                    JOptionPane.showMessageDialog(jf, "添加失败");
                }
            }
        });

        // 返回按钮，直接关闭这个窗口
        backButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });


        vBox.add(Box.createVerticalStrut(100));
        vBox.add(iBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(nBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(aBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(pBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(tBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(bBox);

        //为了左右有间距，在vBox外层封装一个水平的Box，添加间隔
        Box hBox = Box.createHorizontalBox();
        hBox.add(Box.createHorizontalStrut(20));
        hBox.add(vBox);
        hBox.add(Box.createHorizontalStrut(20));

        bgp.add(hBox);
        this.add(bgp);
    }

}
