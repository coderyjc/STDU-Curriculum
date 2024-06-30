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

    // INT(10) PRIMARY_KEY 学号
    private Integer id;

    // VARCHAR(10) 学生姓名
    private String name;

    // INT(3) 年龄
    private Integer age;

    // INT(1) 性别
    private Integer sex;

    // INT(1) 年级
    private Integer grade;

    // DATE 生日
    private Date birthday;

    // INT(2) 院系
    private Integer dept;

    // VARCHAR(11) 电话号码
    private String telphone;

    // VARCHAR(10) qq号码
    private String qq;

}
