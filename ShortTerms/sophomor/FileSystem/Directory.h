#pragma once
#include <vector>
#include "MemoryNode.h"

class Directory : public MemoryNode {

public:

    Directory() {
        // 目录
        this->type = 'd';
        authority = "rwxr--r--";
        user = "root";
        this->createDate = getCurrentTimeString();
        this->updateDate = getCurrentTimeString();
    }

    Directory(string name) {
        this->type = 'd';
        authority = "rwxr--r--";
        user = "root";
        this->name = name;
        this->createDate = getCurrentTimeString();
        this->updateDate = getCurrentTimeString();
    }

public:

    // 创建目录
    int makeDirectory(string options, vector<string> params) override;

    // 创建文件
    int touch(string options, vector<string> params) override;

    // 列出目录下面的文件
    void list(string options, vector<string> params) override;

    // 树形列出目录下面的所有文件
    int tree(string options, vector<string> params, int directoryLevel) override;

    // 删除目录
    int removeDirectory(string options, vector<string> params) override;

    // 目录下是否有指定名称和类型的文件
    MemoryNode* find(string name, char type) override;

    // 删除目录或者文件
    int remove(string options, vector<string> params) override;

    // 在指定目录下面全局寻找文件
    int findAll(string options, vector<string> params) override;

    // 目录解析器
    vector<string> directoryDealer(string directory);
};
