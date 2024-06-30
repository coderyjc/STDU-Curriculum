using System;

namespace Toturial
{
    /**
     * @Author：Yan Jingcun
     * @Date：2021.10.26
     * @Description：鞍点
     * */
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n\n******* 作者：闫竞存 信1901-4 20194127  ******\n\n");

            Console.WriteLine("请输入数组的行的大小");
            int heng = int.Parse(Console.ReadLine());
            Console.WriteLine("请输入数组的列的大小");
            int shu = int.Parse(Console.ReadLine());

            double[] hengMax = new double[shu]; // 一行中最大的元素的索引
            double[] shuMin = new double[heng]; // 一列中最小的元素的索引

            // 动态声明数组
            double[, ] arr = new double[shu, heng];

            // 输入数据
            for (int i = 0; i < shu; i++)
            {
                // 按照行输入数据
                Console.WriteLine("输入第{0}行的数据，用空格隔开", i + 1);
                String[] nums = Console.ReadLine().Split(' ');
                hengMax[i] = 0;
                for (int j = 0; j < heng; j++)
                { // 赋值
                    arr[i, j] = double.Parse(nums[j]);
                    if (arr[i, j] >= hengMax[i])
                    {
                        // col 查找最大的
                        hengMax[i] = arr[i, j];
                    }
                }
            }

            // row 查找最小的
            for (int i = 0; i < heng; i++)
            {
                shuMin[i] = arr[0, i];
                for (int j = 0; j < shu; j++)
                {
                    if (arr[j, i] <= shuMin[i])
                    {
                        shuMin[i] = arr[j, i];
                    }
                }
            }

            bool hasPoint = false;
            // 查找鞍点
            for (int i = 0; i < shu; i++)
            {
                for(int j = 0; j < heng; j++)
                {
                    if(arr[i, j] == hengMax[i] && arr[i, j] == shuMin[j])
                    {
                        Console.WriteLine("> 第{0}行，第{1}列，鞍点值为{2}", i+1, j+1, arr[i, j]);
                        hasPoint = true;
                    }
                }
            }
            if (!hasPoint)
            {  
                Console.WriteLine("没有鞍点");
            }

            Console.ReadLine();
        }
    }
}
