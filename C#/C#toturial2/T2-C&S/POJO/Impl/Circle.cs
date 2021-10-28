using System;

namespace Toturial.POJO.Impl
{
    /*
 * @Author: Yan Jingcun
 * @Date: 2021.10.28
 * @Description: 圆形
 * */
    class Circle : IShape, IDisplayResult
    {

        // 半径 
        private decimal radius;

        public decimal getArea()
        {
            return decimal.Parse(Math.PI.ToString()) * radius * radius;
        }

        public decimal getPerimeter()
        {
            return decimal.Parse(Math.PI.ToString()) * 2 * radius;
        }

        public bool initialize(decimal size)
        {
            if (size <= 0) return false;
            radius = size;
            return true;
        }

        public void showResult()
        {
            Console.WriteLine("圆形的周长为：{0}\n面积为：{1}", getPerimeter(), getArea());
        }
    }
}
