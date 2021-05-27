/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/27
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.service;

import com.jancoyan.lab03.dao.DepartmentDao;
import com.jancoyan.lab03.pojo.Department;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class DepartmentService {

    @Autowired
    DepartmentDao departmentDao;

    public List<Department> getAll() {
        return departmentDao.getAll();
    }
}
