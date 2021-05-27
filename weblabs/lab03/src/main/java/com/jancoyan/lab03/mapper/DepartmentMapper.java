package com.jancoyan.lab03.mapper;

import com.jancoyan.lab03.pojo.Department;
import org.apache.ibatis.annotations.Select;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface DepartmentMapper {

    @Select("select * from tbl_dept")
    List<Department> getAll();

}
