/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/4
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowPart;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import org.apache.hadoop.io.WritableComparable;

import java.io.DataInput;
import java.io.DataOutput;
import java.io.IOException;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class FlowBean implements WritableComparable<FlowBean> {

    private Integer upFlow; //上行数据包数
    private Integer downFlow; //下行数据包数
    private Integer upCountFlow; //上行流量总和
    private Integer downCountFlow; //下行流量总和


    @Override
    public int compareTo(FlowBean o) {
        return o.getUpFlow() - this.upFlow;
    }

    @Override
    public void write(DataOutput dataOutput) throws IOException {
        dataOutput.write(upFlow);
        dataOutput.write(downFlow);
        dataOutput.write(upCountFlow);
        dataOutput.write(downCountFlow);
    }

    @Override
    public void readFields(DataInput dataInput) throws IOException {
        this.upFlow = dataInput.readInt();
        this.downFlow = dataInput.readInt();
        this.upCountFlow = dataInput.readInt();
        this.downCountFlow = dataInput.readInt();
    }
}
