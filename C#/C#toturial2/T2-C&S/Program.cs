using System;
using Toturial.POJO.Impl;

namespace Toturial
{
    /**
     * @Author：Yan Jingcun
     * @Date：2021.10.26
     * @Description：Inplement 
     * */
    class Program
    {
        static void Main(string[] args) {
            Console.WriteLine("\n\n******* 作者：闫竞存 信1901-4 20194127  ******\n\n计算周长和面积");

            int choose = 0;
            decimal size = 0;
            while (true)
            {
                Console.WriteLine("输入选项：\n1. 正方形\t2.圆形\t其他.退出");
                choose = int.Parse(Console.ReadLine());

                if (1 == choose)
                {
                    Console.Write("输入边长：");
                    size = decimal.Parse(Console.ReadLine());
                    Square square = new Square();
                    if (square.initialize(size))
                    {
                        square.showResult();
                    }
                    else
                    {
                        Console.WriteLine("输入错误，请重新输入");
                    }
                }
                else if (2 == choose)
                {
                    Console.Write("输入半径：");
                    size = decimal.Parse(Console.ReadLine());
                    Circle square = new Circle();
                    if (square.initialize(size))
                    {
                        square.showResult();
                    }
                    else
                    {
                        Console.WriteLine("输入错误，请重新输入");
                    }
                }
                else
                    break;
            }
            Console.ReadLine();
        }
    }
}
