package Components;

import Components.Dialog.AddBookDialog;
import Components.Dialog.BorrowBookDialog;
import Components.Dialog.UpdateBookDialog;
import Domain.Book;
import Domain.User;
import Utils.DBUtils.DBUtil;
import Utils.DBUtils.DMLUtils;

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

/**
 * 主页面上，树形结构的右半边
 * @author Jingcun Yan
 */
public class BookTableComponent extends Box {

    final int WIDTH = 1000;

    JFrame jf;
    Vector<Vector> td = new Vector<>();
    DefaultTableModel model;

    public BookTableComponent(JFrame jf, User user) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        Object[] columnNames = {"ISBN", "书名", "作者", "价格", "是否借出"};

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

        this.add(Box.createVerticalStrut(15));

        // 书籍搜索框
        JPanel searchPanel = new JPanel();
        searchPanel.setMaximumSize(new Dimension(WIDTH, 70));
        searchPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        JLabel sLabel = new JLabel("书籍查询 按照");
        JTextField sField = new JTextField(20);
        JButton sButton = new JButton("查询");
        JComboBox<String> jcb_column = new JComboBox<>(new String[]{
                "书名", "ISBN", "作者"
        });

        sButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if("".equals(sField.getText().trim())){
                    JOptionPane.showMessageDialog(jf, "请输入查询内容");
                }else{
                    model.getDataVector().clear();
                    switch (jcb_column.getSelectedIndex()){
                        case 0 : searchBook("name", sField.getText().trim()); break;
                        case 1 : searchBook("ISBN", sField.getText().trim()); break;
                        case 2 : searchBook("author", sField.getText().trim()); break;
                        default:
                    }
                    if(td.isEmpty()){
                        JOptionPane.showMessageDialog(jf, "查找失败");
                        requestData();
                    } else {
                        JOptionPane.showMessageDialog(jf, "查询成功");
                    }
                }
            }
        });

        searchPanel.add(sLabel);
        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(jcb_column);
        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(sField);
        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(sButton);
        this.add(searchPanel);

        this.add(Box.createVerticalStrut(10));

        //----这个功能应该是管理员才有的，读者的功能应该只有借阅和还书
        //----添加图书，修改图书，删除图书的按钮

        JPanel btnPanel = new JPanel();
        btnPanel.setMaximumSize(new Dimension(WIDTH,80));
        btnPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));

        JButton addButton = new JButton("添加");
        JButton updButton = new JButton("修改");
        JButton delButton = new JButton("删除选中行");


        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 添加图书信息
                new AddBookDialog(jf, "添加图书", true, new ActionListenerCallBack() {
                    @Override
                    public void hasDone(Object obj) {
                        model.getDataVector().clear();
                        requestData(); //获取信息并刷新表格
                    }
                }).setVisible(true);
            }
        });

        updButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String defaultText = "";
                if(table.getSelectedRow() != -1) {
                    defaultText = (String) td.get(table.getSelectedRow()).get(0);
                }
                // 修改图书信息
                new UpdateBookDialog(defaultText
                        ,jf, "修改图书", true, new ActionListenerCallBack() {
                    @Override
                    public void hasDone(Object obj) {
                        model.getDataVector().clear();
                        requestData(); //获取信息并刷新表格
                    }
                }).setVisible(true);
            }
        });

        delButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //删除图书信息
                int selected = table.getSelectedRow();
                if(selected == -1){
                    JOptionPane.showMessageDialog(jf, "当前未选中行");
                } else {
                    int click = JOptionPane.showConfirmDialog(jf, "确定删除选中行？");
                    if(click == JOptionPane.YES_OPTION){
                        //执行图书删除业务
                        boolean succ = DMLUtils.deleteBook(new Book((String) td.get(selected).get(0)));
                        model.getDataVector().clear();
                        requestData(); //获取信息并刷新表格
                        if(succ){
                            JOptionPane.showMessageDialog(jf, "删除成功");
                        }else {
                            JOptionPane.showMessageDialog(jf, "删除失败");
                        }
                    }
                }
            }
        });

        //借阅按钮
        JButton borrowButton = new JButton("借阅图书");
        borrowButton.setSize(150, 100);

        borrowButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(table.getSelectedRow() == -1){
                    JOptionPane.showMessageDialog(jf, "请选中一本图书");
                } else {
                    Book toBorrow = new Book(
                            (String) td.get(table.getSelectedRow()).get(0),
                            (String) td.get(table.getSelectedRow()).get(1),
                            Double.parseDouble((String) td.get(table.getSelectedRow()).get(3)) ,
                            (String) td.get(table.getSelectedRow()).get(2),
                            Integer.parseInt((String) td.get(table.getSelectedRow()).get(4))
                    );
                    new BorrowBookDialog(toBorrow, user, jf, "Borrow Book", true);
                    model.getDataVector().clear();
                    requestData();
                }
            }
        });

        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(borrowButton);
        btnPanel.add(addButton);
        btnPanel.add(Box.createHorizontalStrut(10));
        btnPanel.add(updButton);
        btnPanel.add(Box.createHorizontalStrut(10));
        btnPanel.add(delButton);

        //管理员权限： 对书籍的添加，修改和删除
        if(user.getUserType() == 0){
            this.add(btnPanel);
            this.add(Box.createVerticalStrut(10));
        }

        JScrollPane jsp = new JScrollPane(table);
        this.add(jsp);
        requestData();
    }

    public void requestData(){

        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from t_book";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(rs.getString("isbn"));
                temp.add( rs.getString("name"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("price"));
                temp.add(rs.getString("instock"));
                td.add(temp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps, rs);
        }
        model.fireTableDataChanged();
    }


    /**
     *  使用查询更新当前的数据向量
     * @param column 要查询的字段
     * @param text 查询的文本
     */
    public void searchBook(String column, String text){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from t_book where " + column + " like ?";
            ps = conn.prepareStatement(sql);
            String even = "%" + text + "%";
            ps.setString(1, even);
            rs = ps.executeQuery();
            td.clear();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(rs.getString("isbn"));
                temp.add( rs.getString("name"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("price"));
                temp.add(rs.getString("instock"));
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
