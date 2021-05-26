<%--
  Created by Jancoyan.
  User: Jancoyan
  Date: 2021/5/21
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
    <link href="https://cdn.bootcdn.net/ajax/libs/twitter-bootstrap/5.0.1/css/bootstrap.min.css" rel="stylesheet">
    <script src="https://cdn.bootcdn.net/ajax/libs/jquery/3.6.0/jquery.min.js"></script>
    <script src="https://cdn.bootcdn.net/ajax/libs/twitter-bootstrap/5.0.1/js/bootstrap.min.js"></script>
</head>
<body>

<div class="col-4" style="margin: 100px auto">
    <div class="card">
        <div class="card-header">
            Note:
        </div>
        <div class="card-body">
            <blockquote class="blockquote mb-0">
                登录成功，当前的登录次数为：<%=application.getAttribute("loginCount")%>
            </blockquote>
        </div>
    </div>
</div>

</body>
</html>