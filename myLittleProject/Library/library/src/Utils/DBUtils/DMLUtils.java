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
            int rs = ps.executeUpdate();
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
     * @return 添加图书的业务是否成功了
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
    public static boolean updateBook(Book book, String column, String changed){
        Connection conn = null;
        PreparedStatement ps = null;
        boolean succ = false;
        try {
            conn = DBUtil.getConnection();
            /*
                这里要针对不同的字段修改做不同的语句处理
                一种本身就是字符串型的
                一种是数字型的，这俩分别写sql
             */
            if(column.equals("lent") || column.equals("stock") || column.equals("price")){
                String sql_int = "update books set " + column + " = " + changed + " where ISBN = " + book.getBookISBN();
                ps = conn.prepareStatement(sql_int);
            }else{
                String sql_string = "update books set " + column + " = '" + changed + "' where ISBN = " + book.getBookISBN();
                ps = conn.prepareStatement(sql_string);
            }
            int rst = ps.executeUpdate();
            if(rst != 0)
                succ = true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return succ;
    }

    /**
     *  删除一列书的数据
     * @param book 传进来的book参数，只有一个ISBN 属性
     * @return 删除成功或者失败，在这里选中的列一定是数据库中已经存在的，所以一般不会有删除失败的情况
     */
    public static boolean deleteBook(Book book){
        boolean success = false;
        Connection conn;
        PreparedStatement ps;
        try {
            conn = DBUtil.getConnection();
            String sql = "delete from books where ISBN = " + book.getBookISBN();
            ps = conn.prepareStatement(sql);
            int rst = ps.executeUpdate();
            if(rst != 0)
                success = true;
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return  success;
    }


}
