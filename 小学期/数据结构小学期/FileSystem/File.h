#pragma once

#include "MemoryNode.h"


class File : public MemoryNode {

public:

    File() {
        // 普通文件
        this->type = '-';
        this->authority = "rwxr--r--";
        this->user = "root";
        this->createDate = getCurrentTimeString();
        this->updateDate = getCurrentTimeString();
    }

    File(string name) {
        // 普通文件
        this->type = '-';
        this->authority = "rwxr--r--";
        this->user = "root";
        this->name = name;
        this->createDate = getCurrentTimeString();
        this->updateDate = getCurrentTimeString();
    }
};
