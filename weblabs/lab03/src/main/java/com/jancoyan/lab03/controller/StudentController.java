/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/26
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.controller;

import com.alibaba.fastjson.JSONObject;
import com.github.pagehelper.PageHelper;
import com.github.pagehelper.PageInfo;
import com.jancoyan.lab03.pojo.Student;
import com.jancoyan.lab03.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

@Controller
public class StudentController {

    @Autowired
    private StudentService service;

    @RequestMapping("/students")
    @ResponseBody
    public JSONObject getStudentsByPage(Integer page, Integer limit){
        PageHelper.startPage(page, limit);
        List<Student> list = service.findAll();
        PageInfo<Student> pageInfo = new PageInfo<>(list);
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("code", 0);
        jsonObject.put("msg", "");
        jsonObject.put("count", limit);
        jsonObject.put("data", pageInfo);
        return jsonObject;
    }



}
