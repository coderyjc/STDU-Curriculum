namespace Toturial.POJO
{
    /*
 * @Author: Yan Jingcun
 * @Date: 2021.10.28
 * @Description: 形状操作的接口
 * */
    interface IShape
    {
        // 初始化参数
        bool initialize(decimal size);

        // 获取周长
        decimal getPerimeter();

        // 获取面积
        decimal getArea();
    }
}
