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
     * @Description：验证输入的月份的季节
     * */
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n\n******* 作者：闫竞存 信1901-4 20194127  ******\n\n");

            String[] monthName = {"冬季", "春季", "夏季", "秋季", "冬季" };
            // 输入季节
            Console.Write("请输入月份（1~12）：");
            int month = int.Parse(Console.ReadLine());
            // 数据校验
            while (!verifyData(month)){ 
              Console.Write("请输入月份（1~12）：");
                // 数据输入错误，重新输入
                month = int.Parse(Console.ReadLine());
            }
            Console.WriteLine("{0} 月是 {1}", month, monthName[month  / 3]);
            Console.ReadLine();
        }
        /**
         * 对输入的数据进行校验
         * */
        static bool verifyData(int data)
        {
            if(data < 1 || data > 12)
            {
                Console.WriteLine("输入数据有误");
                return false;
            }
            return true;
        }
    }
}
