/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/7
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.sort;

import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

public class SortReducer extends Reducer<SortBean, NullWritable, Integer, Integer> {

    private Integer idx = 1;

    @Override
    protected void reduce(SortBean key, Iterable<NullWritable> values, Context context) throws IOException, InterruptedException {
        context.write(idx++, key.getNumber());
    }
}
