/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/17
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.dig;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

public class DigMapper extends Mapper<LongWritable, Text, Text, Text> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        String[] datas = value.toString().split("\t");
        context.write(new Text(datas[0]), new Text("-" + datas[1]));
        context.write(new Text(datas[1]), new Text("+" + datas[0]));
    }
}
