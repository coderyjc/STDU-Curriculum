//package Components;
//
//import Utils.DBUtils.DBUtil;
//
//import javax.swing.*;
//import javax.swing.table.DefaultTableModel;
//import java.awt.*;
//import java.sql.Connection;
//import java.sql.PreparedStatement;
//import java.sql.ResultSet;
//import java.sql.SQLException;
//import java.util.Collections;
//import java.util.Vector;
//
//public class LendingComponent extends Box {
//    final int WIDTH = 1000;
//    final int HEIGHT = 750;
//
//    JFrame jf;
//    Vector<Vector<Object>> td = new Vector<>();
//    DefaultTableModel model;
//
//    public LendingComponent(JFrame jf) {
//        super(BoxLayout.Y_AXIS);
//        this.jf = jf;
//
//        this.add(Box.createVerticalStrut(30));
//
//        // 借阅和归还的按钮
//        JPanel btnPanel = new JPanel();
//        btnPanel.setMaximumSize(new Dimension(WIDTH, 50));
//        btnPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
//
//        JButton borrowButton = new JButton("借阅图书");
//        JButton returnButton = new JButton("归还图书");
//        borrowButton.setSize(150, 100);
//        returnButton.setSize(150, 100);
//        btnPanel.add(borrowButton);
//        btnPanel.add(Box.createHorizontalStrut(50));
//        btnPanel.add(returnButton);
//        this.add(btnPanel);
//
//        // 借阅和归还的监听器
//
//
//        // 书籍搜索框
//        JPanel searchPanel = new JPanel();
//        searchPanel.setMaximumSize(new Dimension(WIDTH, 70));
//        searchPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
//
//        JLabel sLabel = new JLabel("书籍查询 按照");
//        JTextField sField = new JTextField(20);
//        JButton sButton = new JButton("查询");
//        JComboBox<String> jcb_column = new JComboBox<>(new String[]{
//                "书名", "ISBN", "作者"
//        });
//
//        searchPanel.add(sLabel);
//        searchPanel.add(Box.createHorizontalStrut(20));
//        searchPanel.add(jcb_column);
//        searchPanel.add(Box.createHorizontalStrut(20));
//        searchPanel.add(sField);
//        searchPanel.add(Box.createHorizontalStrut(20));
//        searchPanel.add(sButton);
//
//        this.add(searchPanel);
//
//        /*
//        模糊查询之前显示的表为初始的表，但是不可编辑
//        当用户选择了查询之后，更改表中的数据，然后对表进行刷新
//        最终显示刷新后的数据。
//         */
//
//        Object[] columnNames = {"ISBN", "书名", "作者", "简介", "库存"};
//        Vector columnName = new Vector();
//        Collections.addAll(columnName, columnNames);
//        model = new DefaultTableModel(td, columnName);
//        JTable table = new JTable(){
//            @Override
//            public boolean isCellEditable(int row, int column) {
//                return false;
//            }
//        };
//        table.setModel(model);
//        table.setRowHeight(25);
//
//    }
//
//    public void requestData(){
//        Connection conn = null;
//        PreparedStatement ps = null;
//        ResultSet rs = null;
//        try {
//            conn = DBUtil.getConnection();
//            String sql = "select * from books";
//            ps = conn.prepareStatement(sql);
//            rs = ps.executeQuery();
//            while(rs.next()){
//                Vector<Object> temp = new Vector<>();
//                String id = rs.getString("ISBN");
//                String name = rs.getString("name");
//                String author = rs.getString("author");
//                String description = rs.getString("description");
//                String stock = rs.getString("stock");
//                temp.add(id); temp.add(name); temp.add(author); temp.add(description);
//                temp.add(stock);
//                td.add(temp);
//            }
//        } catch (SQLException e) {
//            e.printStackTrace();
//        } finally {
//            DBUtil.close(conn, ps, rs);
//        }
//        model.fireTableDataChanged();
//    }
//}
