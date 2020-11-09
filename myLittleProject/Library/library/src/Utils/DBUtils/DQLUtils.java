package Utils.DBUtils;

import Domain.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Map;

public class DQLUtils {
    private DQLUtils(){}

    public static boolean isExist(User user){
        boolean exist = false;
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from users where id = ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1, user.getUserId());
            rs = ps.executeQuery();
            if(rs.next()){
                exist = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps , rs);
        }
        return exist;
    }

    public static boolean login(Map<String, String> user){
        boolean loginSuccess = false;
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from users where id = ? and password = ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1, user.get("userId"));
            ps.setString(2, user.get("userPwd"));
            rs = ps.executeQuery();
            if(rs.next()){
                loginSuccess = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps , rs);
        }
        return loginSuccess;
    }
}
