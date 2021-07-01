//
// Created by Administrator on 2021/6/29.
//

#ifndef CLION_MEMORYNODE_H
#define CLION_MEMORYNODE_H

#include <iostream>

using namespace std;

class MemoryNode {

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

};


#endif //CLION_MEMORYNODE_H
