/**
 * @Author Jingcun Yan
 * @Date 09:32 2020/11/16
 * @Description
 */
package Components;

import Components.Dialog.AddUserDialog;
import Components.Dialog.UpdateUserDialog;
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
 * @author JingcunYan
 */
public class UserTableComponent extends Box {

    final int WIDTH = 1000;
    final int HEIGHT = 750;

    JFrame jf;
    Vector<Vector> td = new Vector<>();
    JTable table;
    DefaultTableModel model;

    public UserTableComponent(JFrame jf, User user){
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        Object[] columnNames = {"序号", "ID", "姓名", "类型", "性别", "电话", "密码"};

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

        // 对用户的增删改操作 panel
        JPanel btnPanel = new JPanel();
        btnPanel.setMaximumSize(new Dimension(WIDTH,80));
        btnPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        // 增加用户
        JButton addButton = new JButton("添加新用户");
        // 修改用户信息
        JButton updButton = new JButton("修改用户信息");
        // 删除用户
        JButton delButton = new JButton("删除选中用户");

        // 增加用户监听器
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new AddUserDialog(jf, "创建用户", true);
                model.getDataVector().clear();
                requestData();
            }
        });

        // 修改用户监听器
        updButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String defaultText = "";
                if(table.getSelectedRow() != -1) {
                    defaultText = (String) td.get(table.getSelectedRow()).get(1);
                }
                new UpdateUserDialog(defaultText, jf, "修改信息", true, new ActionListenerCallBack() {
                    @Override
                    public void hasDone(Object obj) {
                        model.getDataVector().clear();
                        requestData();
                    }
                }).setVisible(true);
            }
        });

        // 删除用户监听器
        delButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                //删除图书信息
                int selected = table.getSelectedRow();
                if(selected == -1){
                    JOptionPane.showMessageDialog(jf, "未选中任何用户");
                } else {
                    int click = JOptionPane.showConfirmDialog(jf, "确定删除此用户？");
                    if(click == JOptionPane.YES_OPTION){
                        //执行图书删除业务
                        boolean succ = DMLUtils.deleteUser(new User((String) td.get(table.getSelectedRow()).get(1)));
                        if(succ){
                            model.getDataVector().clear();
                            requestData();
                            JOptionPane.showMessageDialog(jf, "删除成功");
                        }else {
                            JOptionPane.showMessageDialog(jf, "删除失败");
                        }
                        model.getDataVector().clear();
                        requestData(); //获取信息并刷新表格
                    }
                }
            }
        });


        // 按钮添加到panel上
        btnPanel.add(addButton);
        btnPanel.add(Box.createHorizontalStrut(40));
        btnPanel.add(updButton);
        btnPanel.add(Box.createHorizontalStrut(40));
        btnPanel.add(delButton);

        // 查找用户（comboBox）
        // 查找用户单独一个panel
        JPanel sPanel = new JPanel();
        JLabel sLabel = new JLabel("查找用户 根据");
        JComboBox<String> sComboBox = new JComboBox<>(new String[]{
                "ID", "姓名", "类型", "性别", "电话"
        });
        JTextField sField = new JTextField(10);
        JButton sButton = new JButton("查找");

        sButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                // 查询
                if("".equals(sField.getText().trim())){
                    JOptionPane.showMessageDialog(jf, "请输入查询内容");
                }else{
                    model.getDataVector().clear();
                    switch (sComboBox.getSelectedIndex()){
                        case 0:searchUser("id", sField.getText().trim()); break;
                        case 1:searchUser("name", sField.getText().trim()); break;
                        case 2:searchUser("type", sField.getText().trim()); break;
                        case 3:searchUser("sex", sField.getText().trim()); break;
                        case 4:searchUser("tel", sField.getText().trim()); break;
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

        //添加间隔和控件
        sPanel.add(Box.createHorizontalStrut(20));
        sPanel.add(sLabel);
        sPanel.add(sComboBox);
        sPanel.add(Box.createHorizontalStrut(20));
        sPanel.add(sField);
        sPanel.add(Box.createHorizontalStrut(20));
        sPanel.add(sButton);

        JScrollPane jsp = new JScrollPane(table);
        this.add(Box.createVerticalStrut(40));
        this.add(btnPanel);
        this.add(Box.createVerticalStrut(30));
        this.add(sPanel);
        this.add(jsp);
        requestData();
        this.setVisible(true);
        resizeColumnWidth();
    }

    public void requestData(){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from t_user";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            int i = 1;
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(i++);
                temp.add(rs.getString("id"));
                temp.add(rs.getString("name"));
                temp.add(rs.getString("type"));
                temp.add(rs.getString("sex"));
                temp.add(rs.getString("tel"));
                temp.add(rs.getString("password"));
                td.add(temp);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }finally {
            DBUtil.close(conn, ps, rs);
        }
        model.fireTableDataChanged();
    }

    public void searchUser(String column, String text){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from t_user where " + column + " = ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1, text);
            rs = ps.executeQuery();
            td.clear();
            int i = 1;
            while(rs.next()){
                Vector<Object> temp = new Vector<>();
                temp.add(i++);
                temp.add(rs.getString("id"));
                temp.add(rs.getString("name"));
                temp.add(rs.getString("type"));
                temp.add(rs.getString("sex"));
                temp.add(rs.getString("tel"));
                temp.add(rs.getString("password"));
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
        table.getColumnModel().getColumn(2).setPreferredWidth(240);
        table.getColumnModel().getColumn(3).setPreferredWidth(150);
        table.getColumnModel().getColumn(4).setPreferredWidth(100);
        table.getColumnModel().getColumn(5).setPreferredWidth(150);
        table.getColumnModel().getColumn(6).setPreferredWidth(280);
    }
}