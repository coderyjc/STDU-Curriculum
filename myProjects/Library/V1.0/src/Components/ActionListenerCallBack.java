package Components;

/**
 * @author Jingcun Yan
 */
public interface ActionListenerCallBack {

    /**
     *  表示已经做完一件事的函数，参数当传给子类的时候， 相当于在子类中可以为父类传达一个信息表示。
     *  从而让父类可以对父类的特有元素进行操作。
     * @param obj 参数
     */
    void hasDone(Object obj);
}
