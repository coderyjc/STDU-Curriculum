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

    // ���ڵ�ָ��
    MemoryNode* root;

    // �û�
    User user;

    // ��ǰ·���б�
    deque<MemoryNode*> currentNode;

    // ��ǰ·�� pwd
    string currentPath;

public:

    // ��ʼ������һЩ��ʼ�Ĵ���
    void init();

    // ��ȡ��ǰʱ��
    string getCurrentTimeString();

    // ��¼
    bool login();

    // ִ������
    int execute(string command);

    // ָ��ַ���
    int commandDispatcher(string instruction, string options, vector<string> parameters);

    // ���������н���
    void commendLine();

    // �ı䵱ǰĿ¼
    int changeDirectory(string options, vector<string> parameters);

    // �г�Ŀ¼��
    int treeSingleTree(string options, vector<string> parameters);

    // ȫ�ֲ���
    int searchSingleDirectory(string options, vector<string> parameters);

    // Ŀ¼������
    vector<string> directoryDealer(string directory);
};
