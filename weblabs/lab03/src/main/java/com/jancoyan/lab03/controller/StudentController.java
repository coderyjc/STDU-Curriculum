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


    @RequestMapping(value = "/students", method = RequestMethod.POST)
    @ResponseBody
    public Msg updateStudent(){
        return null;
    }

    @RequestMapping(value = "/students", method = RequestMethod.PUT)
    @ResponseBody
    public Msg insertStudent(){
        return null;
    }


}
