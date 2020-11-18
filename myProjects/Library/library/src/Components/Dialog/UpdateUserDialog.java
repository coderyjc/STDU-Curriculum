/**
 * @Author JingcunYan
 * @Date 0:38 2020/11/16
 * @Description
 */

package Components.Dialog;

import Components.ActionListenerCallBack;
import Components.Panel.BackgroundPanel;
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

/**
 * 管理员主动修改用户信息
 * @author Jingcun Yan
 */
public class UpdateUserDialog extends JDialog {

    final int WIDTH = 500;
    final int HEIGHT = 450;

    public UpdateUserDialog(String id, JFrame jf, String title, boolean isModel, ActionListenerCallBack listener ){
        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth() - WIDTH) / 2, (ScreenUtils.getScreenHeight() - HEIGHT) / 2, WIDTH, HEIGHT);
        BackgroundPanel bgp = null;

        try {
            bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("updateUser.png"))));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 大Box，放置一行一行的 box
        Box vBox = Box.createVerticalBox();

        // 用户的ID
        Box iBox = Box.createHorizontalBox();
        JLabel iLabel = new JLabel("I   D");
        JTextField iField = new JTextField(15);
        iBox.add(iLabel);
        iBox.add(Box.createHorizontalStrut(20));
        iBox.add(iField);
        iField.setText(id);

        // 要更改的项目
        Box cBox = Box.createHorizontalBox();
        JLabel cLabel = new JLabel("要更改的项目");
        JComboBox<String> jcbItem = new JComboBox<>(new String[]{
                "姓名", "类别", "性别", "电话", "密码"
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
                int item = jcbItem.getSelectedIndex();
                User user = new User(iField.getText().trim());
                switch (item){
                    //进行相关信息的更新
                    case 0: rst = DMLUtils.updateUser(user, "name", uField.getText().trim()); break;
                    case 1: rst = DMLUtils.updateUser(user, "type", uField.getText().trim()); break;
                    case 2: rst = DMLUtils.updateUser(user, "sex", uField.getText().trim()); break;
                    case 3: rst = DMLUtils.updateUser(user, "tel", uField.getText().trim()); break;
                    case 4: rst = DMLUtils.updateUser(user, "password", uField.getText().trim()); break;
                    default:
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
