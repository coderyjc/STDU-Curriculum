/**
 * @Author JingcunYan
 * @Date 19:57 2020/11/15
 * @Description
 */

package Components;

import Domain.User;
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
import java.util.Collections;
import java.util.Vector;

public class BorrowTableComponent extends Box {

    final int WIDTH = 1000;
    final int HEIGHT = 750;

    JFrame jf;
    Vector<Vector<Object>> td = new Vector<>();
    DefaultTableModel model;

    public BorrowTableComponent(JFrame jf, User user) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        Object[] columnNames = {"借阅人姓名", "书名", "作者", "借阅时间", "借阅人ID", "书籍ISBN"};

        Vector columnName = new Vector<>();
        Collections.addAll(columnName, columnNames);
        model = new DefaultTableModel(td, columnName);
        JTable table = new JTable(){
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
        table.setModel(model);
        table.setRowHeight(25);

        this.add(Box.createVerticalStrut(30));

        // 这个查询按钮应是管理元才有的权限，在一个用户访问的时候应该显示他自己的借阅信息
        // 所以如果是查询的话，直接不显示以姓名或者ID查询就行了
        JPanel searchPanel = new JPanel();
        searchPanel.setMaximumSize(new Dimension(WIDTH, 70));
        searchPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        JLabel sLabel = new JLabel("记录查询 按照");
        JTextField sField = new JTextField(20);
        JButton sButton = new JButton("查询");
        JComboBox<String> jcbColumn = new JComboBox<>(new String[]{
                "借阅人姓名", "借阅人ID", "书名", "ISBN", "作者"
        });


        // 监听用户查询信息
        sButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 查询
                if("".equals(sField.getText().trim())){
                    JOptionPane.showMessageDialog(jf, "请输入查询内容");
                } else if (user.getUserType() != 0 &&
                        (jcbColumn.getSelectedIndex() == 0 || jcbColumn.getSelectedIndex() == 1)){
                    JOptionPane.showMessageDialog(jf, "非管理员无权操作");
                    return;
                } else {
                    model.getDataVector().clear();
                    switch (jcbColumn.getSelectedIndex()){
                        case 0:searchBorrow("u.name", sField.getText().trim()); break;
                        case 1:searchBorrow("u.id", sField.getText().trim()); break;
                        case 2:searchBorrow("b.name", sField.getText().trim()); break;
                        case 3:searchBorrow("b.isbn", sField.getText().trim()); break;
                        case 4:searchBorrow("b.author", sField.getText().trim()); break;
                        default:
                    }
                }
                if(td.isEmpty()){
                    JOptionPane.showMessageDialog(jf, "查找失败");
                    requestData();
                } else {
                    JOptionPane.showMessageDialog(jf, "查询成功");
                }
            }
        });


        searchPanel.add(sLabel);
        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(jcbColumn);
        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(sField);
        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(sButton);
        this.add(searchPanel);

        this.add(Box.createVerticalStrut(10));

        JScrollPane jsp = new JScrollPane(table);
        this.add(jsp);

        // 如果是管理员，那么可以requestData,如果不是，则只能通过筛选输出
        if(user.getUserType() == 0){
            requestData();
        } else {
            searchBorrow("u.id", user.getUserId());
        }
        this.setVisible(true);
    }


    public void requestData(){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select u.name as username, b.name as bookname, b.author, bo.borrowdate, u.id, b.isbn from users u, books b, borrow bo where u.id = bo.userId and bo.bookId = b.ISBN";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(rs.getString("username"));
                temp.add(rs.getString("bookname"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("borrowdate"));
                temp.add(rs.getString("id"));
                temp.add(rs.getString("isbn"));
                td.add(temp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps, rs);
        }
        model.fireTableDataChanged();
    }

    public void searchBorrow(String column, String text){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select u.name as username, b.name as bookname, b.author, bo.borrowdate, u.id, b.isbn from users u, books b, borrow bo where u.id = bo.userId and bo.bookId = b.ISBN and " + column + " = ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1, text);
            rs = ps.executeQuery();
            td.clear();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(rs.getString("username"));
                temp.add(rs.getString("bookname"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("borrowdate"));
                temp.add(rs.getString("id"));
                temp.add(rs.getString("isbn"));
                td.add(temp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(conn, ps, rs);
        }
        model.fireTableDataChanged();
    }

}
