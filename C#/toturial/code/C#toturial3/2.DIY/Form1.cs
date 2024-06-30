using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

/*
 * @Author: Yan Jingcun
 * @Date: 2021.11.02
 * @Description: 修仙模拟器
 */
namespace HelloCSWin
{
    public partial class Form1 : Form
    {

        private int count = 1;

        public Form1()
        {
            InitializeComponent();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private String get_sex()
        {
            if (radioButton1.Checked)
                return "你出生了，是个男娃";
            else if (radioButton2.Checked)
                return "你出生了，是个女娃";
            else return "你出生了，但旁边的人都没看出来你是男是女";
        }

        private String get_name()
        {
            if (textBox1.Text != "")
                return "于是父母给你起名为" + textBox1.Text;
            else return "父母给你起名为‘无名’";
        }

        private void get_luxury()
        {
            listBox1.Items.Add("突然风雨大作");
            if(checkBox1.Checked)
                listBox1.Items.Add("众人看到你脖子上挂着一块阴阳鱼玉佩，甚恐");
            if(checkBox2.Checked)
                listBox1.Items.Add("他们不知道的是，你嘴里含着还一块丹心佛玉佩");
        }

        private String get_level()
        {
            String str = "你自幼聪慧，悟性极高，出生便是" + comboBox1.Text + "高手";
            if(comboBox1.Text == "")
            {
                str = "你天生根骨残缺，众人说你不适合走修炼这条路"; 
            }
            return str;
        }
        

        private void time_go(object sender, EventArgs e)
        {
            // 时间流逝函数
            if(count == 1)
            {
                listBox1.Items.Add(get_sex());
            }
            if(count == 2)
            {
                listBox1.Items.Add(get_name());
            }
            if(count == 3)
            {
                get_luxury();
            }
            if(count == 4)
            {
                listBox1.Items.Add(get_level());
            }
            if(count == 5)
            {
                listBox1.Items.Add("于是你在仙界开始了一段传奇的旅程...");
                timer1.Stop();
                groupBox1.Enabled = true;
                groupBox2.Enabled = true;
            }
            count++;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            groupBox1.Enabled = false;
            groupBox2.Enabled = false;
            timer1.Start();
        }
    }
}
