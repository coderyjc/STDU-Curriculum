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
     * @Description：while实现数鸡蛋
     * */
    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("\n\n******* 作者：闫竞存 信1901-4 20194127  ******\n\n");
            int numberOfEgg = 2;
            while (true)
            {
                if (numberOfEgg % 2 == 1 && numberOfEgg % 3 == 1 && numberOfEgg % 4 == 1)
                {
                    Console.WriteLine("这筐鸡蛋至少有 {0} 个", numberOfEgg);
                    break;
                }
                else
                    numberOfEgg++;
            }
            Console.ReadLine();
        }
        
    }
}
