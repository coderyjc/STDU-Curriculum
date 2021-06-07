/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/7
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.sort;

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
public class SortBean implements WritableComparable<SortBean> {

    private Integer number;

    @Override
    public String toString() {
        return " number=" + number;
    }

    @Override
    public int compareTo(SortBean o) {
        return this.number.compareTo(o.getNumber());
    }

    @Override
    public void write(DataOutput dataOutput) throws IOException {
        dataOutput.write(number);
    }

    @Override
    public void readFields(DataInput dataInput) throws IOException {
        this.number = dataInput.readInt();
    }
}
