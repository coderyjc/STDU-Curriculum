package Components;

import Utils.DBUtils.DBUtil;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Arrays;
import java.util.Vector;

public class BookTableComponent extends Box {

    final int WIDTH = 800;
    final int HEIGHT = 750;

    JFrame jf;
    private JTable table;
    private Object[][] obj = null;
    Vector<Vector<Object>> td =  new Vector<>();

    public BookTableComponent(JFrame jf) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        //----这个功能应该是管理员才有的，读者的功能应该只有借阅和还书
        //----添加图书，修改图书，删除图书的按钮

        JPanel btnPanel = new JPanel();
        btnPanel.setOpaque(false); // 设置透明度
        btnPanel.setMaximumSize(new Dimension(WIDTH,80));
        btnPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));

        JButton addButton = new JButton("添加");
        JButton updButton = new JButton("修改");
        JButton delButton = new JButton("删除");

        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 添加图书信息
                new AddBookDialog(jf, "添加图书", true, new ActionListenerCallBack() {
                    @Override
                    public void hasDone(Object obj) {
                        /*
                            问题根本没有解决。我只是画出了一个表格的样子，但没有真正实现表格的动态刷新。
                            这个问题先这样放下吧，等我画完了整体框架再用表格模型试试。
                         */
                        table = null;
                        requestData(); //获取信息并刷新表格
                    }
                }).setVisible(true);
            }
        });

        updButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 修改图书信息

            }
        });

        delButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //删除图书信息

            }
        });

        btnPanel.add(addButton);
        btnPanel.add(updButton);
        btnPanel.add(delButton);

        this.add(btnPanel);

        Object[] columnNames = {"编号", "书名", "作者", "简介", "价格", "库存", "借出"};

        requestData();
        JTable table = new JTable(obj, columnNames);
        JScrollPane jsp = new JScrollPane(table);
        this.add(jsp);
    }

    public void requestData(){

        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from books";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                String id = rs.getString("id");
                String name = rs.getString("name");
                String author = rs.getString("author");
                String description = rs.getString("description");
                String price = rs.getString("price");
                String stock = rs.getString("stock");
                String lent = rs.getString("lent");
                temp.add(id); temp.add(name); temp.add(author); temp.add(description);
                temp.add(price); temp.add(stock); temp.add(lent);
                td.add(temp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps, rs);
        }

        obj = new Object[td.size()][7];
        int j = 0;
        for(Vector vector : td){
            for(int i = 0; i < 7; i ++)
                obj[j][i] = vector.get(i);
            j++;
        }
    }

}
