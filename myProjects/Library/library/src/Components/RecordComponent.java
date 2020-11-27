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

        Object[] columnNames = {"序号","借阅人账号", "书籍ID", "借阅时间"};

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




    }

    public void requestData(){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from t_user_log";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            while(rs.next()){



            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        model.fireTableDataChanged();
    }

}
