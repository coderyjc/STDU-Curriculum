<%@ page import="com.jancoyan.lab2_2.pojo.User" %><%--
  Created by Jancoyan.
  User: Jancoyan
  Date: 2021/5/23
  Time: 19:28
 --%>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String basePath = request.getScheme() + "://" +
            request.getServerName() + ":" + request.getServerPort() +
            request.getContextPath() + "/";
    response.setCharacterEncoding("utf-8");
//    进行信息的存放
    User user = new User();
//    将所有信息存放到对象中
    String name = request.getParameter("userName");
    String email = request.getParameter("userEmail");
    String sex = request.getParameter("sex");
    String realName = request.getParameter("realName");
    String location = request.getParameter("city");
    String date = request.getParameter("like");
    String dire = request.getParameter("birthdate");
    String info = request.getParameter("personal-info");
    System.out.println(name);
    System.out.println(email);
    System.out.println(sex);
    System.out.println(realName);
    System.out.println(location);
    System.out.println(date);
    System.out.println(dire);
    System.out.println(info);
%>

<!DOCTYPE html>
<html>
<head>
    <title>Title</title>
    <base href="<%=basePath%>"/>
</head>
<body>
</body>
</html>