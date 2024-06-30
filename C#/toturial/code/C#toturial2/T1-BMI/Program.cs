using System;
using Toturial.POJO;

namespace Toturial
{
    /**
     * @Author：Yan Jingcun
     * @Date：2021.10.26
     * @Description：BMI
     * */
    class Program
    {
        static void Main(string[] args) {
            Console.WriteLine("\n\n******* 作者：闫竞存 信1901-4 20194127  ******\n\n计算BMI");

            Console.Write("输入性别（0代表女，1代表男）：");
            int sex = int.Parse(Console.ReadLine());
            Console.Write("输入体重（kg）：");
            double weight = double.Parse(Console.ReadLine());
            Console.Write("输入身高（m）：");
            double height = double.Parse(Console.ReadLine());
            Adult adult = null;
            if(1 == sex)
            {
                // 男
                adult = new Man(height, weight);
            }
            else
            {
                adult = new Woman(height, weight);
            }

            adult.Conclusion();
            
            Console.ReadLine();
        }
    }
}
