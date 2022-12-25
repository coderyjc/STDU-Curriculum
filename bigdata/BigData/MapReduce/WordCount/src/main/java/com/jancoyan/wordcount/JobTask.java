/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/30
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.wordcount;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.conf.Configured;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.hadoop.mapreduce.lib.output.TextOutputFormat;
import org.apache.hadoop.util.Tool;
import org.apache.hadoop.util.ToolRunner;

import java.net.URI;

public class JobTask extends Configured implements Tool {

    @Override
    public int run(String[] strings) throws Exception {
        Job job = Job.getInstance(super.getConf(), JobTask.class.getSimpleName());
        job.setJarByClass(JobTask.class);
        //第一步 读入文件解析成kv对
        job.setInputFormatClass(TextInputFormat.class);
        TextInputFormat.addInputPath(job, new Path("hdfs://"));
        //第二步 设置mapper类
        job.setMapperClass(WordCountMapper.class);
        job.setMapOutputKeyClass(Text.class);
        job.setMapOutputValueClass(LongWritable.class);
        // 3456 步默认处理
        //第七步 设置reducer类
        job.setReducerClass(WordCountReducer.class);
        job.setOutputKeyClass(Text.class);
        job.setOutputValueClass(LongWritable.class);
        //第八步 输出文件的建立
        job.setOutputFormatClass(TextOutputFormat.class);
//        TextOutputFormat.setOutputPath(job, new Path("hdfs://"));
        //设置输出路径
        Path path = new Path("hdfs://输出路径");
        TextOutputFormat.setOutputPath(job, path);
        // 获取FileSystem
        FileSystem fileSystem = FileSystem.get(new URI("hdfs://输出路径"), super.getConf());
        // 如果存在就删除
        boolean bl = fileSystem.exists(path);
        if(bl){
            fileSystem.delete(path, true);
        }
        boolean b = job.waitForCompletion(true);
        return b ? 0 : 1;
    }


    public static void main(String[] args) throws Exception {
        Configuration configuration = new Configuration();
        Tool tool = new JobTask();
        int code = ToolRunner.run(configuration, tool, args);
        System.exit(code);
    }

}
