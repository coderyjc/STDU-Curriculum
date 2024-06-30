#include<algorithm>

#include "File.h"
#include "Directory.h"


void Directory::list(string options, vector<string> params) {
    if ("a" == options || options[0] == '\0' || options == "") {
        for (auto node : subNode) {
            cout << node->name << '\t';
        }
    }
    else if ("l" == options || "al" == options) {
        for (auto node : subNode) {
            cout << node->type << node->authority << '\t'
                << node->user << '\t'
                << node->updateDate << '\t'
                << node->createDate << '\t'
                << node->name << endl;
        }
    }
    cout << endl;
}

int Directory::tree(string options, vector<string> params, int directoryLevel){
    // �������Ŀ¼��
    for (int i = 0; i < directoryLevel; i++) cout << "��";
    cout << this->name << endl;
    for (int i = 0; i < this->subNode.size(); i++) {
        if(this->subNode[i]->type == 'd') 
            this->subNode[i]->tree(options, params, directoryLevel + 1);
    }
    return 0;
}


int Directory::removeDirectory(string options, vector<string> params) {
    // ·���ָ�
    string path = params[0];
    vector<string> directories = directoryDealer(path);

    // �Ƿ�Ӹ��ڵ㿪ʼ�Ѿ��ڿ�ʼ��ʱ��������
    // ����ֱ�ӽ��� Ȼ��ɾ��
    int directoryIdx = 0;

    MemoryNode* temp = this;

    // �Ƚ���Ҫɾ���Ľڵ�ĸ��ڵ�
    for (directoryIdx = 0; directoryIdx < directories.size() - 1; directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            return -1; // �Ҳ�������ڵ�ĸ��ڵ㣬�˳�ѭ��
        else if (temp->find(directories[directoryIdx], 'd')) {
            // �ҵ�������ڵ�,�����Ǹ�Ŀ¼������֮������Ǹ��ļ�Ҳ�˳�
            temp = temp->find(directories[directoryIdx], 'd');
        }
    }
    
    MemoryNode* parent = temp;
    temp = temp->find(directories[directoryIdx], 'd');
    if (temp != nullptr && temp->subNode.size() == 0) { //���ҵ���ɾ��
        for (vector<MemoryNode*>::iterator iter = parent->subNode.begin(); iter != parent->subNode.end(); iter++) {
            if ((*iter)->name == directories[directoryIdx]) {
                parent->subNode.erase(iter);
                parent->updateDate = getCurrentTimeString();
                return 1;
            }
        }
    }
    return -1;
}

// �ҵ�����ָ������ָ�룬�Ҳ����ͷ��ؿ�ָ��
MemoryNode* Directory::find(string name, char type){
    for (int i = 0; i < subNode.size(); i++) {
        if (subNode[i]->name == name && subNode[i]->type == type) {
            return subNode[i];
        }
    }
    return nullptr;
}

int Directory::remove(string options, vector<string> params){
    // Ĭ�����Ƴ��ļ������˲���֮������Ƴ�Ŀ¼

    // ·���ָ�
    string path = params[0];
    vector<string> directories = directoryDealer(path);

    // �Ƿ�Ӹ��ڵ㿪ʼ�Ѿ��ڿ�ʼ��ʱ��������
    // ����ֱ�ӽ��� Ȼ��ɾ��
    int directoryIdx = 0;

    MemoryNode* temp = this;

    // �Ƚ���Ҫɾ���Ľڵ�ĸ��ڵ�
    for (directoryIdx = 0; directoryIdx < directories.size() - 1; directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            return -1; // �Ҳ�������ڵ�ĸ��ڵ㣬�˳�ѭ��
        else if (temp->find(directories[directoryIdx], 'd')) {
            // �ҵ�������ڵ�,�����Ǹ�Ŀ¼������֮������Ǹ��ļ�Ҳ�˳�
            temp = temp->find(directories[directoryIdx], 'd');
        }
    }

    MemoryNode* parent = temp;
    temp = temp->find(directories[directoryIdx], '-');
    if (temp != nullptr && temp->subNode.size() == 0) { //���ҵ���ɾ��
        for (vector<MemoryNode*>::iterator iter = parent->subNode.begin(); iter != parent->subNode.end(); iter++) {
            if ((*iter)->name == directories[directoryIdx]) {
                parent->subNode.erase(iter);
                parent->updateDate = getCurrentTimeString();
                return 1;
            }
        }
    }
    return -1;
}


