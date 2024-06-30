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
     * @Description：分别计算奇数和偶数之和
     * */
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n\n******* 作者：闫竞存 信1901-4 20194127  ******\n\n");

            // 输入大小和分配空间
            Console.WriteLine("输入数组的大小：");
            int size = int.Parse(Console.ReadLine());
            double[] arr = new double[size];

            for (int i = 0; i < arr.Length; i++)
            { // 输入
                Console.Write("输入第{0}个数：", i+1);
                arr[i] = double.Parse(Console.ReadLine());
            }
            calculate(arr); // 调用函数计算并输出
            Console.ReadLine();
        }

        /**
         * 分别计算输入的数组中的奇数和偶数之和并输出
         * */
        static void calculate(double[] arr){
            double evenSum = 0, oddSum = 0;
            for(int i = 0; i < arr.Length; i++){
                if(arr[i] % 2 == 0)
                {// 偶数
                    evenSum += arr[i];
                }else{// 奇数
                    oddSum += arr[i];
                }
            }
            Console.WriteLine("输入的数组中偶数之和为{0}，奇数之和为{1}\n", evenSum, oddSum);
        }


    }


}
