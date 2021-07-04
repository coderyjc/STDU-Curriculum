#pragma once

#include "MemoryNode.h"


#include "MemoryNode.h"


class File : public MemoryNode {

public:

    File() {
        // 普通文件
        this->type = '-';
    }


public:

    // 输出文件内容
    void content();

};



