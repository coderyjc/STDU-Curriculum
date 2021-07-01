//
// Created by Administrator on 2021/7/1.
//

#ifndef CLION_FILESYSTEM_H
#define CLION_FILESYSTEM_H

#include <iostream>
#include <deque>
#include <vector>

#include "MemoryNode.h"
#include "User.h"

using namespace std;

class FileSystem {

public:

    FileSystem(){
        init();
    }


public:

    // 根节点指针
    MemoryNode root;

    // 用户
    User user;

    // 当前路径列表
    deque<MemoryNode> currentNode;

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
    void commandDispatcher(string instruction, string options, vector<string> parameters);

    // 进入命令行界面
    void commendLine();

};


#endif //CLION_FILESYSTEM_H
