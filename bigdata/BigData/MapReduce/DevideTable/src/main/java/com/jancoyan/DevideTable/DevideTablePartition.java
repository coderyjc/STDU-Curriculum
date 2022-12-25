/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/30
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.DevideTable;

import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Partitioner;

public class DevideTablePartition extends Partitioner<Text, NullWritable> {
    @Override
    public int getPartition(Text text, NullWritable nullWritable, int i) {
        if(Integer.parseInt(text.toString().split("\t")[5]) <= 15)
            return 0;
        else return 1;
    }
}
