package Utils.DBUtils;

import java.sql.*;


/**
 * @author Jingcun Yan
 */
public class DBUtil {
    private DBUtil() {
    }

    static {
        try {
            Class.forName("com.mysql.jdbc.Driver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    //获取数据库连接
    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection("jdbc:mysql://localhost:3306/library", "root", "333");
    }

    /**
     * 关闭数据库， 释放资源
     *
     * @param conn 数据库连接对象
     * @param ps   SQL语句
     * @param rs   查询结果集
     */
    public static void close(Connection conn, PreparedStatement ps, ResultSet rs) {

        if (conn != null) {
            try {
                conn.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        if (ps != null) {
            try {
                ps.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }

        if (rs != null) {
            try {
                rs.close();
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }
}