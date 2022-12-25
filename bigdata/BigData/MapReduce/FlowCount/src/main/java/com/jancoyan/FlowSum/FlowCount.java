/**
 * @Author: Yan Jingcun
 * @Date: 2021/6/3
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.FlowSum;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class FlowCount {

    private Integer upFlow;  //上行数据包数
    private Integer downFlow;  //下行数据包数
    private Integer upCountFlow; //上行流量总和
    private Integer downCountFlow;//下行流量总和

}
