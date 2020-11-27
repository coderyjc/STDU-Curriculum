/**
 * @Author Jingcun Yan
 * @Date Create in 19:33 2020/11/26
 * @Description
 */

package Components;

import Domain.User;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.util.Vector;

/**
 * 主页面上，树形结构的右半边
 * @author Jingcun Yan
 */
public class RecommendComponent extends Box {

    JFrame jf;
    Vector<Vector> td = new Vector<>();
    DefaultTableModel model;

    public RecommendComponent(JFrame jf, User user) {
        super(BoxLayout.Y_AXIS);
        this.jf = jf;

        

    }
}