<%--
  Created by Jancoyan.
  User: Jancoyan
  Date: 2021/5/23
  Time: 19:32
 --%>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%
    String basePath = request.getScheme() + "://" +
            request.getServerName() + ":" + request.getServerPort() +
            request.getContextPath() + "/";
%>

<!DOCTYPE html>
<html>
<head>
    <title>showInfo</title>
    <base href="<%=basePath%>"/>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/layui.min.js" integrity="sha512-oXOXRWbCoIxnjpKGxUYbZ5DC0pQJzgKV72sC/F+vCZXpz63NNAVDUGkzxuTVdx7cLwUz6Bt3DjcHviQwNqoHNw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
     <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/css/layui.min.css" integrity="sha512-e3/5WX6u9vRRITzzgruZq1yspUQr1jUc/wdzsw2gKzU7ibNQWZYv1OX+w/9fqeZWjapWTJNaFtMxZqrfs4UKmw==" crossorigin="anonymous" referrerpolicy="no-referrer" />
</head>
<style type="text/css">

    #main-container{
        width: 60%;
        margin: 5% auto;
    }

    .show-info-title{
        text-align: center;
        margin: 20px 0;
    }

    table{
        text-align: center;
    }

    #personal-info-panel{
        padding-left:5%;
        padding-right:5%;
    }
</style>
<body>
<div id="main-container" class="layui-row layui-col-space15">
    <div class="layui-col-md">
        <div id="personal-info-panel" class="layui-panel">
            <h1 class="show-info-title">个人信息展示</h1>
            <table class="layui-table">
                <colgroup>
                    <col width="150">
                    <col>
                </colgroup>
                <tbody>
                <tr>
                    <td>用户名</td>
                    <td>2016-11-29</td>
                </tr>
                <tr>
                    <td>邮箱</td>
                    <td>2016-11-28</td>
                </tr>
                <tr>
                    <td>性别</td>
                    <td>2016-11-28</td>
                </tr>
                <tr>
                    <td>真实姓名</td>
                    <td>2016-11-28</td>
                </tr>
                <tr>
                    <td>居住地</td>
                    <td>2016-11-28</td>
                </tr>
                <tr>
                    <td>出生日期</td>
                    <td>2016-11-28</td>
                </tr>
                <tr>
                    <td>研究方向</td>
                    <td>2016-11-28</td>
                </tr>
                <tr>
                    <td>个人简介</td>
                    <td>2016-11-28</td>
                </tr>
                </tbody>
            </table>
        </div>
    </div>
</div>
</body>
</html>
