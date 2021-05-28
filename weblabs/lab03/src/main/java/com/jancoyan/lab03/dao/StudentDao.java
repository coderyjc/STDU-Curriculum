/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/27
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.dao;

import com.jancoyan.lab03.mapper.StudentMapper;
import com.jancoyan.lab03.pojo.Student;
import org.apache.ibatis.annotations.Param;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public class StudentDao {

    @Autowired
    private StudentMapper studentMapper;

    public List<Student> findAll(){
        return studentMapper.findAll();
    }


    public boolean deleteStudentById(Integer id) {
        return studentMapper.deleteStudentByPrimaryKey(id);
    }

    public Integer getStudentMaxId() {
        return studentMapper.getStudentMaxId();
    }

    public void updateStudent(Student student) {
        studentMapper.updateStudent(
                student.getId(),
                student.getName(),
                student.getAge(),
                student.getSex(),
                student.getGrade(),
                student.getBirthday(),
                student.getDept(),
                student.getTelphone(),
                student.getQq());
    }

    public void insertStudent(Student student) {
        studentMapper.insertStudent(
                student.getId(),
                student.getName(),
                student.getAge(),
                student.getSex(),
                student.getGrade(),
                student.getBirthday(),
                student.getDept(),
                student.getTelphone(),
                student.getQq());
    }
}
