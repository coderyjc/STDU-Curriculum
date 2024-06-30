/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/27
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Department {

    // INT(2) PRIMARY_KEY 院系号
    private int deptid;

    // VARCHAR(20) 院系名称
    private String deptname;

    // VARCHAR(50)  院系地址
    private String location;
}
