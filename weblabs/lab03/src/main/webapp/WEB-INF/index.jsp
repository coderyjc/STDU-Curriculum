<%@ page contentType="text/html;charset=UTF-8" language="java" %>


<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>lab03</title>
<%--    <script src="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/layui.min.js" integrity="sha512-oXOXRWbCoIxnjpKGxUYbZ5DC0pQJzgKV72sC/F+vCZXpz63NNAVDUGkzxuTVdx7cLwUz6Bt3DjcHviQwNqoHNw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>--%>
<%--    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/css/layui.min.css" integrity="sha512-e3/5WX6u9vRRITzzgruZq1yspUQr1jUc/wdzsw2gKzU7ibNQWZYv1OX+w/9fqeZWjapWTJNaFtMxZqrfs4UKmw==" crossorigin="anonymous" referrerpolicy="no-referrer" />--%>
    <script src="/layui/layui.js"></script>
    <script src="/js/index.js"></script>
    <link rel="stylesheet" href="/css/index.css">
    <link rel="stylesheet" href="/layui/css/layui.css">
</head>
<style>
    body{
        text-align: center;
    }
    h1{
        margin: 20px 0;
    }
    .main{
        margin: 30px auto;
        width: 85%;
    }

</style>
<body>

<h1>SpringBoot + LayUI 简易学生信息管理系统</h1>

<div class="main">
    <table id="student-list"  class="layui-hide" lay-filter="student-list"></table>
</div>

<div class="layui-btn-group demoTable">
    <button class="layui-btn" data-type="addStudent">添加学生</button>
    <button class="layui-btn layui-btn-danger" data-type="batchDelete">批量删除</button>
</div>

<!-- 添加、编辑、查看的模态框 -->
<div id="myModal" class="modal">
    <div class="modal-content">
        <fieldset class="layui-elem-field layui-field-title" style="margin-top: 20px;">
            <legend>标题</legend>
        </fieldset>
        <form class="layui-form" action="" lay-filter="information" method="post">
            <div class="layui-form-item">
                <label class="layui-form-label">id</label>
                <div class="layui-input-block">
                    <input id="modal-student-id" type="text" name="id" autocomplete="off"
                           placeholder="不可编辑" class="layui-input" disabled="disabled"
                           lay-verify="required">
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">姓名</label>
                <div class="layui-input-block">
                    <input id="modal-student-name" type="text" name="name" autocomplete="off"
                           placeholder="请输入姓名" class="layui-input" lay-verify="required">
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">年级</label>
                <div class="layui-input-block">
                    <select id="modal-student-grade" name="grade" lay-filter="grade"
                            lay-verify="required">
                        <option value="" selected></option>
                        <option value="1">1</option>
                        <option value="2">2</option>
                        <option value="3">3</option>
                        <option value="4">4</option>
                        <option value="5">5</option>
                    </select>
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">学院</label>
                <div class="layui-input-block">
                    <select id="modal-dept-list" name="dept" lay-filter="dept"
                            lay-verify="required">
                        <option value="" selected></option>
                        <option value="0">土木工程学院</option>
                        <option value="1">机械工程学院</option>
                        <option value="2">经济学院</option>
                        <option value="3">文法学院</option>
                        <option value="4">交通运输学院</option>
                        <option value="5">建筑与艺术学院</option>
                        <option value="6">电气与电子工程学院</option>
                        <option value="7">信息科学与技术学院</option>
                        <option value="8">工程力学系学院</option>
                        <option value="9">数理系</option>
                        <option value="10">外语系</option>
                        <option value="11">管理学院</option>
                        <option value="12">医学院</option>
                    </select>
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">性别</label>
                <div class="layui-input-block">
                    <select id="modal-student-sex" name="sex" lay-filter="sex"
                            lay-verify="required">
                        <option value="" selected></option>
                        <option value="0">女</option>
                        <option value="1">男</option>
                    </select>
                </div>
            </div>

            <div class="layui-form-item" style="float: left">
                <div class="layui-inline">
                    <label class="layui-form-label">出生日期</label>
                    <div class="layui-input-block">
                        <input type="text" class="layui-input" id="modal-student-birthday"
                              name="birthday" placeholder="yyyy-MM-dd" style="width: 350px" lay-verify="required">
                    </div>
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">QQ号</label>
                <div class="layui-input-block">
                    <input id="modal-student-qq" type="text" name="qq" autocomplete="off"
                           placeholder="qq号" class="layui-input" lay-verify="qq">
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">手机号</label>
                <div class="layui-input-block">
                    <input id="modal-student-tel" type="text" name="telphone" lay-verify="phone"
                           autocomplete="off"
                           placeholder="手机号" class="layui-input">
                </div>
            </div>

            <div class="layui-form-item">
                <div id="modal-buttons" class="layui-input-block">
                    <button id="update-btn" type="submit" class="layui-btn" lay-submit
                            lay-filter="update">修改
                    </button>
                    <button id="insert-btn" type="submit" class="layui-btn" lay-submit
                            lay-filter="insert">添加
                    </button>
                    <button type="button" id="return-to-index"
                            class="layui-btn layui-btn-primary">返回</button>
                </div>
            </div>
        </form>
    </div>
</div>

<script type="text/html" id="toolBar">
    <a class="layui-btn layui-btn-primary layui-btn-xs" lay-event="detail">查看</a>
    <a class="layui-btn layui-btn-xs" lay-event="edit">编辑</a>
    <a class="layui-btn layui-btn-danger layui-btn-xs" lay-event="del">删除</a>
</script>

</body>
</html>