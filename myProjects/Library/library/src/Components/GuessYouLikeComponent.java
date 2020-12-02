/**
 * @Author Jingcun Yan
 * @Date Create in 10:50 2020/11/30
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
import java.util.HashMap;
import java.util.Map;
import java.util.Vector;

public class GuessYouLikeComponent extends Box {

    JFrame jf;
    Vector<Vector<Object>> td = new Vector<>();
    JTable table;
    DefaultTableModel model;

    public GuessYouLikeComponent(JFrame jf, User user){
        super(BoxLayout.Y_AXIS);
        this.jf = jf;




    }

    /**
     * 获取用户最近10次借书记录，统计类型并且按照类型的比例推送与类型相关的书
     * 如果用户当前没有借阅记录，就随机推送各种类型的书籍
     */
    public void requestData(){
        Connection conn = null;
        PreparedStatement ps =  null;
        ResultSet rs = null;
        Map<Integer, Double> userPreference = new HashMap<>(16);
        try {
            conn = DBUtil.getConnection();
            String sql = "";
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();
            while(rs.next()){
                userPreference.put(rs.getInt("type"), rs.getDouble("act"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps, rs);
        }
        System.out.println(userPreference.get(1));



    }
}
