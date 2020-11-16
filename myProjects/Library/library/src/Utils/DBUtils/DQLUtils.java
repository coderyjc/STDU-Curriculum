package Utils.DBUtils;

import Domain.Book;
import Domain.User;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.Map;

public class DQLUtils {
    private DQLUtils(){}

    /**
     *  查看用户是否存在
     * @param user 用户，其中只包含用户的ID
     * @return 返回数据库中是否已经存在这个用户的ID了
     */
    public static boolean isExist(User user){
        boolean succ = false;
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
                succ = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps , rs);
        }
        return succ;
    }

    public static User login(Map<String, String> user){
        /**
         * 原来的时候我在这里给usr new了一个内存，这就导致了在返回的时候usr永远不可能为null
         * 所以登录的时候永远显示成功，所以应该改成null，等到查找到了之后才给他分配一个地址
         * 避免了空指针异常
         */
        User usr = null;
//        boolean loginSuccess = false;
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
                // 在登录的时候只把ID和姓名查找出来，其他的以后再说

                /*
                 * 我在第一次查找的时候只找了姓名和类型，而没有找密码，从而导致了在修改密码的时候修改错误。
                 * 这个用户的类型要传递就要传递完整的类型，不能只传一半，不然后期出错了之后会会很难找。
                 */
                usr = new User();
                usr.setUserId(user.get("userId"));
                usr.setUserName(rs.getString("name"));
                usr.setUserType(Integer.parseInt(rs.getString("type")));
                usr.setUserPwd(rs.getString("password"));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps , rs);
        }
        return usr;
    }

    /**
     * 获取图书的工具类
     * @param ISBN 书籍的ISBN号
     * @return 如果找到了这本书，就返回这本书构成的对象，如果没找到，就返回null
     */
    public static Book getBook(String ISBN){
        Book rst = null;
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
                rst = new Book();
                rst.setAuthor(rs.getString("author"));
                rst.setBookISBN(rs.getString("ISBN"));
                rst.setBookName(rs.getString("name"));
                rst.setBookPrice(Double.valueOf(rs.getString("price")));
                rst.setDescription(rs.getString("description"));
                rst.setLent(Integer.parseInt(rs.getString("lent")));
                rst.setStock(Integer.parseInt(rs.getString("stock")));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            DBUtil.close(conn, ps , rs);
        }
        return rst;
    }
}
