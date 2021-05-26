/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.mapperTest;

import com.jancoyan.lab03.Lab03ApplicationTests;
import com.jancoyan.lab03.mapper.StudentMapper;
import com.jancoyan.lab03.pojo.Student;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.List;

public class StudentMapperTest extends Lab03ApplicationTests {

    @Autowired
    private StudentMapper mapper;

    @Test
    void findAllTest(){
        List<Student> list = mapper.findAll();
        for(int i = 0; i < 10; i++){
            System.out.println(list.get(i));
        }

    }


}
