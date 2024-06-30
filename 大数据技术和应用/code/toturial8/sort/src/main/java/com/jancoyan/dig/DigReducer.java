/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/17
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.dig;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class DigReducer extends Reducer<Text, Text, Text, Text> {

    List<Text> texts = new ArrayList<Text>();
    List<Text> sub = new ArrayList<Text>();

    @Override
    protected void reduce(Text key, Iterable<Text> values, Context context) throws IOException, InterruptedException {
        for (Text v : values) {
            String s = v.toString();
            if (v.toString().startsWith("-")) {
                sub.add(new Text(s.substring(1)));
            } else {
                texts.add(new Text(s.substring(1)));
            }
        }
        for (Text text : sub) {
            for (Text value : texts) {
                context.write(text, value);
            }
        }
        texts.clear();
        sub.clear();
    }
}
