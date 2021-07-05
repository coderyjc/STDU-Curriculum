/**
 * @Author Jingcun Yan
 * @Date Create in 14:44 2020/11/27
 * @Description
 */

package Components;

import Domain.User;
import Utils.DBUtils.DBUtil;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Collections;
import java.util.Vector;

public class RecordComponent  extends Box{

    final int WIDTH = 1000;

    JFrame jf;
    Vector<Vector> td = new Vector<>();
    JTable table;
    DefaultTableModel model;

    public RecordComponent(JFrame jf, User user){
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        Object[] columnNames = {"序号","借阅人账号", "书籍ISBN", "借阅时间", "操作类型"};

        Vector<Object> columnName = new Vector<>();
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

        JScrollPane jsp = new JScrollPane(table);
        this.add(jsp);
        requestData();
        this.setVisible(true);
    }

    public void requestData(){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select id, isbn, datetime, typename " +
                    "from T_USER_LOG, T_OPERATOR_TYPE " +
                    "where T_USER_LOG.TYPE = T_OPERATOR_TYPE.TYPEID " +
                    "order by DATETIME desc";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            int i = 0;
            while(rs.next()){
                Vector<String> temp = new Vector<>();
                temp.add(String.valueOf(++i));
                temp.add(rs.getString("id"));
                temp.add(rs.getString("isbn"));
                temp.add(rs.getString("datetime"));
                temp.add(rs.getString("typename"));
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
