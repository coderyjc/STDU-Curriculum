/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/31
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.SortAndSerialize;

import com.jancoyan.Bean.PairWritable;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;


public class JobMain extends Configured implements Tool {

    @Override
    public int run(String[] strings) throws Exception {
        // 第一步：获取Job实例、设置输入格式
        Job job = Job.getInstance(super.getConf(), "sort_and_serialize");
        job.setInputFormatClass(TextInputFormat.class);
        TextInputFormat.addInputPath(job, new Path("hdfs://..."));

        // 第二步：设置Mapper类
        job.setMapperClass(PairMapper.class);
        job.setMapOutputKeyClass(PairWritable.class);
        job.setMapOutputValueClass(NullWritable.class);

        // 第三、四、五、六步：分区、排序、规约、分组
        // 在pojo中设置的排序类会被默认执行

        // 第七步：设置Reducer启动类
        job.setReducerClass(PairReducer.class);
        job.setOutputKeyClass(PairWritable.class);
        job.setOutputValueClass(NullWritable.class);

        // 第八步：设置输出文件格式
        job.setOutputFormatClass(TextOutputFormat.class);
        TextOutputFormat.setOutputPath(job, new Path("hdfs://..."));
        // 等待执行
        boolean b = job.waitForCompletion(true);
        // 0表示正常退出
        return b?0:1;
    }

    public static void main(String[] args) throws Exception {
        int exitCode = ToolRunner.run(new Configuration(), new JobMain(), args);
        System.exit(exitCode);
    }
}
