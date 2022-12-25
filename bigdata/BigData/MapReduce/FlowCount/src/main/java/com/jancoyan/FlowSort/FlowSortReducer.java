/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/3
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowSort;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

public class FlowSortReducer extends Reducer<FlowBean, Text, Text, FlowBean> {

    @Override
    protected void reduce(FlowBean key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
        for (Text value : values) {
            context.write(value, key);
        }
    }
}
