/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.service;

import com.jancoyan.lab03.mapper.StudentMapper;
import com.jancoyan.lab03.pojo.Student;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class StudentService {

    @Autowired
    StudentMapper mapper;

    public List<Student> findAll(){
        return mapper.findAll();
    }

}
