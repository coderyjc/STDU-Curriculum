<%--
  Created by Jancoyan.
  User: Jancoyan
  Date: 2021/5/23
  Time: 18:12
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
    <title>Title</title>
    <base href="<%=basePath%>"/>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/layui.min.js" integrity="sha512-oXOXRWbCoIxnjpKGxUYbZ5DC0pQJzgKV72sC/F+vCZXpz63NNAVDUGkzxuTVdx7cLwUz6Bt3DjcHviQwNqoHNw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/css/layui.min.css" integrity="sha512-e3/5WX6u9vRRITzzgruZq1yspUQr1jUc/wdzsw2gKzU7ibNQWZYv1OX+w/9fqeZWjapWTJNaFtMxZqrfs4UKmw==" crossorigin="anonymous" referrerpolicy="no-referrer" />
</head>

<style type="text/css">
    html{
        width: 100%;
        height: 100%;
    }

    body{
        background-image: url(./static/img/personal-form-bg.png);
        background-position: 100% 100%;
    }

    .personal-info-container{
        width: 50%;
        margin: 10px auto;
        background-color: white;
        padding: 2rem;
        border-radius: 10px;
        opacity: 0.9;
    }

    .title{
        text-align: center;
        margin-bottom: 30px;
    }

    #btn-group{
        float: right;
        margin-right: 30px;
    }
</style>

<body>

<div class="personal-info-container">
    <h1 class="title">个人信息填写</h1>
    <form class="layui-form layui-form-pane" action="saveData.jsp" method="post">
        <div class="layui-form-item">
            <label class="layui-form-label">用户名</label>
            <div class="layui-input-block">
                <input type="text" name="userName" required  lay-verify="required"
                       placeholder="请输入用户名" autocomplete="off" class="layui-input">
            </div>
        </div>
        <div class="layui-form-item">
            <label class="layui-form-label">邮箱</label>
            <div class="layui-input-block">
                <input type="text" name="userEmail" autocomplete="off" placeholder="请输入邮箱"
                       class="layui-input">
            </div>
        </div>
        <div class="layui-form-item">
            <label class="layui-form-label">真实姓名</label>
            <div class="layui-input-block">
                <input type="text" name="realName" required  lay-verify="required"
                       placeholder="请输入真实姓名" autocomplete="off" class="layui-input">
            </div>
        </div>
        <div class="layui-form-item">
            <label class="layui-form-label">性别</label>
            <div class="layui-input-block">
                <input type="radio" name="sex" value="1" title="男" checked>
                <input type="radio" name="sex" value="0" title="女" >
            </div>
        </div>
        <div class="layui-form-item">
            <label class="layui-form-label">居住地</label>
            <div class="layui-input-block">
                <select name="city" lay-verify="required">
                    <option value=""></option>
                    <option value="0">北京</option>
                    <option value="1">上海</option>
                    <option value="2">广州</option>
                    <option value="3">深圳</option>
                    <option value="4">杭州</option>
                </select>
            </div>
        </div>
        <div class="layui-form-item">
            <div class="layui-inline">
                <label class="layui-form-label">出生日期</label>
                <div class="layui-input-inline">
                    <input name="birthdate" type="text" class="layui-input" id="birthdate"
                           placeholder="yyyy-MM-dd">
                </div>
            </div>
        </div>
        <div class="layui-form-item">
            <label class="layui-form-label">研究方向</label>
            <div class="layui-input-block">
                <input type="checkbox" name="web" value="web" title="Web开发">
                <input type="checkbox" name="machine" value="machine" title="机器学习">
                <input type="checkbox" name="bigdata" value="bigdata" title="大数据分析">
                <input type="checkbox" name="database" value="database" title="数据库开发">
            </div>
        </div>
        <div class="layui-form-item layui-form-text">
            <label class="layui-form-label">个人简介</label>
            <div class="layui-input-block">
                <textarea name="personal-info" placeholder="请输入内容"
                          class="layui-textarea"></textarea>
            </div>
        </div>
        <div class="layui-form-item">
            <div class="layui-input-block" id="btn-group">
                <button type="submit" class="layui-btn" lay-submit="" lay-filter="*">立即提交</button>
                <button type="reset" class="layui-btn layui-btn-primary">重置</button>
            </div>
        </div>
    </form>
</div>

<script>

    layui.use('form', function(){
        var form = layui.form;

        form.on('submit(*)', function(data){
            // console.log(data.field);
        });
    });

    layui.use('laydate', function(){
        var laydate = layui.laydate;
        laydate.render({
            elem: '#birthdate'
        });
    })
</script>

</body>
</html>