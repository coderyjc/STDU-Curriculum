/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/31
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.Bean;

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
public class PairWritable implements WritableComparable<PairWritable> {

    private String str;
    private Integer num;

    @Override
    public String toString() {
        return str + '\t' + num;

    }

    /**
     * 序列化对象
     * @param dataOutput 序列化对象
     * @throws IOException IOException
     */
    @Override
    public void write(DataOutput dataOutput) throws IOException {
        dataOutput.writeUTF(str);
        dataOutput.writeInt(num);
    }

    /**
     * 反序列化对象
     * @param dataInput 反序列化
     * @throws IOException 异常
     */
    @Override
    public void readFields(DataInput dataInput) throws IOException {
        this.str = dataInput.readUTF();
        this.num = dataInput.readInt();
    }


    @Override
    public int compareTo(PairWritable o) {
        /*
         第一列按照字典顺序进行排列
         第一列相同的时候, 第二列按照升序进行排列
        */

        int rst = this.str.compareTo(o.getStr());
        if (0 == rst){
            rst = this.num.compareTo(o.getNum());
        }
        return rst;
    }
}
