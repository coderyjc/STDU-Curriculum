using System;

namespace Toturial.POJO.Impl
{
    /*
     * @Author: Yan Jingcun
     * @Date: 2021.10.28
     * @Description: 正方形
     * */
    class Square : IShape, IDisplayResult
    {

        // 边长
        private decimal size;

        public decimal getArea()
        {
            return size * size;
        }

        public decimal getPerimeter()
        {
            return size * 4;
        }

        public bool initialize(decimal size)
        {
            if (size <= 0) return false;
            this.size = size;
            return true;
        }

        public void showResult()
        {
            Console.WriteLine("正方形的周长为：{0}\n面积为：{1}", getPerimeter(), getArea());
        }
    }
}
