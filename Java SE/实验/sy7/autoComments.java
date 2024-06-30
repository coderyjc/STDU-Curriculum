import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class autoComments{
    public static void main(String[] args) {
        JFrame jf = new JFrame();
        JPanel jp = new JPanel();
        jf.setSize(400, 300);

        jp.add(Box.createVerticalStrut(20));

        Box vBox = Box.createVerticalBox(); //整体的垂直布局

        Box scoreBox = Box.createHorizontalBox();

        //分数文本输入
        JTextField sField = new JTextField(10);
        sField.setFont(new Font(null, Font.PLAIN, 22));
        scoreBox.add(sField);
        vBox.add(scoreBox);
        vBox.add(Box.createVerticalStrut(30));

        // 分数提交
        JButton sButton = new JButton("提交");
        sButton.setFont(new Font(null, Font.PLAIN, 18));
        vBox.add(sButton);
        vBox.add(Box.createVerticalStrut(10));

        // 显示结果
        Box rsBox = Box.createHorizontalBox();
        JLabel rst = new JLabel("输入分数");
        rsBox.add(rst);
        rst.setFont(new Font(null, Font.PLAIN, 18));
        vBox.add(Box.createVerticalStrut(20));
        vBox.add(rsBox);

        sButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(sField.getText().trim().equals("")){
                    rst.setText("文本不能为空");
                }else {
                    int score = Integer.parseInt(sField.getText().trim());
                    if(score >= 90 && score <= 100) rst.setText("成绩优秀，继续保持");
                    else if(score <= 89 && score >= 80) rst.setText("成级良好，再接再厉");
                    else rst.setText("分数不在判断区间");
                }
            }
        });

        jp.add(Box.createVerticalStrut(20));
        jp.add(vBox);
        jf.add(jp);
        jf.setVisible(true);
        jf.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
        jf.setResizable(false);
        jf.setLocationRelativeTo(null);
    }
}