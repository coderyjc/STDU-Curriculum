/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/7
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.merge;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.yarn.webapp.hamlet.Hamlet;

import java.io.IOException;


public class MergeMapper extends Mapper<LongWritable, Text, MergeBean, NullWritable> {
    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        MergeBean bean = new MergeBean();
        String[] split = key.toString().split("\t");
        bean.setStr(split[0]);
        bean.setVal(split[1]);
        context.write(bean, NullWritable.get());
    }
}
