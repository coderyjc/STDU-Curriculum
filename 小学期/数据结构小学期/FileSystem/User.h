#pragma once
class User {
public:

    User() {
        userName = "root";
        passwd = "333";
        role = 0;
    }

public:
    // �û���
    string userName;

    // ����
    string passwd;

    // Ȩ��
    int role;

};
