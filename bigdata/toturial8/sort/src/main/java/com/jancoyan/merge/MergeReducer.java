/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/7
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.merge;

import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

public class MergeReducer extends Reducer<MergeBean, NullWritable, MergeBean, NullWritable> {

    @Override
    protected void reduce(MergeBean key, Iterable<NullWritable> values, Context context) throws IOException, InterruptedException {


    }
}
