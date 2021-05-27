package com.jancoyan.lab03.mapper;

import com.jancoyan.lab03.pojo.Student;
import org.apache.ibatis.annotations.Delete;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.Select;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface StudentMapper {

    @Select("select * from tbl_student")
    List<Student> findAll();


    @Delete("delete from tbl_student where id = #{id}")
    boolean deleteStudentByPrimaryKey(@Param("id") Integer id);

}
