#pragma once
#pragma warning(disable:4996)

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
    MemoryNode* parent;

    // 节点的下属节点
    vector<MemoryNode*> subNode;

public:


    // 获取当前时间
    string getCurrentTimeString() {
        time_t nowtime;
        nowtime = time(NULL);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&nowtime));
        return tmp;
    };



    // 列出目录下面的所有文件和目录
    virtual void list(string options, vector<string> params) {}

    // 创建目录
    virtual int makeDirectory(string options, vector<string> params) { return 0; }

    // 创建文件
    virtual int touch(string options, vector<string> params) { return 0; }

    // 在指定目录的下面查找指定类型和名称的文件或目录
    virtual MemoryNode* find(string name, char type) { return nullptr; }

    // 移除非空目录
    virtual int removeDirectory(string options, vector<string> params) { return 0; }

    // 移除文件
    virtual int remove(string options, vector<string> params) { return 0; }

    // 按照树形结构列出文件
    virtual int tree(string options, vector<string> params, int directoryLevel) { return 0; }

    // 递归查找文件的位置
    virtual int recursiveFind(string options, vector<string> params) { return 0; }
    
    // 在指定目录下面全局搜索文件
    virtual int findAll(string options, vector<string> params) { return 0; }
};
