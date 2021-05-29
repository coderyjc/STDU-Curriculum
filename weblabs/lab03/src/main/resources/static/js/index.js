
var $ = layui.$;

$(function () {
    // 关闭注册模态框
    $("#return-to-index").click(function(){
        $("#myModal").css("display", "none");
        // 清空模态框
        toggleModal(0);
    });
    // 渲染日期组件
    layui.use('laydate', function(){
        var laydate = layui.laydate;
        //执行一个laydate实例
        laydate.render({
            elem: '#modal-student-birthday' //指定元素
        });
    });
    layui.form.render('select');

})

layui.use('table', function(){
    var table = layui.table;

    // 监听表格复选框选择
    table.on('checkbox(student-list)', function(obj){
        console.log(obj)
    });

    //查看、修改、删除
    //这一部分是点击查看、修改、删除之后要进行的操作
    //而不是点击模态框上的按钮之后进行的操作
    //关于表单的提交会在下面用 form.on 来写
    table.on('tool(student-list)', function(obj){
        var data = obj.data;
        if(obj.event === 'detail'){
            // 查看
            $("#myModal legend").text("查看");
            // 筛选按钮
            $("#update-btn").css("display", "none");
            $("#insert-btn").css("display", "none");
            // 展示
            $("#myModal").css("display", "block");
            form = layui.form;
            // 填充信息
            form.val("information", {
                "id": data.id
                ,"name": data.name
                , "age": data.age
                , "dept": get_dept_id_by_name(data.dept)
                , "grade": data.grade
                ,"sex": data.sex === "男" ? 1 : 0
                ,"qq": data.qq
                , "telphone": data.telphone
            });
            layui.laydate.render({
                elem: '#modal-student-birthday'
                ,value: dateFormat(data.birthday)
                ,isInitValue: true //是否允许填充初始值，默认为 true
            });
            // 锁住信息
            toggleModal(1);
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
            // 筛选按钮
            $("#update-btn").css("display", "inline");
            $("#insert-btn").css("display", "none");
            $("#myModal").css("display", "block");
            toggleModal(2);
            $("#modal-student-id").attr("disabled", "disabled");
            //给表单赋值
            form = layui.form;
            form.val(`information`, {
                "id": data.id
                ,"name": data.name
                , "age": data.age
                , "dept": get_dept_id_by_name(data.dept)
                , "grade": data.grade
                ,"sex": data.sex === "男" ? 1 : 0
                ,"qq": data.qq
                , "telphone": data.telphone
            });
            layui.laydate.render({
                elem: '#modal-student-birthday'
                ,value: dateFormat(data.birthday)
                ,isInitValue: true //是否允许填充初始值，默认为 true
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
            toggleModal(0);
            toggleModal(2);
            // 获取最大id
            $.ajax({
                url: "maxid",
                type:"GET",
                success: function (result){
                    // 当前id为最大 id + 1
                    var id = result.extend.id + 1;
                    // id 填充
                    $("#modal-student-id").val(id).attr("disabled", "disabled");
                }
            });
            $("#myModal legend").text("添加学生");
            // 筛选按钮
            $("#update-btn").css("display", "none");
            $("#insert-btn").css("display", "inline");
            $("#myModal").css("display", "block");
            // 发送ajax请求添加学生
            // 这部分的代码写在下面了
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
        ,height: 'full-200' // 页面的最大高度 - 100 （自适应）
        ,defaultToolbar: ['filter', 'exports', 'print', { //自定义头部工具栏右侧图标。如无需自定义，去除该参数即可
            title: '提示'
            ,layEvent: 'LAYTABLE_TIPS'
            ,icon: 'layui-icon-tips'
        }]
        ,parseData: function(res){ // 数据源
            var list = res.extend.data.list;
            //进行数据清洗
            $.each(list, function (index, item) {
                item.birthday = dateFormat(item.birthday);
                item.dept = get_dept_name_by_id(item.dept);
                item.sex = item.sex === 1 ? "男" : "女";
            })
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
            ,{field: 'birthday', title: '生日', width: 150}
            ,{field: 'dept', title: '院系', width: 180}
            ,{field: 'telphone', title: '电话', width: 160}
            ,{field: 'qq', title: 'QQ', width: 135}
            ,{fixed: 'right', title:'操作', toolbar: '#toolBar', width:170}
        ]]
    });
});


var form = layui.form;
// 提交修改
form.on('submit(update)', function(data){
    // 获取数据
    var post = data.field;
    post.birthday = $("#modal-student-birthday").val();
    post.age = 2021 - Number(post.birthday.substr(0, 4));
    // 发送请求
    // console.log(post) //当前容器的全部表单字段，名值对形式：{name: value}
    $.ajax({
        url: "students",
        type: "POST",
        data: post,
        success: function () {
            // 关闭模态框
            $("#myModal").css("display", "none");
            // 清空模态框信息
            toggleModal(0);
            // 提示用户修改成功
            layer.msg("修改成功");
        }
    });
    // 重载表格
    layui.table.reload('student-table', {
        url: 'students'
    });
    return false;
});

// 提交插入数据
form.on('submit(insert)', function(data){
    // 获取数据
    var post = data.field;
    post.birthday = $("#modal-student-birthday").val();
    post.age = 2021 - Number(post.birthday.substr(0, 4));
    console.log(post) //当前容器的全部表单字段，名值对形式：{name: value}
    $.ajax({
        url: "students",
        type: "PUT",
        data: post,
        success: function () {
            // 关闭模态框
            $("#myModal").css("display", "none");
            // 清空模态框信息
            toggleModal(0);
            // 提示用户修改成功
            layer.msg("插入成功");
        }
    })
    // 重载表格
    layui.table.reload('student-table', {
        url: 'students'
    });
    return false;
});

form.verify({
    // qq
    qq: function(value, item){ //value：表单的值、item：表单的DOM对象
        if(value.length < 5 || value.length > 12){
            return '请输入正确的qq号格式';
        }
    }
    //学院
    ,dept: function (value, item) {
        if (value){

        }
    }
    // 性别
    ,sex: function (value, item){
        if (value === -1){
            return false;
        }
    }


});

/**
 * 约定
 * 0 - 清空
 * 1 - 置为 disable
 * 2 - 置为 可用
 */
function toggleModal(nextStatus) {
    // 转换模态框的状态
    if (0 === nextStatus){
        // 清空模态框
        $("#myModal input").val("");
        $(".default-selected").attr("selected", "selected");
    } else if (1 === nextStatus) {
        // 置为disable
        $("#myModal input").attr("disabled", "disabled");
    } else if (2 === nextStatus){
        // 置为可用的
        $("#myModal input").removeAttr("disabled");
    }

}


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

function get_dept_name_by_id(id) {

    var deptList = [
        '土木工程学院',
        '机械工程学院',
        '经济学院',
        '文法学院',
        '交通运输学院',
        '建筑与艺术学院',
        '电气与电子工程学院',
        '信息科学与技术学院',
        '工程力学系',
        '数理系',
        '外语系',
        '管理学院',
        '医学院'
    ]
    return deptList[id];
}

function get_dept_id_by_name(name) {
    var deptList = [
        '土木工程学院',
        '机械工程学院',
        '经济学院',
        '文法学院',
        '交通运输学院',
        '建筑与艺术学院',
        '电气与电子工程学院',
        '信息科学与技术学院',
        '工程力学系',
        '数理系',
        '外语系',
        '管理学院',
        '医学院'
    ]
    return deptList.indexOf(name);
}