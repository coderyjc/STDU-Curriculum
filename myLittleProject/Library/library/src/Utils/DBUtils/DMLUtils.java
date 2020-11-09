package Utils.DBUtils;

import Domain.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;

public class DMLUtils {
    private DMLUtils(){}

    public static boolean addUser(User user){
        boolean success = false;
        Connection conn = null;
        PreparedStatement ps = null;
        int rs = 0;

        try {
            conn = DBUtil.getConnection();
            String sql = "insert into users values (?, ?, ?, ?, ?, ?)";
            ps = conn.prepareStatement(sql);
            ps.setString(1, user.getUserId());
            ps.setString(2, user.getUserName());
            ps.setString(3, String.valueOf(user.getUserType()));
            ps.setString(4, String.valueOf(user.getUserSex()));
            ps.setString(5, user.getUserTel());
            ps.setString(6, user.getUserPwd());
            rs = ps.executeUpdate();
            if(rs != 0){
                success = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            //关闭数据库连接
            DBUtil.close(conn, ps);
        }
        return success;
    }
}
