/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.service;

import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import com.jancoyan.lab03.dao.StudentDao;
import com.jancoyan.lab03.pojo.Student;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class StudentService {

    @Autowired
    StudentDao studentDao;

    public PageInfo<Student> findAll(Integer page, Integer limit){
        PageHelper.startPage(page, limit);
        List<Student> list = studentDao.findAll();
        return new PageInfo<>(list);
    }

    public void deleteStudentById(Integer id) {
        studentDao.deleteStudentById(id);
    }
}
