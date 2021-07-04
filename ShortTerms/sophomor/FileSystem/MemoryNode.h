#pragma once
#include <iostream>
#include <vector>

using namespace std;

class MemoryNode {

public:

    MemoryNode() {
        authority = "rwxr--r--";
        user = "root";

    }

public:
    // 节点类型：d表示目录、-表示文件
    char type;

    // 权限 rwx 模式
    string authority;

    // 文件属主, 用户名
    string user;

    // 创建日期
    string createDate;

    // 上一次修改日期
    string updateDate;

    // 节点名称（目录名或者文件名）
    string name;

    // 上一级节点
    MemoryNode* parent{};



public:

    virtual void list(string options, vector<string> params) {}
    virtual int makeDirectory(string options, vector<string> params) {}
    virtual int touch(string options, vector<string> params) {}

};
