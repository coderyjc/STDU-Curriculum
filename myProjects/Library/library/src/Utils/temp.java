///**
// * @Author Jingcun Yan
// * @Date Create in 20:46 2020/11/24
// * @Description
// */
//
//package Utils;
//
//import Utils.DBUtils.DBUtil;
//
//import java.sql.Connection;
//import java.sql.PreparedStatement;
//import java.sql.SQLException;
//import java.util.Random;
//
//public class temp {
//
//    public static String getRandomISBN(){
//        int i = 10000 + new Random().nextInt(9999);
//        return "565260" + i;
//    }
//
//    public static void main(String[] args) {
//        Random r = new Random();
//        Connection conn = null;
//        PreparedStatement ps = null;
//        try {
//            conn = DBUtil.getConnection();
//            String sql = "insert into t_book value (?, ?, ?, ?, ?, ?)";
//             ps = conn.prepareStatement(sql);
//             String isbn = getRandomISBN();
//             int ran = r.nextInt(7) + 1;
//            for(int i = 0 ; i < ran; i++){
//                ps.setString(1, isbn + i);
//                ps.setString(2, "《临床医学》");
//                ps.setString(3, "潍坊医学院");
//                ps.setString(4, "199.66");
//                ps.setString(5, "0");
//                ps.setString(6, "5");
//            ps.executeUpdate();
//            }
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }finally {
//            DBUtil.close(conn, ps, null);
//        }
//
//    }
//}
