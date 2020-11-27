## 图书馆管理系统

### 目录结构

|文件夹| 作用|
|----|---|
|Components| UI界面的组件，里面的子文件夹存放各种的自定义控件|
|Domain | 实体类，即POJO|
|imgs | UI中的背景图片|
|jar| 项目所使用的jar包 |
|UI| 程序使用的UI界面，都是Frame|
|Utils| 工具类，主要有数据库工具类和其他工具类|

### 数据库表的设计

#### **t_book** 

存储所有的书籍

```sql
drop table if exists t_book;

/*==============================================================*/
/* Table: t_book                                                */
/*==============================================================*/
create table t_book
(
   isbn                 varchar(20) not null,
   name                 varchar(50),
   author               varchar(50),
   price                decimal(10.2),
   instock              int(1),
   primary key (isbn)
);
```


| 字段 | 名称 | 类型 | 说明 |
| ---- | ---- | ---- | ---|
|isbn| 书籍ISBN号 | varchar(20) | 主键、非空 |
|name|书名|varchar(50)||
|author|书籍作者|varchar(50)||
|price|书籍价格|decimal(10.2)||
|instock|是否在库|int(1)||


#### t_user 用户表 

存储所有用户，包括管理员

```sql
drop table if exists t_user;

/*==============================================================*/
/* Table: t_user                                                */
/*==============================================================*/
create table t_user
(
   id                   varchar(20),
   name                 varchar(40),
   type                 int(2),
   sex                  int(1),
   tel                  varchar(11),
   password             varchar(255)
);
```


| 字段 | 名称 | 类型 | 说明 |
| ---- | ---- | ---- | ---|
| id | 用户账号 | varchar(20) | |
| name | 用户名| varchar(40) | |
| type | 用户类型 | int(2) ||
| sex | 用户性别 | int(1) ||
| tel | 用户电话 | varchar(11) ||
| password | 用户的登录密码 | varchar(255) ||


#### t_borrowing 借出的书籍表

存储已经处于借出状态的书籍，借书人和时间

```sql
drop table if exists t_borrowing;

/*==============================================================*/
/* Table: t_borrowing                                           */
/*==============================================================*/
create table t_borrowing
(
   id                   varchar(20),
   isbn                 varchar(20),
   datetime             timestamp
);
```


| 字段 | 名称 | 类型 | 说明 |
| ---- | ---- | ---- | ---|
| id | 用户的账号 | varchar(20)| |
| isbn | 图书的ISBN |  varchar(20)| |
| datetime | 操作的日期 | timestamp | |

#### t_user_log 用户操作日志表

```sql
drop table if exists t_user_log;

/*==============================================================*/
/* Table: t_user_log                                            */
/*==============================================================*/
create table t_user_log
(
   id                   varchar(20),
   isbn                 varchar(20),
   datetime             timestamp
);
```


| 字段 | 名称 | 类型 | 说明 |
| ---- | ---- | ---- | ---|
| id | 用户的账号 | varchar(20)| |
| isbn | 图书的ISBN |  varchar(20)| |
| datetime | 操作的日期 | timestamp | |

