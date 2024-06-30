namespace Toturial.POJO
{
    abstract class Adult
    {
        private double height;
        private double weight;

        /**
         * 有参构造函数
         */
        public Adult(double height, double weight) {
            this.height = height;
            this.weight = weight;
        }

        /**
         * 计算BMI指数
         */
        public double CalculateBMI()
        {
            return height / (weight * weight);
        }

        public abstract void Conclusion();

        public double Height
        {
            get
            {
                return height;
            }
            set
            {
                height = value;
            }
        }

        public double Weight
        {
            get
            {
                return weight;
            }
            set
            {
                weight = value;
            }
        }

    }
}
