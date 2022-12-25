/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/3
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowSum;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;

public class FlowCountReducer extends Reducer<Text, FlowCount, Text, FlowCount>{

    @Override
    protected void reduce(Text key, Iterable<FlowCount> values, Context context) throws IOException, InterruptedException {

        Integer upFlow = 0;
        Integer downFlow = 0;
        Integer upCountFlow = 0;
        Integer downCountFlow = 0;

        for (FlowCount value : values) {
            upFlow += value.getUpFlow();
            downFlow += value.getDownFlow();
            upCountFlow += value.getUpCountFlow();
            downFlow += value.getDownCountFlow();
        }

        FlowCount flowCount = new FlowCount();

        flowCount.setUpFlow(upFlow);
        flowCount.setDownFlow(downFlow);
        flowCount.setDownCountFlow(downCountFlow);
        flowCount.setUpCountFlow(upCountFlow);

        context.write(key, flowCount);
    }
}
