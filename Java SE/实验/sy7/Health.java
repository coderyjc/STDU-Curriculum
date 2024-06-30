import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Health{
    public static void main(String[] args) {
        JFrame jf = new JFrame();
        jf.setSize(400, 250);
        JPanel jPanel = new JPanel(); //主要窗口
        Box vBox = Box.createVerticalBox();
        //身高
        Box hBox = Box.createHorizontalBox();
        hBox.add(new JLabel("身高（米）"));
        JTextField hField = new JTextField(10);
        hBox.add(hField);

        //体锺
        Box wBox = Box.createHorizontalBox();
        wBox.add(new JLabel("体重（公斤）"));
        JTextField wField = new JTextField(10);
        wBox.add(wField);

        //按钮和 结果
        Box rBox = Box.createHorizontalBox();
        JButton rButton = new JButton("计算");
        JLabel rLabel = new JLabel("");
        rBox.add(rButton);
        rBox.add(Box.createHorizontalStrut(20));
        rBox.add(rLabel);

        // 按钮监听器
        rButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(hField.getText().trim().equals("") || wField.getText().trim().equals(""))
                    rLabel.setText("请输入完整");
                else {
                    // 获取数值
                    double height = Double.parseDouble(hField.getText().trim());
                    double weight = Double.parseDouble(wField.getText().trim());
                    //计算
                    double rst = weight / height / height;
                    if(rst < 18) rLabel.setText("偏瘦");
                    else if(rst >= 18 && rst <= 25) rLabel.setText("正常");
                    else if(rst > 25 && rst < 27) rLabel.setText("超重");
                    else if(rst >= 27) rLabel.setText("肥胖");
                }
            }
        });


        vBox.add(Box.createVerticalStrut(20));
        vBox.add(hBox);
        vBox.add(Box.createVerticalStrut(20));
        vBox.add(wBox);
        vBox.add(Box.createVerticalStrut(20));
        vBox.add(rBox);
        jPanel.add(vBox);
        jf.add(jPanel);
        
        jf.setVisible(true);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jf.setResizable(false);
        jf.setLocationRelativeTo(null);
    }
}