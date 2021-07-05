#pragma once
class User {
public:

    User() {
        userName = "root";
        passwd = "333";
        role = 0;
    }

public:
    // 用户名
    string userName;

    // 密码
    string passwd;

    // 权限
    int role;

};
