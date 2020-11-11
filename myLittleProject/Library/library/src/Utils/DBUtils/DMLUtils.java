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
     *   添加图书，如果已经有了就添加到库存里
     * @param book 要添加的图书
     * @return 1 代表添加成功
     *         -1 代表图书名字和编号对不上
     */
    public static int addBook(Book book){
        if(DQLUtils.bookExist(book.getBookISBN(), book.getBookName()) == 1){
            // 如果已经存在，就添加到库存中
            DMLUtils.updateBook(book, "stock", 1, book.getStock());
            return 1;
        }else if(DQLUtils.bookExist(book.getBookISBN(), book.getBookName()) == -1){
            return -1;
        }
        int rst = 1;
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
                rst = 0;
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
     * @param status 要对书籍执行的操作，加是1，减是-1，其他是0
     * @param number 加减书籍的数量
     * @param column 要修改的字段
     * @return 执行的情况 成功/失败 + 数量
     * 约定几种情况 ：没有足够的书籍，应该：----
     */
    public static int updateBook(Book book, String column, int status, int number){
        String name = book.getBookName();
        Connection conn = null;
        PreparedStatement ps = null;
        try {
            conn = DBUtil.getConnection();
            String sql = "update books set " + column + " = " ;
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
