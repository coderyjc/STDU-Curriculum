/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/1
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.WordCountCombiner;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

public class JobMain extends Configured implements Tool {

    @Override
    public int run(String[] strings) throws Exception {
        // 第一步，创造实例，创建输入流
        Job job = Job.getInstance(super.getConf(), "word_count_combiner_test");

        job.setInputFormatClass(TextInputFormat.class);
        TextInputFormat.addInputPath(job, new Path("hdfs://127.0.0.1"));

        // 第二步，设置map类和mapKV
        job.setMapperClass(WordCountCMapper.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(LongWritable.class);

        // 第三四五六步，排序，规约，分组
        job.setCombinerClass(WordCountCombiner.class);
        // 其他使用默认配置

        // 第七步 设置reduce类和KV
        job.setReducerClass(WordCountCReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(LongWritable.class);

        // 第八步，设置输出类，等待任务执行结束
        job.setOutputFormatClass(TextOutputFormat.class);
        TextOutputFormat.setOutputPath(job, new Path("hdfs://127.0.0.1"));

        boolean b = job.waitForCompletion(true);
        return b ? 0 : 1;
    }

    public static void main(String[] args) throws Exception {
        int exeCode = ToolRunner.run(new Configuration(), new JobMain(), args);
        System.exit(exeCode);
    }
}
