/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/4
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowPart;

import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Partitioner;

public class FlowCountPartition extends Partitioner<Text, FlowBean> {
    @Override
    public int getPartition(Text text, FlowBean flowBean, int i) {
        if(text.toString().startsWith("135")){
            return 0;
        } else if(text.toString().startsWith("136")) {
            return 1;
        }
        return 2;
    }
}
