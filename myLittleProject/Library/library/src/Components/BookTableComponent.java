package Components;

import Domain.Book;
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

public class BookTableComponent extends Box {

    final int WIDTH = 1000;
    final int HEIGHT = 750;

    JFrame jf;
    private JTable table;
    private Object[][] obj = null;
    Vector<Vector> td = new Vector<>();
    DefaultTableModel model;

    public BookTableComponent(JFrame jf) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        //----这个功能应该是管理员才有的，读者的功能应该只有借阅和还书
        //----添加图书，修改图书，删除图书的按钮

        JPanel btnPanel = new JPanel();
        btnPanel.setMaximumSize(new Dimension(WIDTH,80));
        btnPanel.setLayout(new FlowLayout(FlowLayout.RIGHT));

        JButton addButton = new JButton("添加");
        JButton updButton = new JButton("修改");
        JButton delButton = new JButton("删除选中行");

        Object[] columnNames = {"ISBN", "书名", "作者", "简介", "价格", "库存", "借出"};

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
                // 修改图书信息
                new UpdateBookDialog(jf, "修改图书", true, new ActionListenerCallBack() {
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
                        }else
                            JOptionPane.showMessageDialog(jf, "删除失败");
                    }
                }
            }
        });

        btnPanel.add(addButton);
        btnPanel.add(updButton);
        btnPanel.add(delButton);
        this.add(btnPanel);

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
            String sql = "select * from books";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                String id = rs.getString("ISBN");
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

        model.fireTableDataChanged();

    }
}
