package com.jancoyan.lab03;

import org.mybatis.spring.annotation.MapperScan;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
@MapperScan("com.jancoyan.lab03.mapper")
public class Lab03Application{

    public static void main(String[] args) {
        SpringApplication.run(Lab03Application.class, args);
    }

}
