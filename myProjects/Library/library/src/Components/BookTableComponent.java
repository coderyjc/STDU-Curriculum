package Components;

import Components.Dialog.AddBookDialog;
import Components.Dialog.BorrowBookDialog;
import Components.Dialog.UpdateBookDialog;
import Domain.Book;
import Domain.User;
import Utils.DBUtils.DBUtil;
import Utils.DBUtils.DMLUtils;
import Utils.DBUtils.DQLUtils;

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

    final int COLUMN_PER_PAGE = 18;

    JFrame jf;
    Vector<Vector> td = new Vector<>();
    JTable table;
    DefaultTableModel model;

    // 显示页面数据的参数
    public int totalPage ;
    public int currPage = 1;

    public BookTableComponent(JFrame jf, User user) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        Object[] columnNames = {"序号","ISBN", "书名", "作者", "类别", "价格", "是否借出"};

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
                        requestData(currPage);
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

        // 添加图书
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 添加图书信息
                new AddBookDialog(jf, "添加图书", true, new ActionListenerCallBack() {
                    @Override
                    public void hasDone(Object obj) {
                        model.getDataVector().clear();
                        requestData(currPage); //获取信息并刷新表格
                    }
                }).setVisible(true);
            }
        });

        // 更新图书
        updButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String defaultText = "";
                if(table.getSelectedRow() != -1) {
                    defaultText = (String) td.get(table.getSelectedRow()).get(1);
                }
                // 修改图书信息
                new UpdateBookDialog(defaultText
                        ,jf, "修改图书", true, new ActionListenerCallBack() {
                    @Override
                    public void hasDone(Object obj) {
                        model.getDataVector().clear();
                        requestData(1); //获取信息并刷新表格
                    }
                }).setVisible(true);
            }
        });

        // 删除图书
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
                        boolean succ = DMLUtils.deleteBook(new Book((String) td.get(selected).get(1)));
                        model.getDataVector().clear();
                        requestData(currPage); //获取信息并刷新表格
                        if(succ){
                            JOptionPane.showMessageDialog(jf, "删除成功");
                        }else {
                            JOptionPane.showMessageDialog(jf, "删除失败");
                        }
                    }
                }
            }
        });


        JPanel pagePanel = new JPanel();
        pagePanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        // 获取图书总数量
        totalPage = (int) Math.ceil(DQLUtils.getNumberOfBooks() / (double)COLUMN_PER_PAGE);
        // 翻页按钮
        JButton lastPageButton = new JButton("上一页");
        JLabel numberLabel = new JLabel();
        JButton nextPageButton = new JButton("下一页");

        // 上一页的监听器
        lastPageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(currPage == 1){
                    JOptionPane.showMessageDialog(jf, "已经是第一页了");
                }else{
                    // 请求第上一页
                    model.getDataVector().clear();
                    requestData(--currPage);
                    numberLabel.setText(currPage + "/" + totalPage);
                }
            }
        });


        // 下一页的监听器
        nextPageButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(currPage == totalPage){
                    JOptionPane.showMessageDialog(jf, "已经是最后一页了");
                } else{
                    // 请求下一页的数据
                    model.getDataVector().clear();
                    requestData(++currPage);
                    numberLabel.setText(currPage + "/" + totalPage);
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
                            (String) td.get(table.getSelectedRow()).get(1),
                            (String) td.get(table.getSelectedRow()).get(2),
                            Double.parseDouble((String) td.get(table.getSelectedRow()).get(5)) ,
                            (String) td.get(table.getSelectedRow()).get(3),
                            Integer.parseInt((String) td.get(table.getSelectedRow()).get(6)),
                            (String) td.get(table.getSelectedRow()).get(4)
                    );
                    new BorrowBookDialog(toBorrow, user, jf, "Borrow Book", true);
                    model.getDataVector().clear();
                    requestData(currPage);
                }
            }
        });

        searchPanel.add(Box.createHorizontalStrut(20));
        searchPanel.add(borrowButton);

        pagePanel.add(lastPageButton);
        pagePanel.add(Box.createHorizontalStrut(10));
        pagePanel.add(numberLabel);
        pagePanel.add(Box.createHorizontalStrut(10));
        pagePanel.add(nextPageButton);

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
        this.add(Box.createVerticalStrut(20));
        this.add(pagePanel);
        // 第一次请求数据只显示第一页
        requestData(1);
        numberLabel.setText(currPage + "/" + totalPage);
        resizeColumnWidth();
    }

    public void requestData(int page){

        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        int i = COLUMN_PER_PAGE * (page - 1);
        try {
            conn = DBUtil.getConnection();
            String sql = "select tb.isbn isbn, tb.name name, tb.author author, tb.price price, tb.instock instock, tt.typename typename from t_book tb, t_booktype tt where tb.type = tt.typeid limit ?, ?";
            ps = conn.prepareStatement(sql);
            ps.setInt(1,COLUMN_PER_PAGE * (page - 1));
            ps.setInt(2, COLUMN_PER_PAGE);
            rs = ps.executeQuery();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(++i);
                temp.add(rs.getString("isbn"));
                temp.add( rs.getString("name"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("typename"));
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
        int i = 1;
        try {
            conn = DBUtil.getConnection();
            String sql = "select tb.isbn isbn, tb.name name, tb.author author, tb.price price, tb.instock instock, tt.typename typename from t_book tb, t_booktype tt where tb.type = tt.typeid and " + column + " like ?";
            ps = conn.prepareStatement(sql);
            String even = "%" + text + "%";
            ps.setString(1, even);
            rs = ps.executeQuery();
            td.clear();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(i++);
                temp.add(rs.getString("isbn"));
                temp.add( rs.getString("name"));
                temp.add(rs.getString("author"));
                temp.add(rs.getString("typename"));
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

    public void resizeColumnWidth(){
        table.setAutoResizeMode(JTable.AUTO_RESIZE_OFF);
        table.getColumnModel().getColumn(0).setPreferredWidth(80);
        table.getColumnModel().getColumn(1).setPreferredWidth(200);
        table.getColumnModel().getColumn(2).setPreferredWidth(300);
        table.getColumnModel().getColumn(3).setPreferredWidth(200);
        table.getColumnModel().getColumn(4).setPreferredWidth(100);
        table.getColumnModel().getColumn(5).setPreferredWidth(150);
        table.getColumnModel().getColumn(6).setPreferredWidth(100);
    }
}
