/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class Student {

    private Integer id;
    private String name;
    private Integer age;
    private Integer sex;
    private Integer grade;
    private Date birthday;
    private Integer dept;
    private String telphone;
    private String qq;

}
