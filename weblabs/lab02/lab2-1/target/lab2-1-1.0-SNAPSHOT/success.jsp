<%--
  Created by Jancoyan.
  User: Jancoyan
  Date: 2021/5/23
  Time: 14:57
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
    <title>Title</title>
    <base href="<%=basePath%>"/>
</head>
<body>
    登录成功，当前的登录次数为：<%=application.getAttribute("loginCount")%>
</body>
</html>