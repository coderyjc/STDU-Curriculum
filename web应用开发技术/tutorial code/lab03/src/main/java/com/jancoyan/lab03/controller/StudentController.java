/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.controller;

import com.github.pagehelper.PageInfo;
import com.jancoyan.lab03.pojo.Student;
import com.jancoyan.lab03.service.StudentService;
import com.jancoyan.lab03.utils.Msg;
import com.jancoyan.lab03.utils.TimeUtils;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;


@Controller
public class StudentController {

    @Autowired
    private StudentService studentService;

    /**
     * RESTful
     * /students
     *  - GET 获取所有学生信息
     *  - DELETE 删除一条记录
     *  - POST 修改一条记录
     *  - PUT 插入一条记录
     */

    /**
     * 获取所有学生的分页列表
     * @param page 第几页
     * @param limit 一页多少数据
     * @return layui要求的json数据
     */
    @RequestMapping(value = "/students", method = RequestMethod.GET)
    @ResponseBody
    public Msg getStudentsByPage(Integer page, Integer limit){
        PageInfo<Student> pageInfo = studentService.findAll(page, limit);
        return Msg.success().add("count", pageInfo.getTotal()).add("data", pageInfo);
    }

    /**
     * 删除一条记录
     * @param id 主键
     * @return 删除状态消息
     */
    @RequestMapping(value = "/students", method = RequestMethod.DELETE)
    @ResponseBody
    public Msg deleteStudent(Integer id){
        studentService.deleteStudentById(id);
        return Msg.success();
    }

    /**
     * 更新学生信息
     * @param id 学号
     * @param name 姓名
     * @param age 年龄
     * @param sex 性别
     * @param grade 年级
     * @param birthday 生日
     * @param dept 学院
     * @param telphone 电话
     * @param qq qq
     * @return 消息
     */
    @RequestMapping(value = "/students", method = RequestMethod.POST)
    @ResponseBody
    public Msg updateStudent(Integer id,
                             String name,
                             Integer age,
                             Integer sex,
                             Integer grade,
                             String birthday,
                             Integer dept,
                             String telphone,
                             String qq){
        Student student = new Student();
        student.setId(id);
        student.setAge(age);
        student.setBirthday(TimeUtils.castDateStringToDateTypeYMD(birthday));
        student.setDept(dept);
        student.setGrade(grade);
        student.setSex(sex);
        student.setName(name);
        student.setTelphone(telphone);
        student.setQq(qq);
        studentService.updateStudent(student);
        return Msg.success();
    }

    /**
     * 添加学生信息
     * @param id 学号
     * @param name 姓名
     * @param age 年龄
     * @param sex 性别
     * @param grade 年级
     * @param birthday 生日
     * @param dept 学院
     * @param telphone 电话
     * @param qq qq
     * @return 消息
     */
    @RequestMapping(value = "/students", method = RequestMethod.PUT)
    @ResponseBody
    public Msg insertStudent(Integer id,
                             String name,
                             Integer age,
                             Integer sex,
                             Integer grade,
                             String birthday,
                             Integer dept,
                             String telphone,
                             String qq){
        Student student = new Student();
        student.setId(id);
        student.setAge(age);
        student.setBirthday(TimeUtils.castDateStringToDateTypeYMD(birthday));
        student.setDept(dept);
        student.setGrade(grade);
        student.setSex(sex);
        student.setName(name);
        student.setTelphone(telphone);
        student.setQq(qq);
        System.out.println(student);
        studentService.insertStudent(student);
        return Msg.success();
    }


    /**
     * 获取最高学生序号，用于添加学生时候的学号填充
     * @return 消息
     */
    @RequestMapping(value = "/maxid", method = RequestMethod.GET)
    @ResponseBody
    public Msg getStudentMaxId(){
        Integer id = studentService.getStudentMaxId();
        return Msg.success().add("id", id);
    }
}
