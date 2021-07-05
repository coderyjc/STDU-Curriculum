/**
 * @Author JingcunYan
 * @Date 19:57 2020/11/15
 * @Description
 */

package Components;

import Components.Dialog.ReturnBookDialog;
import Domain.Book;
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
    JTable table;
    DefaultTableModel model;

    public BorrowTableComponent(JFrame jf, User user) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        Object[] columnNames = {"序号", "书籍ISBN", "书名", "作者", "借阅人", "账号", "借阅时间"};

        Vector columnName = new Vector<>();
        Collections.addAll(columnName, columnNames);
        model = new DefaultTableModel(td, columnName);
        table = new JTable(){
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
        table.setModel(model);
        table.setRowHeight(25);

        // 归还按钮
        JPanel lentPanel = new JPanel();
        lentPanel.setMaximumSize(new Dimension(WIDTH, 50));
        lentPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        JButton returnButton = new JButton("归还图书");
        returnButton.setSize(150, 100);
        lentPanel.add(returnButton);

        // 归还图书的监听器
        returnButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(table.getSelectedRow() == -1){
                    JOptionPane.showMessageDialog(jf, "请选中一本图书");
                } else {
                    Book toBorrow = new Book(
                            (String) td.get(table.getSelectedRow()).get(1),
                            (String) td.get(table.getSelectedRow()).get(2),
                            null , // book price
                            null ,
                            1,
                            null
                    );
                    new ReturnBookDialog(toBorrow, user, jf, "Return Book", true);
                    model.getDataVector().clear();
                    // 如果是管理员，那么可以requestData,如果不是，则只能通过筛选输出
                    if(user.getUserType() == 0){
                        requestData();
                    } else {
                        searchBorrow("u.id", user.getUserId());
                    }
                }
            }
        });

        this.add(lentPanel);

        this.add(Box.createVerticalStrut(20));

        // 这个查询按钮应是管理员才有的权限，在一个用户访问的时候应该显示他自己的借阅信息
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
                } else if (user.getUserType() != 0){
                    JOptionPane.showMessageDialog(jf, "非管理员无权查找");
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
                    if(user.getUserType() == 0){
                        requestData();
                    }else{
                        searchBorrow("u.id", user.getUserId());
                    }
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
        resizeColumnWidth();
    }


    public void requestData(){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select b.isbn, b.name as bookname, b.author, u.name as username, u.id, bo.datetime from t_user u, t_book b, t_borrowing bo where u.id = bo.id and bo.isbn = b.isbn order by datetime desc";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            int i = 1;
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(i++);
                temp.add(rs.getString("isbn"));
                temp.add(rs.getString("bookname"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("username"));
                temp.add(rs.getString("id"));
                temp.add(rs.getString("datetime"));
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
            String sql = "select b.isbn, b.name as bookname, b.author, u.name as username, u.id, bo.datetime from t_user u, t_book b, t_borrowing bo where u.id = bo.id and bo.isbn = b.isbn and " + column + " like ? order by datetime desc";
            ps = conn.prepareStatement(sql);
            String even = "%" + text + "%";
            ps.setString(1, even);
            rs = ps.executeQuery();
            td.clear();
            int i = 1;
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(i++);
                temp.add(rs.getString("isbn"));
                temp.add(rs.getString("bookname"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("username"));
                temp.add(rs.getString("id"));
                temp.add(rs.getString("datetime"));
                td.add(temp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(conn, ps, rs);
        }
        model.fireTableDataChanged();
    }

    public void resizeColumnWidth(){
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        table.getColumnModel().getColumn(0).setPreferredWidth(60);
        table.getColumnModel().getColumn(1).setPreferredWidth(170);
        table.getColumnModel().getColumn(2).setPreferredWidth(300);
        table.getColumnModel().getColumn(3).setPreferredWidth(200);
        table.getColumnModel().getColumn(4).setPreferredWidth(100);
        table.getColumnModel().getColumn(5).setPreferredWidth(150);
        table.getColumnModel().getColumn(6).setPreferredWidth(240);
    }
}
