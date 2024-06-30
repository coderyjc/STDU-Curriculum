#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <vector>

using namespace std;

class MemoryNode {

public:

    MemoryNode() {
        authority = "rwxr--r--";
        user = "root";
    }

public:
    // �ڵ����ͣ�d��ʾĿ¼��-��ʾ�ļ�
    char type;

    // Ȩ�� rwx ģʽ
    string authority;

    // �ļ�����, �û���
    string user;

    // ��������
    string createDate;

    // ��һ���޸�����
    string updateDate;

    // �ڵ����ƣ�Ŀ¼�������ļ�����
    string name;

    // ��һ���ڵ�
    MemoryNode* parent;

    // �ڵ�������ڵ�
    vector<MemoryNode*> subNode;

public:


    // ��ȡ��ǰʱ��
    string getCurrentTimeString() {
        time_t nowtime;
        nowtime = time(NULL);
        char tmp[64];
        strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&nowtime));
        return tmp;
    };



    // �г�Ŀ¼����������ļ���Ŀ¼
    virtual void list(string options, vector<string> params) {}

    // ����Ŀ¼
    virtual int makeDirectory(string options, vector<string> params) { return 0; }

    // �����ļ�
    virtual int touch(string options, vector<string> params) { return 0; }

    // ��ָ��Ŀ¼���������ָ�����ͺ����Ƶ��ļ���Ŀ¼
    virtual MemoryNode* find(string name, char type) { return nullptr; }

    // �Ƴ��ǿ�Ŀ¼
    virtual int removeDirectory(string options, vector<string> params) { return 0; }

    // �Ƴ��ļ�
    virtual int remove(string options, vector<string> params) { return 0; }

    // �������νṹ�г��ļ�
    virtual int tree(string options, vector<string> params, int directoryLevel) { return 0; }

    // �ݹ�����ļ���λ��
    virtual int recursiveFind(string options, vector<string> params) { return 0; }
    
    // ��ָ��Ŀ¼����ȫ�������ļ�
    virtual int findAll(string options, vector<string> params) { return 0; }
};