int Directory::makeDirectory(string options, vector<string> params) {

    // ·���ָ�
    string path = params[0];
    vector<string> directories = directoryDealer(path);
   
    // �Ƿ�Ӹ��ڵ㿪ʼ�Ѿ��ڿ�ʼ��ʱ��������
    // ����ֱ�ӽ��� + ����
    int directoryIdx = 0;

    MemoryNode* temp = this;
    
    // �Ƚ����Ѵ��ڵĽڵ�
    for (directoryIdx = 0; directoryIdx < directories.size(); directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            break; // �Ҳ�������ڵ㣬�˳�ѭ��
        else if (temp->find(directories[directoryIdx], 'd')) {
            // �ҵ�������ڵ�,�����Ǹ�Ŀ¼������֮������Ǹ��ļ�Ҳ�˳�
            temp = temp->find(directories[directoryIdx], 'd');
        }
        else break;
    }
    
    // ��ʼ�����ڵ�
    Directory* newTemp;
    while (directoryIdx < directories.size()) {
        // �����ֽ���
        newTemp = new Directory(directories[directoryIdx++]);
        temp->subNode.push_back(newTemp);
        temp = newTemp;
    }
    return 1;
}

// �����ļ�
int Directory::touch(string options, vector<string> params) {

    // ·���ָ�
    string path = params[0];
    vector<string> directories = directoryDealer(path);

    // �Ƿ�Ӹ��ڵ㿪ʼ�Ѿ��ڿ�ʼ��ʱ��������
    // ����ֱ�ӽ��� + ����
    int directoryIdx = 0;

    MemoryNode* temp = this;

    // �Ƚ����Ѵ��ڵĽڵ�
    for (directoryIdx = 0; directoryIdx < directories.size() - 1; directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            break; // �Ҳ�������ڵ㣬�˳�ѭ��
        else if (temp->find(directories[directoryIdx], 'd')) {
            // �ҵ�������ڵ�,�����Ǹ�Ŀ¼������֮������Ǹ��ļ�Ҳ�˳�
            temp = temp->find(directories[directoryIdx], 'd');
        }
    }
    // ��ʼ�����ļ�
    File* newTemp;
    if (temp->find(directories[directoryIdx], '-')) {
        return -1; // �ļ��Ѵ���
    }
    else {
        temp->subNode.push_back(new File(directories[directoryIdx]));
        temp->updateDate = getCurrentTimeString();
    }
    return 1;
}

vector<string> Directory::directoryDealer(string directory) {

    // ��Ҫ�ָ��Ŀ¼
    string toBeSplit = directory;

    // �ָ���Ŀ¼
    vector<string> directories;

    // ��Ŀ¼�Ƿ�Ӹ���ʼ
    int startFromRoot = 0;

    // �Ӹ�Ŀ¼��ʼ
    if (toBeSplit[0] == '/') startFromRoot = 1;
    // ��ȡĿ¼���Ʒ�
    int lastInx = startFromRoot;
    // ��Ŀ¼������ָ�Ŀ¼
    for (int i = startFromRoot; i < toBeSplit.length(); i++) {
        if (toBeSplit[i] == '/') {
            directories.push_back(toBeSplit.substr(lastInx, i - lastInx));
            lastInx = i + 1;
        }
    }
    if (lastInx <= toBeSplit.length() - 1) {
        // Ŀ¼��β���� ��/��
        directories.push_back(toBeSplit.substr(lastInx, toBeSplit.length() - lastInx));
    }
    return directories;
}

int Directory::findAll(string options, vector<string> params){
    if (this->find(params[0], '-') || this->find(params[0], 'd')) {
        // ����·���� ����ģʽ
        cout << params[1] << params[0] << endl;
    }
    for (int i = 0; i < this->subNode.size(); i++) {
        //���²���·���� ���������µ�·���������
        if (this->subNode[i]->type == 'd') {
            // ����·��
            if (params[1][params[1].length() - 1] == '/') {
                params[1] = params[1]+ this->subNode[i]->name + "/";
            } else params[1] = params[1] + "/" + this->subNode[i]->name + "/";
            // ��������
            this->subNode[i]->findAll(options, params);
        }
    }
    return 0;
}
