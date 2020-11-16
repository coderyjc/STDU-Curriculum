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
 * @author Jingcun Yan
 */
public class ChangePwdDialog extends JDialog {

    final int WIDTH = 400;
    final int HEIGHT = 430;

    public ChangePwdDialog(User user, JFrame jf, String title, boolean isModel, ActionListenerCallBack listener){
        super(jf, title, isModel);

        this.setBounds((ScreenUtils.getScreenWidth()-WIDTH)/2,(ScreenUtils.getScreenHeight()-HEIGHT)/2,WIDTH,HEIGHT);
        BackgroundPanel bgp = null;
        try {
            bgp = new BackgroundPanel(ImageIO.read(new File(RealPath.realPath("changePwd.png"))));
        } catch (IOException e) {
            e.printStackTrace();
        }

        // 竖直布局
        Box vBox = Box.createVerticalBox();

        //旧密码
        Box oBox = Box.createHorizontalBox();
        oBox.add(new JLabel("  旧密码"));
        oBox.add(Box.createHorizontalStrut(20));
        JPasswordField oField = new JPasswordField(15);
        oBox.add(oField);

        //新密码
        Box nBox = Box.createHorizontalBox();
        nBox.add(new JLabel("  新密码"));
        nBox.add(Box.createHorizontalStrut(20));
        JPasswordField nField = new JPasswordField(15);
        nBox.add(nField);


        //确认密码
        Box cBox = Box.createHorizontalBox();
        cBox.add(new JLabel("确认密码"));
        cBox.add(Box.createHorizontalStrut(20));
        JPasswordField cField = new JPasswordField(15);
        cBox.add(cField);

        //确认和取消按钮
        Box bBox = Box.createHorizontalBox();
        JButton confirmButton = new JButton("确认");
        JButton cancelButton = new JButton("取消");
        bBox.add(confirmButton);
        bBox.add(Box.createHorizontalStrut(50));
        bBox.add(cancelButton);

        // 确认和取消按钮的监听器
        confirmButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String old = new String(oField.getPassword());
                String newPwd = new String(nField.getPassword());
                String rePwd = new String(cField.getPassword());
                //旧密码错误判断
                if(!old.equals(user.getUserPwd())){
                    JOptionPane.showMessageDialog(jf, "旧密码错误");
                // 空值判断
                }
                else if("".equals(old) || "".equals(newPwd) || "".equals(rePwd)){
                    JOptionPane.showMessageDialog(jf, "密码不能为空");
                // 两次密码一致判断
                } else if(!newPwd.equals(rePwd)){
                    JOptionPane.showMessageDialog(jf, "新密码与重复密码不一致");
                // 新旧密码一致判断
                } else if(old.equals(newPwd)){
                    JOptionPane.showMessageDialog(jf, "新旧密码一致");
                //更新数据库，并提示重新登录
                }else{
                    if(DMLUtils.updateUser(user, "password", newPwd)){
                        JOptionPane.showMessageDialog(jf, "密码修改成功，请重新登录");
                        // 回调函数，关闭界面并重新登陆
                        listener.hasDone(null);
                    }
                }
            }
        });

        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dispose();
            }
        });

        //添加进去
        vBox.add(Box.createVerticalStrut(40));
        vBox.add(oBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(nBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(cBox);
        vBox.add(Box.createVerticalStrut(30));
        vBox.add(bBox);

        bgp.add(vBox);
        this.add(bgp);
        this.setVisible(true);
    }

}