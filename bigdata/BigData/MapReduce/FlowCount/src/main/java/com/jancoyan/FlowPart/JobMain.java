/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/4
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowPart;

import com.jancoyan.FlowSort.FlowBean;
import com.jancoyan.FlowSort.FlowSortMapper;
import com.jancoyan.FlowSort.FlowSortReducer;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class JobMain extends Configured implements Tool {

    @Override
    public int run(String[] strings) throws Exception {

        // 1. 创建任务对象和输入类
        Job job =  Job.getInstance(super.getConf(), "FlowCountSort");
        job.setInputFormatClass(TextInputFormat.class);
        TextInputFormat.addInputPath(job, new Path("hdfs://127.0.0.1:9090"));

        // 2. 设置mapper任务
        job.setMapperClass(FlowSortMapper.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(com.jancoyan.FlowSort.FlowBean.class);

        // 3，自定义分区类
        job.setPartitionerClass(FlowCountPartition.class);
        job.setNumReduceTasks(3);
        // 456 规约、排序、分组 系统默认

        // 7. 设置reducer任务
        job.setReducerClass(FlowSortReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(FlowBean.class);

        // 8. 设置输出类
        job.setOutputFormatClass(TextOutputFormat.class);
        TextOutputFormat.setOutputPath(job, new Path("hdfs://127.0.0.1:9090"));

        // 等待任务执行完成
        boolean b = job.waitForCompletion(true);
        return b ? 0 : 1;

    }

    public static void main(String[] args) throws Exception {
        int exeCode = ToolRunner.run(new Configuration(), new com.jancoyan.FlowSort.JobMain(), args);
        System.exit(exeCode);
    }
}
