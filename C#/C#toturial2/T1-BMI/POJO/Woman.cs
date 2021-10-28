using System;

namespace Toturial.POJO
{
    class Woman : Adult
    {
        public Woman(double height, double weight) : base(weight, height) { }
        public override void Conclusion()
        {
            // 计算BMI并输出
            int chose = int.Parse(Math.Floor (CalculateBMI() + 1 / 5).ToString());
            if (chose >= 7)
            {
                Console.WriteLine("BMI测试结果为：非常肥胖");
                return;
            }
            String[] conclusion = { "过轻", "过轻", "过轻", "过轻", "适中", "过重", "肥胖" };
            Console.WriteLine("BMI测试结果为：{0}", conclusion[chose]);
        }
    }
}
