package Utils.DBUtils;

import java.sql.*;
import java.util.ResourceBundle;

/**
 * @author Jingcun Yan
 */
public class DBUtil {
    private DBUtil() {
    }

    static {
        try {
            Class.forName("oracle.jdbc.OracleDriver");
        } catch (ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    /**
     *  获取数据库连接
     * @return 数据库连接对象
     * @throws SQLException SQL 异常
     */
    public static Connection getConnection() throws SQLException {

        ResourceBundle bundle = ResourceBundle.getBundle("db");
        String user = bundle.getString("user");
        String passWord = bundle.getString("password");
        String url = bundle.getString("url");
        return DriverManager.getConnection(url, user, passWord);
    }

    /**
     * 关闭数据库， 释放资源
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