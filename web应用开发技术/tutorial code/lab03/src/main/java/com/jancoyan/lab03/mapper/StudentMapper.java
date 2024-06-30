package com.jancoyan.lab03.mapper;

import com.jancoyan.lab03.pojo.Student;
import org.apache.ibatis.annotations.*;
import org.springframework.stereotype.Repository;

import java.util.Date;
import java.util.List;

@Repository
public interface StudentMapper {

    // 查询所有学生
    @Select("select * from tbl_student")
    List<Student> findAll();

    // 查询最大id
    @Select("select max(id) from tbl_student")
    Integer getStudentMaxId();

    // 删除学生
    @Delete("delete from tbl_student where id = #{id}")
    boolean deleteStudentByPrimaryKey(@Param("id") Integer id);

    // 插入学生
    @Insert("insert into tbl_student values(#{id}, #{name}, #{age}, #{sex}, #{grade}, " +
            "#{birthday}, #{dept}, #{telphone}, #{qq})")
    void insertStudent(@Param("id") Integer id,
                       @Param("name") String name,
                       @Param("age") Integer age,
                       @Param("sex")Integer sex,
                       @Param("grade")Integer grade,
                       @Param("birthday")Date birthday,
                       @Param("dept")Integer dept,
                       @Param("telphone")String telphone,
                       @Param("qq")String qq);
    // 更新学生
    @Update("update tbl_student set name=#{name}, age=#{age}, sex=#{sex}, grade=#{grade}, " +
            "birthday=#{birthday}, dept=#{dept}, telphone=#{telphone}, qq=#{qq} where id = #{id}")
    void updateStudent(@Param("id") Integer id,
                       @Param("name") String name,
                       @Param("age") Integer age,
                       @Param("sex")Integer sex,
                       @Param("grade")Integer grade,
                       @Param("birthday")Date birthday,
                       @Param("dept")Integer dept,
                       @Param("telphone")String telphone,
                       @Param("qq")String qq);

}
