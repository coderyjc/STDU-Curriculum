package com.jancoyan.lab03;

import org.junit.jupiter.api.Test;
import org.springframework.boot.test.context.SpringBootTest;


import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Random;

@SpringBootTest
public class Lab03ApplicationTests {

    @Test
    void contextLoads() {
    }


    @Test
    void generateSql(){

        Random r = new Random();

        for(int i = 1500; i < 2001; i++){



        String strBase = "qwertyuioplkjhgfdsazxcbvnm";
        // nextInt = [0,2)
        int lowIdx = r.nextInt(21);
        // 学号用循环生成
        // 随机姓名
        String name = strBase.substring(lowIdx, lowIdx + 4);
        // 随机年龄
        int age = r.nextInt(20) + 10;
        // 随机性别
        int sex = r.nextInt(2);
        // 随机年级
        int grade = 1 + r.nextInt(5);
        // 生日
        int year = 1990 + r.nextInt(30);
        int month = 1 + r.nextInt(12);
        int day = 1 + r.nextInt(29);
//        学院
        int dept = 1 + r.nextInt(12);
//        电话号码
        int tel_1 = 100000 + r.nextInt(100000);
        int tel_2 = 10000 + r.nextInt(10000);
//       qq号
        int qq = r.nextInt(100000000) + 100000000;

        String sql = "INSERT INTO tbl_student VALUES("+i+" , '" + name + "', " + age + ", "+sex+
                ", " +
                ""+ grade +", " +
                "'"+year+"-"+month+"-"+day+"', " +
                ""+dept+", '"+tel_1+tel_2+"', '"+qq+"');";
            System.out.println(sql);
        }
    }

}
