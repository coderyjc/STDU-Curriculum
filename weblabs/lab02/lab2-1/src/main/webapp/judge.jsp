<%--
  Created by Jancoyan.
  User: Jancoyan
  Date: 2021/5/21
  Time: 14:50
--%>

<%@ page contentType="text/html;charset=UTF-8" language="java"  pageEncoding="UTF-8" %>

<%
    String basePath = request.getScheme() + "://" +
            request.getServerName() + ":" + request.getServerPort() +
            request.getContextPath() + "/";
%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>登录状态</title>
    <base href="<%=basePath%>"/>
    <link href="https://cdn.bootcdn.net/ajax/libs/twitter-bootstrap/5.0.1/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://cdn.bootcdn.net/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="https://cdn.bootcdn.net/ajax/libs/twitter-bootstrap/5.0.1/js/bootstrap.min.js"></script>
</head>
<body>
<%
    response.setCharacterEncoding("utf-8");

    String userName = request.getParameter("userName");
    String userPwd = request.getParameter("userPwd");

    if("jsj".equals(userName) && "123".equals(userPwd)){
        Integer count = (Integer) application.getAttribute("loginCount");
        if( null == count){
            application.setAttribute("loginCount", 1);
        } else {
            application.setAttribute("loginCount", count + 1);
        }
        response.sendRedirect("success.jsp");
    }else{
%>

<jsp:forward page="fail.html"></jsp:forward>

<%
    }
%>

</body>
</html>