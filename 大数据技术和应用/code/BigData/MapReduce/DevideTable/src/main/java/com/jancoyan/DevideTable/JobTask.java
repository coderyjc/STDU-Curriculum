/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/30
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.DevideTable;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class JobTask extends Configured implements Tool {

    @Override
    public int run(String[] strings) throws Exception {
        // 创建Job任务对象
        Job job = Job.getInstance(super.getConf(), "partition_mapreduce");

        // 第一步：设置输入类和输入的路径
        job.setInputFormatClass(TextInputFormat.class);
        TextInputFormat.addInputPath(job, new Path("hdfs://000"));

        // 第二步：设置Mapper类和数据类型（K2、V2）
        job.setMapperClass(DevideTableMapper.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(NullWritable.class);

        // 第三步： 指定分区类
        job.setPartitionerClass(DevideTablePartition.class);

        // 第四五六步默认
        // 第七步：指定Reducer类和数据类型（K3、V3）
        job.setReducerClass(DevideTableReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(NullWritable.class);

        // 设置ReduceTask个数
        job.setNumReduceTasks(2);

        // 第八步：指定输出类和输出路径
        job.setOutputFormatClass(TextOutputFormat.class);
        TextOutputFormat.setOutputPath(job, new Path("hdfs://..."));

        // 等待任务结束
        boolean b = job.waitForCompletion(true);

        return b ? 0 : 1;
    }

    public static void main(String[] args) throws Exception {
        int run = ToolRunner.run(new Configuration(), new JobTask(), args);
        System.exit(run);
    }
}
