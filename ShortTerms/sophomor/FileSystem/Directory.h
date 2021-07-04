#pragma once
#include <vector>
#include "MemoryNode.h"

class Directory : public MemoryNode {

public:


    Directory() {
        // 目录
        this->type = 'd';
    }

    // 目录节点的下属节点
    vector<MemoryNode> subNode;

public:

    // 创建目录
    int makeDirectory(string options, vector<string> params) override;

    int touch(string options, vector<string> params) override;

    // 删除目录 前提是为空 rmdir
    bool removeDirectory();

    // 列出目录下面的文件
    void list(string options, vector<string> params) override;

    // 当前目录下面的目录的个数
    int numberOfSubDirNode();

    // 当前目录下面的文件个数
    int numberOfFileNode();

};
