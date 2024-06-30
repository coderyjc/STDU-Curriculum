/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/31
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.SortAndSerialize;

import com.jancoyan.Bean.PairWritable;
import io.netty.channel.rxtx.RxtxChannelConfig;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import java.io.IOException;

/*
传入数据格式：
K1     V1
偏移量  数据行
传出数据格式：
K2         V2
自定义Bean  Null
 */
public class PairMapper extends Mapper<LongWritable, Text, PairWritable, NullWritable> {

    @Override
    protected void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {
        // 直接组合和写入数据
        String[] split = key.toString().split("\t");
        // 假设第一个是Str，第二个是num
        PairWritable pairWritable = new PairWritable(split[0], Integer.parseInt(split[1]));
        // 写入输出
        context.write(pairWritable, NullWritable.get());
    }
}

