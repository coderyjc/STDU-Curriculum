/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/7
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.sort;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

public class SortMapper extends Mapper<LongWritable, Text, SortBean, NullWritable> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        SortBean bean = new SortBean();
        bean.setNumber(Integer.parseInt(value.toString()));
        context.write(bean, NullWritable.get());
    }
}
