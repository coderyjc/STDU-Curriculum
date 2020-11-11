//package Components;
//
//import javax.swing.table.AbstractTableModel;
//import java.sql.ResultSet;
//import java.sql.ResultSetMetaData;
//import java.sql.SQLException;
//
//public class RSTableModel extends AbstractTableModel {
//
//    private ResultSet rs;
//    private ResultSetMetaData rsmd;
//
//    private Object[] columnNames = {"编号", "书名", "作者", "简介", "价格", "库存", "借出"};
//
//    private Object[][] rowData;
//
//    public RSTableModel(Object[][] row, ResultSet rs){
//        this.rowData = row;
//        this.rs = rs;
//    }
//
//    //Constructor
//    public RSTableModel(Object[][] rs){
//        this.rs = rs;
//        try {
//            rsmd = rs.getMetaData();
//        } catch (SQLException e) {
//            e.printStackTrace();
//        }
//    }
//
//    @Override
//    public String getColumnName(int column) {
//        try {
//            return rsmd.getColumnName(column + 1);
//        } catch (SQLException e) {
//            e.printStackTrace();
//            return "";
//        }
//    }
//
//
//    @Override
//    public int getRowCount() {
//        try {
//            rs.last();
//            return rs.getRow();
//        } catch (SQLException e) {
//            e.printStackTrace();
//            return 0;
//        }
//    }
//
//    @Override
//    public int getColumnCount() {
//        try {
//            return rsmd.getColumnCount();
//        } catch (SQLException e) {
//            e.printStackTrace();
//            return 0;
//        }
//    }
//
//    @Override
//    public Object getValueAt(int rowIndex, int columnIndex) {
//        try {
//            rs.absolute(rowIndex + 1);
//            return rs.getObject(columnIndex + 1);
//        } catch (SQLException e) {
//            e.printStackTrace();
//            return null;
//        }
//    }
//
//    @Override
//    public boolean isCellEditable(int rowIndex, int columnIndex) {
//        return false;
//    }
//}
