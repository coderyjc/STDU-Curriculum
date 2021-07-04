//
// Created by Administrator on 2021/6/29.
//

#ifndef CLION_DIRECTORY_H
#define CLION_DIRECTORY_H

#include <vector>
#include "MemoryNode.h"

class Directory : public MemoryNode {

public:

    // 目录节点的下属节点
    vector<MemoryNode> subNode;

public:

    // 创建目录
    void makeDirectory();

    // 删除目录 前提是为空  rmdir
    bool removeDirectory();

    // 列出目录下面的文件
    void list();

    // 当前目录下面的目录的个数
    int numberOfSubDirNode();

    // 当前目录下面的文件个数
    int numberOfFileNode();

};


#endif //CLION_DIRECTORY_H
