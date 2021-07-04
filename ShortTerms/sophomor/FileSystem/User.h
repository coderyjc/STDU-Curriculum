#pragma once
class User {
public:

    User() {}

    User(string userName, string passwd, int role) : userName(std::move(userName)), passwd(std::move(passwd)), role(role) {}

public:
    // 用户名
    string userName;

    // 密码
    string passwd;

    // 权限
    int role;

};
