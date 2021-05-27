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
    <link rel="stylesheet" href="/css/index.css">
</head>
<style>
    body{
        text-align: center;
    }
</style>
<body>

<%--表格的主体--%>
<div class="main">
    <table id="student-list"  class="layui-hide" lay-filter="student-list"></table>
</div>

<%--表格上的按钮--%>
<div class="layui-btn-group demoTable">
    <button class="layui-btn" data-type="addStudent">添加学生</button>
    <button class="layui-btn layui-btn-danger" data-type="batchDelete">批量删除</button>
</div>

<!-- 添加、编辑、查看的模态框 -->
<%-- 共用一个模态框 --%>
<div id="myModal" class="modal">
    <div class="modal-content">
        <fieldset class="layui-elem-field layui-field-title" style="margin-top: 20px;">
            <legend>标题</legend>
        </fieldset>
        <form class="layui-form" action="" lay-filter="information" method="post">
            <div class="layui-form-item">
                <label class="layui-form-label">id</label>
                <div class="layui-input-block">
                    <input type="text" name="id" autocomplete="off"
                           placeholder="不可编辑" class="layui-input" disabled="disabled">
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">姓名</label>
                <div class="layui-input-block">
                    <input type="text" name="name" autocomplete="off"
                           placeholder="请输入姓名" class="layui-input" required>
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">年级</label>
                <div class="layui-input-block">
                    <select name="grade" lay-filter="grade" required>
                        <option value="0"></option>
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
                    <select id="dept-list" name="dept" lay-filter="dept" required>
<%--                        这个东西通过ajax 请求动态拉取过来--%>
                        <option value=""></option>
<%--                        <option value="4">旅行</option>--%>
                    </select>
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">单选框</label>
                <div class="layui-input-block">
                    <input type="radio" name="sex" value="1" title="男" checked>
                    <input type="radio" name="sex" value="1" title="女">
                </div>
            </div>

            <div class="layui-form-item" style="float: left">
                <div class="layui-inline">
                    <label class="layui-form-label">出生日期</label>
                    <div class="layui-input-block">
                        <input type="text" class="layui-input" id="birthday"
                               placeholder="yyyy-MM-dd" style="width: 350px" required>
                    </div>
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">QQ号</label>
                <div class="layui-input-block">
                    <input type="text" name="qq" autocomplete="off"
                           placeholder="qq号" class="layui-input">
                </div>
            </div>

            <div class="layui-form-item">
                <label class="layui-form-label">手机号</label>
                <div class="layui-input-block">
                    <input type="text" name="telphone" lay-verify="phone" autocomplete="off"
                           placeholder="手机号" class="layui-input">
                </div>
            </div>

            <div class="layui-form-item">
                <div class="layui-input-block">
                    <button type="submit" class="layui-btn" lay-submit lay-filter="submit">提交
                    </button>
                    <button type="reset" class="layui-btn" >重置</button>
                    <button type="button" id="return-to-index" class="layui-btn layui-btn-primary">返回</button>
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

<script type="text/javascript">

    var $ = layui.$;
    // 关闭注册模态框
    $("#return-to-index").click(function(){
        $("#myModal").css("display", "none");
    });

    // 填充模态框中的院系
    $.ajax({
        url:"depts",
        type: "GET",
        success: function (result) {
        //    填充院系
            var depts = result.extend.list;
            $.each(depts, function (index, item) {
                $("<option></option>")
                    .attr("value", item.deptid).text(item.deptname)
                .appendTo("#dept-list");
            });

        }
    })



    // 渲染日期组件
    layui.use('laydate', function(){
        var laydate = layui.laydate;
        //执行一个laydate实例
        laydate.render({
            elem: '#birthday' //指定元素
        });
    });

    layui.use('table', function(){
        var table = layui.table;

        // 监听表格复选框选择
        table.on('checkbox(student-list)', function(obj){
            console.log(obj)
        });

        //查看、修改、删除
        table.on('tool(student-list)', function(obj){
            var data = obj.data;
            if(obj.event === 'detail'){
                // 查看
                $("#myModal legend").text("查看");
                $("#myModal").css("display", "block");




            } else if(obj.event === 'del'){
                layer.confirm('真的要删除' + obj.data.id + " " + obj.data.name + '么', function(index){
                    // console.log(obj);
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
                //修改
                $("#myModal legend").text("修改");
                $("#myModal").css("display", "block");
                //给表单赋值
                form = layui.form;
                form.val("information", {
                    "id": data.id
                    ,"name": data.name
                    , "age": data.age
                    , "dept": data.dept
                    , "grade": data.grade
                    ,"sex": data.sex
                    ,"birthday": data.birthday
                    ,"qq": data.qq
                    , "telphone": data.telphone
                });
                // 向服务端发送更新指令

                // 同步更新缓存的值
                obj.update({

                });
            }
        });

        // 数据的批量删除
        var $ = layui.$, active = {
            batchDelete: function(){ //获取选中数据
                var checkStatus = table.checkStatus('student-table')
                    ,data = checkStatus.data;
                if (data.length === 0){
                    layer.msg("当前没有选中数据");
                    return;
                }
                layer.confirm('真的要删除选中的行么', function() {
                    // 已经获得到了data，点击了确认，下一步是执行删除
                    var $ = layui.$;
                    // console.log(data);
                    $.each(data, function (index, item) {
                        $.ajax({
                            url: "students",
                            type: "DELETE",
                            data: "id=" + item.id,
                            success: function () {
                                // 删除完毕之后暂时不执行任何操作
                            }
                        })
                    })
                    layer.msg("删除成功");
                    table.reload('student-table', {
                        url: 'students'
                    });
                })
            }
            ,addStudent:function () {
                // 添加学生
                //修改
                $("#myModal legend").text("添加学生");
                $("#myModal").css("display", "block");


            }
        };

        $('.demoTable .layui-btn').on('click', function(){
            var type = $(this).data('type');
            active[type] ? active[type].call(this) : '';
        });

        // 表格初始化渲染
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


    /**
     * 将时间戳转化为标准时间
     * @param date 时间戳
     * @returns {string} 标准时间字符串
     */
    function dateFormat(date) {
        var s = new Date(date)
        var y = s.getFullYear()
        var m = (s.getMonth() + 1) < 10 ? '0' + (s.getMonth() + 1) : (s.getMonth() + 1)
        var dd = s.getDate() < 10 ? '0' + s.getDate() : s.getDate()
        var enddate = y + '-' + m + '-' + dd
        return enddate
    }

</script>

</body>
</html>