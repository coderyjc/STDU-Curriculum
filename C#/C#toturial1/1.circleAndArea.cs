using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Toturial
{
    /**
     * @Author：Yan Jingcun
     * @Date：2021.10.26
     * @Description：计算三角形和矩形的边长的C#控制台应用程序
     * */
    class Program
    {
        static void Main(string[] args)
        {
            int choose;  // 用户选择的项目
            double a1, a2, a3; // 三角形的边长
            double lenth, width;  // 

            Console.WriteLine("\n\n******* 作者：闫竞存 信1901-4 20194127  ******\n\n");

             Console.WriteLine("要计算的图形：");
             Console.WriteLine("1.三角形\n2.长方形");
             Console.WriteLine("输入序号：");
             choose = int.Parse(Console.ReadLine());

            if(1 == choose){
                Console.WriteLine("边长 1：");
                a1 = float.Parse(Console.ReadLine());
                Console.WriteLine("边长 2：");
                a2 = float.Parse(Console.ReadLine());
                Console.WriteLine("边长 3：");
                a3 = float.Parse(Console.ReadLine());

                // 验证输入的数据
                if(!verifyTrangle(a1, a2, a3))
                {
                    Console.WriteLine("三角形不符合规范，程序即将退出。");
                    Console.ReadLine();
                    System.Environment.Exit(0); // 结束进程
                }
                double cir = a1 + a2 + a3;      // 直接输出周长和面积
                Console.WriteLine("周长：{0}", cir);
                Console.WriteLine("面积：{0}", Math.Sqrt(cir / 2 * (cir / 2 - a1) * (cir / 2 - a2) * (cir / 2 - a3)));
            }else{
                // 输入数据
                Console.WriteLine("长：");
                lenth = float.Parse(Console.ReadLine());
                Console.WriteLine("宽：");
                width = float.Parse(Console.ReadLine());

                // 直接输出周长和面积
                Console.WriteLine("该长方形周长为：{0}", 2 * (lenth + width));
                Console.WriteLine("该长方形面积为：{0}", lenth * width);
            }
            Console.ReadLine();
        }

        /**
         * 对输入边长的进行验证
         * */
        static bool verifyTrangle(double a1, double a2, double a3)
        {
            if(a1 + a2 < a3 || a1 + a3 < a2 || a2 + a3 < a1)
                return false;
            return true;
        }
    }
}
