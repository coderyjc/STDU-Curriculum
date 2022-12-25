/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/1
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.WordCountCombiner;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

public class WordCountCMapper extends Mapper<LongWritable, Text, Text, LongWritable> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException { super.map(key, value, context);

        Text text = new Text();
        LongWritable writable = new LongWritable();

        String[] strings = value.toString().split("\t");

        for (String string : strings) {
            text.set(string);
            writable.set(1);
            context.write(text, writable);
        }

    }
}
