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
<%--    <script src="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/layui.min.js" integrity="sha512-oXOXRWbCoIxnjpKGxUYbZ5DC0pQJzgKV72sC/F+vCZXpz63NNAVDUGkzxuTVdx7cLwUz6Bt3DjcHviQwNqoHNw==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>--%>
<%--    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/layui/2.6.5/css/layui.min.css" integrity="sha512-e3/5WX6u9vRRITzzgruZq1yspUQr1jUc/wdzsw2gKzU7ibNQWZYv1OX+w/9fqeZWjapWTJNaFtMxZqrfs4UKmw==" crossorigin="anonymous" referrerpolicy="no-referrer" />--%>
    <script src="/layui/layui.js"></script>
    <link rel="stylesheet" href="/layui/css/layui.css">
</head>
<style>
    body{
        text-align: center;
    }
</style>
<body>

<div class="main">
    <table id="student-list"  class="layui-hide" lay-filter="student-list"></table>
</div>

<div class="layui-btn-group demoTable">
    <button class="layui-btn" data-type="addStudent">添加学生</button>
    <button class="layui-btn layui-btn-danger" data-type="batchDelete">批量删除</button>
</div>

<script type="text/html" id="toolBar">
    <a class="layui-btn layui-btn-primary layui-btn-xs" lay-event="detail">查看</a>
    <a class="layui-btn layui-btn-xs" lay-event="edit">编辑</a>
    <a class="layui-btn layui-btn-danger layui-btn-xs" lay-event="del">删除</a>
</script>

<script type="text/javascript">

    layui.use('table', function(){
        var table = layui.table;

        //监听表格复选框选择
        table.on('checkbox(student-list)', function(obj){
            console.log(obj)
        });

        //查看、修改、删除
        table.on('tool(student-list)', function(obj){
            var data = obj.data;
            if(obj.event === 'detail'){
                layer.msg('ID：'+ data.id + ' 的查看操作');
            } else if(obj.event === 'del'){
                layer.confirm('真的要删除' + obj.data.id + " " + obj.data.name + '么', function(index){
                    console.log(obj);
                    obj.del();
                    layer.close(index);
                //    向服务端发送删除指令
                var $ = layui.$;
                $.ajax({
                    url: "students",
                    type: "DELETE",
                    data: "id=" + obj.data.id,
                    success: function (){
                        layer.msg('删除成功');
                    }
                });
                });
            } else if(obj.event === 'edit'){
                layer.alert('编辑行：<br>'+ JSON.stringify(data))
                // 向服务端发送更新指令


                // 同步更新缓存的值
                obj.update({

                });
            }
        });

        var $ = layui.$, active = {
            batchDelete: function(){ //获取选中数据
                var checkStatus = table.checkStatus('student-table')
                    ,data = checkStatus.data;
                // layer.alert(JSON.stringify(data));
                // 已经获得到了data，下一步是执行删除



            }
        };

        $('.demoTable .layui-btn').on('click', function(){
            var type = $(this).data('type');
            active[type] ? active[type].call(this) : '';
        });

        // 表格渲染
        table.render({
            elem: '#student-list' // 挂载点
            ,id: 'student-table' // 表格id
            ,height: 580 // 表格高度
            ,url: '/students' //数据接口
            ,toolbar: '#toolbarDemo' //开启头部工具栏，并为其绑定左侧模板
            ,skin: 'line' //行边框风格
            ,even: true //开启隔行背景
            ,height: 'full-100' // 页面的最大高度 - 100 （自适应）
            ,defaultToolbar: ['filter', 'exports', 'print', { //自定义头部工具栏右侧图标。如无需自定义，去除该参数即可
                title: '提示'
                ,layEvent: 'LAYTABLE_TIPS'
                ,icon: 'layui-icon-tips'
            }]
            ,parseData: function(res){ // 数据源
                //res 即为原始返回的数据
                return {
                    "code": res.code, //解析接口状态
                    "msg": res.msg, //解析提示文本
                    "count": res.extend.count, //解析数据长度
                    "data": res.extend.data.list //解析数据列表
                };
            }
            ,page: { // 分页
                groups: 5 //显示 10 个连续页码
            }
            ,cols: [[ //表头
                {type:'checkbox'}
                ,{field: 'id', title: 'ID', width:80, sort: true}
                ,{field: 'name', title: '姓名', width:80, sort: true}
                ,{field: 'age', title: '年龄', width:80, sort: true}
                ,{field: 'sex', title: '性别', width:80}
                ,{field: 'grade', title: '年级', width: 100, sort: true}
                ,{field: 'birthday', title: '生日', width: 300, sort: true}
                ,{field: 'dept', title: '院系', width: 80, sort: true}
                ,{field: 'telphone', title: '电话', width: 160}
                ,{field: 'qq', title: 'QQ', width: 135}
                ,{fixed: 'right', title:'操作', toolbar: '#toolBar', width:170}
            ]]
        });



    });
</script>

</body>
</html>