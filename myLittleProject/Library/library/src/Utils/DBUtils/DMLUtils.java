package Utils.DBUtils;

import Domain.Book;
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

    /**
     *  添加图书，如果已经有了就添加到库存里
     * @param book 要添加的图书
     * @return
     */
    public static boolean addBook(Book book){
        // inStock 来存储在数据库中的书，以获得其库存量。
        Book inStock = DQLUtils.getBook(book.getBookISBN());
        if(inStock != null){
            // 如果已经存在，此时book已经是完整的一本书了，就添加到库存中
            int last = book.getStock() + inStock.getStock();
            DMLUtils.updateBook(book, "stock", String.valueOf(last));
            return true;
        }
        boolean rst = false;
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "insert into books values (?, ?, ?, ?, ?, ?, 0)";
            ps = conn.prepareStatement(sql);
            ps.setString(1, book.getBookISBN());
            ps.setString(2, book.getBookName());
            ps.setString(3, String.valueOf(book.getBookPrice()));
            ps.setString(4, book.getAuthor());
            ps.setString(5, String.valueOf(book.getStock()));
            ps.setString(6, book.getDescription());
            int rs = ps.executeUpdate();
            if(rs != 0){
                rst = true;
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            //关闭数据库连接
            DBUtil.close(conn, ps);
        }
        return rst;
    }

    /**
     * @param book 书籍对象
     * @param column 要修改的字段
     * @return 执行的情况 成功/失败 + 数量
     * 约定几种情况 ：没有足够的书籍，应该：----
     */
    public static int updateBook(Book book, String column, String changed){
        String name = book.getBookName();
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = DBUtil.getConnection();

            String sql = "";

            ps = conn.prepareStatement(sql);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return 0;
    }



    public static boolean deleteBook(Book book){
        boolean success = false;




        return success;
    }
}
