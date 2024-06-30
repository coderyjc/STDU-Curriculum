<%@ page import="com.jancoyan.lab2_2.pojo.*" %>
<%@ page import="com.jancoyan.lab2_2.utils.*" %>
<%@ page import="java.nio.charset.StandardCharsets" %>

<%--  Created by Jancoyan.
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
    String name = request.getParameter("userName");
    String email = request.getParameter("userEmail");
    String sex = request.getParameter("sex");
    String realName = request.getParameter("realName");
    String location = request.getParameter("city");
    String date = request.getParameter("birthdate");
    String info = request.getParameter("personal-info");
    user.setUserName(new String(name.getBytes(StandardCharsets.ISO_8859_1)));
    user.setUserEmail(new String(name.getBytes(StandardCharsets.ISO_8859_1)));
    user.setUserSex(Integer.parseInt(sex));
    user.setUserEmail(new String(email.getBytes(StandardCharsets.ISO_8859_1)));
    user.setUserRealName(new String(realName.getBytes(StandardCharsets.ISO_8859_1)));
    user.setUserLocation(UserLocationUtil.getLocation(Integer.parseInt(location)));
    user.setPersonalInfo(new String(info.getBytes(StandardCharsets.ISO_8859_1)));
    user.setBirthDate(DateUtils.castDateStringToDateTypeYMD(date));
//    将信息存入变量
    session.setAttribute("flag", user);

%>

<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>信息存放</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/layui.min.js" integrity="sha512-oXOXRWbCoIxnjpKGxUYbZ5DC0pQJzgKV72sC/F+vCZXpz63NNAVDUGkzxuTVdx7cLwUz6Bt3DjcHviQwNqoHNw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/css/layui.min.css" integrity="sha512-e3/5WX6u9vRRITzzgruZq1yspUQr1jUc/wdzsw2gKzU7ibNQWZYv1OX+w/9fqeZWjapWTJNaFtMxZqrfs4UKmw==" crossorigin="anonymous" referrerpolicy="no-referrer" />
    <base href="<%=basePath%>"/>
</head>
<style>

    #notice-card{
        margin: 10% auto;
        text-align: center;
        width: 30%;
    }

    button{
        margin-bottom: 10px;
    }

</style>
<body>
    <div id="notice-card" class="layui-bg-gray" style="padding: 30px;">
        <div class="layui-row layui-col-space15">
            <div class="layui-col-md">
                <div class="layui-card">
                    <div class="layui-card-header">提示</div>
                    <div class="layui-card-body">
                        信息已经保存，点击按钮跳转到信息查看页面
                    </div>
                    <a href="./showData.jsp"><button type="button" class="layui-btn layui-btn-primary">查看信息</button></a>
                    <a href="./index.html"><button type="button" class="layui-btn">重新提交</button></a>
                </div>
            </div>
        </div>
    </div>
</body>
</html>