#pragma once
#include <iostream>
#include <deque>
#include <vector>

#include "MemoryNode.h"
#include "File.h"
#include "Directory.h"
#include "User.h"

using namespace std;

class FileSystem {

public:

    FileSystem() {
        init();
    }

public:

    // 根节点指针
    MemoryNode* root;

    // 用户
    User user;

    // 当前路径列表
    deque<MemoryNode*> currentNode;

    // 当前路径 pwd
    string currentPath;

public:

    // 初始化，做一些初始的处理
    void init();

    // 登录
    bool login();

    // 执行命令
    int execute(string command);

    // 指令分发器
    int commandDispatcher(string instruction, string options, vector<string> parameters);

    // 进入命令行界面
    void commendLine();

    // 改变当前目录
    int changeDirectory(string options, vector<string> parameters);

};
