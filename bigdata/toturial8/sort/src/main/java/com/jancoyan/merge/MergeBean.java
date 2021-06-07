/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/7
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.merge;

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
public class MergeBean implements WritableComparable<MergeBean> {

    private String str;
    private String val;


    @Override
    public int compareTo(MergeBean o) {
        return this.str.compareTo(o.getStr());
    }

    @Override
    public void write(DataOutput dataOutput) throws IOException {
        dataOutput.write(Integer.parseInt(str));
        dataOutput.write(Integer.parseInt(val));
    }

    @Override
    public void readFields(DataInput dataInput) throws IOException {
        this.str = dataInput.readUTF();
        this.val = dataInput.readUTF();
    }
}
