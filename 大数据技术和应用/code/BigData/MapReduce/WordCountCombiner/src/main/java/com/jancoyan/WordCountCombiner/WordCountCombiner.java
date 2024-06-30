/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/1
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.WordCountCombiner;

import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

public class WordCountCombiner extends Reducer<Text, LongWritable, Text, LongWritable> {

    @Override
    protected void reduce(Text key, Iterable<LongWritable> values, Context context) throws IOException, InterruptedException {
        long count = 0;

        for(LongWritable val : values){
            count += val.get();
        }

        context.write(key, new LongWritable(count));
    }

}
