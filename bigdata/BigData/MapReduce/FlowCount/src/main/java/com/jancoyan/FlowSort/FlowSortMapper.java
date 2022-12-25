/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/3
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowSort;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

public class FlowSortMapper extends Mapper<LongWritable, Text, FlowBean, Text> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {

        //1:拆分行文本数据(V1),得到四个流量字段,并封装FlowBean对象---->K2
        String[] split = value.toString().split("\t");

        FlowBean flowBean = new FlowBean();

        flowBean.setUpFlow(Integer.parseInt(split[1]));
        flowBean.setDownFlow(Integer.parseInt(split[2]));
        flowBean.setUpCountFlow(Integer.parseInt(split[3]));
        flowBean.setDownCountFlow(Integer.parseInt(split[4]));

        //2:通过行文本数据,得到手机号--->V2
        String phoneNum = split[0];

        //3:将K2和V2下入上下文中
        context.write(flowBean, new Text(phoneNum));
    }
}
