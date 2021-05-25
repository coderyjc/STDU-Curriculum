package com.jancoyan.lab2_2.pojo;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

import java.util.Date;
import java.util.List;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class User {

    private String userName;
    private String userEmail;
    private Integer userSex;
    private String userRealName;
    private String userLocation;
    private Date birthDate;
    private List<String> searchDirection;
    private String personalInfo;

}
