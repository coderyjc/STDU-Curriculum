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

    /**
     *
     * @param ISBN 图书的ISBN号
     * @param name 图书名
     * @return ISBN和图书名都一样才返回 1
     *         ISBN 一样，书名不一样返回 -1
     */
    public static int bookExist(String ISBN, String name){
        int rst = 0;
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "select * from books where ISBN = ?";
            ps = conn.prepareStatement(sql);
            ps.setString(1, ISBN);
            rs = ps.executeQuery();
            if(rs.next()){
                if(rs.getString("name").equals(name))
                    rst = 1;
                rst = -1;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps , rs);
        }
        return rst;
    }
}
