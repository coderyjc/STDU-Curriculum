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
    private int deptid;
    private String deptname;
    private String location;
}
