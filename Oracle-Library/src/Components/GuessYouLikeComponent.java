/**
 * @Author Jingcun Yan
 * @Date Create in 10:50 2020/11/30
 * @Description
 */

package Components;

import Components.Dialog.BorrowBookDialog;
import Domain.Book;
import Domain.User;
import Utils.DBUtils.DBUtil;
import Utils.DBUtils.DQLUtils;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.*;

public class GuessYouLikeComponent extends Box {

    JFrame jf;
    User localUser;
    Vector<Vector<Object>> td = new Vector<>();
    JTable table;
    DefaultTableModel model;

    public GuessYouLikeComponent(JFrame jf, User user){
        super(BoxLayout.Y_AXIS);
        localUser = user;
        this.jf = jf;

        Object[] columnNames = {"序号","ISBN", "书名", "作者", "价格"};

        Vector<Object> columnName = new Vector<>();
        Collections.addAll(columnName, columnNames);
        model = new DefaultTableModel(td, columnName);
        table = new JTable(){
            @Override
            public boolean isCellEditable(int row, int column) {
                return false;
            }
        };
        table.setModel(model);
        table.setRowHeight(25);

        // 标题的panel
        JPanel titlePanel = new JPanel();
        titlePanel.setLayout(new FlowLayout(FlowLayout.CENTER));
        JLabel titleLabel = new JLabel("图  书  推  荐");
        titleLabel.setFont(new Font(null, Font.PLAIN, 40));
        titlePanel.add(titleLabel);

        // 借阅的 panel
        JPanel borrowPanel = new JPanel();
        borrowPanel.setLayout(new FlowLayout(FlowLayout.CENTER));

        // 借阅的button
        JButton borrowButton = new JButton("借阅");
        borrowPanel.add(borrowButton);

        // 借阅的监听器
        borrowButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if (table.getSelectedRow() == -1){
                    JOptionPane.showMessageDialog(jf, "请选择一本书");
                } else {
                    Book toBorrow = new Book(
                            (String) td.get(table.getSelectedRow()).get(1),
                            (String) td.get(table.getSelectedRow()).get(2),
                            Double.parseDouble((String) td.get(table.getSelectedRow()).get(4)) ,
                            (String) td.get(table.getSelectedRow()).get(3),
                            0, ""
                    );
                    new BorrowBookDialog(toBorrow, user, jf, "Borrow Book", true);
                    model.getDataVector().clear();
                    requestData();
                }
            }
        });

        this.add(Box.createVerticalStrut(30));
        this.add(titlePanel);
        this.add(borrowPanel);
        JScrollPane jsp = new JScrollPane(table);
        this.add(jsp);
        requestData();
    }

    /**
     * 获取用户最近几次借书记录，统计类型并且按照类型的比例推送与类型相关的书
     * 如果用户当前没有借阅记录，就随机推送所有类型的书籍
     */
    public void requestData(){
        Connection conn = null;
        PreparedStatement ps =  null;
        ResultSet rs = null;
        // 存储用户偏好的Map，键为书籍类型，值为用户喜好程度，值越大，用户喜好程度越高
        // **用户的喜好程度也就是最近10次中有几次节约了这种类型的书
        Map<Integer, Integer> userPreference = new HashMap<>();
        try {
            // 获取连接
            conn = DBUtil.getConnection();
            // sql : 获取最近10次用户借阅的书籍类型和借阅该类型书籍的数量（喜好程度）
            String sql = "SELECT t_book.TYPE,count( t_book.TYPE ) cnt FROM t_user_log, t_book WHERE t_user_log.ISBN = t_book.ISBN AND t_user_log.id = ? AND t_user_log.TYPE = 0 AND ROWNUM <= 10 GROUP BY t_book.TYPE";
            ps = conn.prepareStatement(sql);
            ps.setString(1, localUser.getUserId());
            rs = ps.executeQuery();
            // 获取每一种类型的书的键值对
            // 书籍的类型 - 借阅书籍的数量
            while(rs.next()) {
                userPreference.put(rs.getInt("TYPE"), rs.getInt("CNT"));
            }

            // 获取每一种书籍的类型和数量
            Map<Integer, Integer> bookTypeAndNumber = DQLUtils.bookTypeAndNumber();

            // 如果是新用户，也就是从未借阅过任何书籍，就随机推荐书籍
            // 推荐的方式是每一种书籍都推荐两本
            if (userPreference.size() == 0){
                Iterator<Integer> tempIter = bookTypeAndNumber.keySet().iterator();
                while(tempIter.hasNext()){
                    // 每一种类型推荐两本书
                    userPreference.put(tempIter.next(), 2);
                }
            }

            // 用户偏好的迭代器
            Iterator<Integer> iter = userPreference.keySet().iterator();

            // 显示在界面上的“书籍推荐表”的行数，每往书籍推荐表上添加一条数据，这个值就+1
            // 这个值也是显示在界面上的书籍推荐表上的第一列的数值，即“序号”
            int tableRowNumber = 1;

            // 基于以上的结果集获取数据
            // iter是用户偏好结果集中的“键”，也就是用户喜好的书籍类型
            while(iter.hasNext()){
                // 用户 10 次以来借阅这种书籍的类型
                int borrowType = iter.next();

                // 填写sql语句，直接获取查询结果集，然后在循环rs的时候对书籍所在的行数进行获取
                // sql：我们已经通过迭代器获取到了borrowType，书籍类型，这个sql要从book表中查找出来未借出去（instock = 0）
                // 的这种类型的书籍
                sql = "select ROWNUM, isbn, name, author, price from t_book where instock = 0 and type = ? order by type";
                ps = conn.prepareStatement(sql);
                ps.setInt(1, borrowType);
                // 获取查询结果集
                rs = ps.executeQuery();

                // 查询结果集中的数据的书籍的名称有重复的，可能会造成推荐同一本书两次的情况
                // 解决方案：根据用户的喜好程度划分取书间隔，在所有书籍中每间隔一定的距离取出一本书
                // 有重复书籍的情况: 库存中存在10本以上未借出的同一本书籍，且用户在最近10次都是借阅的这一类型的书籍
                // 考虑到一般来说图书馆的同一本书籍不会超过10本，发生这种情况的可能性微乎其微，所以暂时忽略不计

                // 间隔 = 书籍的总数量 / 用户借阅的数量
                int interval = bookTypeAndNumber.get(borrowType) / userPreference.get(borrowType);
                // 按照选取书籍的间隔进行选取

                // 进行书籍的获取
                // i 用来控制循环，来根据间隔获取目标书籍
                int i = 0;
                while(rs.next()) {
                    // i == 1 是第一次，以后每隔一段距离取出一本书
                    if (++i == 1 || i % interval == 0) {
                        Vector<Object> temp = new Vector<>();
                        temp.add(tableRowNumber++);
                        temp.add(rs.getString("ISBN"));
                        temp.add(rs.getString("NAME"));
                        temp.add(rs.getString("AUTHOR"));
                        temp.add(rs.getString("PRICE"));
                        td.add(temp);
                    }
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        } finally {
            // 关闭数据库连接
            DBUtil.close(conn, ps, rs);
        }
        // 刷新JavaSwing表格模型中的数据
        model.fireTableDataChanged();
    }
}
