#pragma once
#include <vector>
#include "MemoryNode.h"

class Directory : public MemoryNode {

public:

    Directory() {
        // Ŀ¼
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

    // ����Ŀ¼
    int makeDirectory(string options, vector<string> params) override;

    // �����ļ�
    int touch(string options, vector<string> params) override;

    // �г�Ŀ¼������ļ�
    void list(string options, vector<string> params) override;

    // �����г�Ŀ¼����������ļ�
    int tree(string options, vector<string> params, int directoryLevel) override;

    // ɾ��Ŀ¼
    int removeDirectory(string options, vector<string> params) override;

    // Ŀ¼���Ƿ���ָ�����ƺ����͵��ļ�
    MemoryNode* find(string name, char type) override;

    // ɾ��Ŀ¼�����ļ�
    int remove(string options, vector<string> params) override;

    // ��ָ��Ŀ¼����ȫ��Ѱ���ļ�
    int findAll(string options, vector<string> params) override;

    // Ŀ¼������
    vector<string> directoryDealer(string directory);
};
