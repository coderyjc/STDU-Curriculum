/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/3
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowSum;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

public class FlowSumMapper extends Mapper<LongWritable, Text, Text, FlowCount> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {

        String[] attr = value.toString().split("\t");
        FlowCount flowCount = new FlowCount();

        flowCount.setUpFlow(Integer.parseInt(attr[1]));
        flowCount.setDownFlow(Integer.parseInt(attr[2]));
        flowCount.setDownCountFlow(Integer.parseInt(attr[3]));
        flowCount.setUpCountFlow(Integer.parseInt(attr[4]));

        context.write(new Text(attr[0]), flowCount);
    }
}
