#pragma once

#include "MemoryNode.h"


class File : public MemoryNode {

public:

    File() {
        // ��ͨ�ļ�
        this->type = '-';
        this->authority = "rwxr--r--";
        this->user = "root";
        this->createDate = getCurrentTimeString();
        this->updateDate = getCurrentTimeString();
    }

    File(string name) {
        // ��ͨ�ļ�
        this->type = '-';
        this->authority = "rwxr--r--";
        this->user = "root";
        this->name = name;
        this->createDate = getCurrentTimeString();
        this->updateDate = getCurrentTimeString();
    }
};
