/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/27
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.controller;

import com.jancoyan.lab03.pojo.Department;
import com.jancoyan.lab03.service.DepartmentService;
import com.jancoyan.lab03.utils.Msg;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.List;

@Controller
public class DepartmentController {

    @Autowired
    DepartmentService departmentService;

    @RequestMapping(value = "/depts", method = RequestMethod.GET)
    @ResponseBody
    public Msg getDepts(){
        List<Department> list = departmentService.getAll();
        return Msg.success().add("list", list);
    }


}
