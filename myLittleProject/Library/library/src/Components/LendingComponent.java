package Components;


import javax.swing.*;
import java.awt.*;

public class LendingComponent extends Box {
    final int WIDTH = 1000;
    final int HEIGHT = 750;

    JFrame jf;

    public LendingComponent(JFrame jf) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        JPanel btnPanel = new JPanel();
        btnPanel.setMaximumSize(new Dimension(WIDTH, 100));
        btnPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        JButton borrowButton = new JButton("借阅图书");
        JButton returnButton = new JButton("归还图书");
        borrowButton.setSize(150, 100);
        returnButton.setSize(150, 100);
        btnPanel.add(borrowButton);
        btnPanel.add(returnButton);
        this.add(btnPanel);






    }
}
