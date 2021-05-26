<%--
  Created by Jancoyan.
  User: Jancoyan
  Date: 2021/5/26
  Time: 16:21
 --%>

<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>SpringBoot学生管理</title>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/layui.min.js" integrity="sha512-oXOXRWbCoIxnjpKGxUYbZ5DC0pQJzgKV72sC/F+vCZXpz63NNAVDUGkzxuTVdx7cLwUz6Bt3DjcHviQwNqoHNw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/css/layui.min.css" integrity="sha512-e3/5WX6u9vRRITzzgruZq1yspUQr1jUc/wdzsw2gKzU7ibNQWZYv1OX+w/9fqeZWjapWTJNaFtMxZqrfs4UKmw==" crossorigin="anonymous" referrerpolicy="no-referrer" />
</head>
<body>

<table id="student-list"></table>

<script type="text/javascript">

    layui.use('table', function(){
        var table = layui.table;
        table.render({
            elem: '#student-list'
            ,height: 600
            ,url: '/students' //数据接口
            ,parseData: function(res){ //res 即为原始返回的数据
                return {
                    "code": res.code, //解析接口状态
                    "msg": res.msg, //解析提示文本
                    "count": res.count, //解析数据长度
                    "data": res.data.list //解析数据列表
                };
            }
            ,page: true //开启分页
            ,cols: [[ //表头
                {field: 'id', title: 'ID', width:80, sort: true, fixed: 'left'}
                ,{field: 'name', title: '姓名', width:80}
                ,{field: 'age', title: '年龄', width:80}
                ,{field: 'sex', title: '性别', width:80}
                ,{field: 'grade', title: '年级', width: 100}
                ,{field: 'birthday', title: '生日', width: 300, sort: true}
                ,{field: 'dept', title: '院系', width: 80, sort: true}
                ,{field: 'tel', title: '电话', width: 80}
                ,{field: 'qq', title: 'QQ', width: 135, sort: true}
            ]]
        });

    });
</script>

</body>
</html>