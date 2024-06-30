/**
 * @Author: Yan Jingcun
 * @Date: 2021/5/27
 * @Description:
 * @Version: 1.0
 */

package com.jancoyan.lab03.dao;

import com.jancoyan.lab03.mapper.DepartmentMapper;
import com.jancoyan.lab03.pojo.Department;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public class DepartmentDao {

    @Autowired
    DepartmentMapper departmentMapper;

    public List<Department> getAll() {
        return departmentMapper.getAll();
    }
}
