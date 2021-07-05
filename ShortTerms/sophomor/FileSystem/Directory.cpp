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
    // 先序遍历目录树
    for (int i = 0; i < directoryLevel; i++) cout << "—";
    cout << this->name << endl;
    for (int i = 0; i < this->subNode.size(); i++) {
        if(this->subNode[i]->type == 'd') 
            this->subNode[i]->tree(options, params, directoryLevel + 1);
    }
    return 0;
}


int Directory::removeDirectory(string options, vector<string> params) {
    // 路径分割
    string path = params[0];
    vector<string> directories = directoryDealer(path);

    // 是否从根节点开始已经在开始的时候分配好了
    // 这里直接进入 然后删除
    int directoryIdx = 0;

    MemoryNode* temp = this;

    // 先进入要删除的节点的父节点
    for (directoryIdx = 0; directoryIdx < directories.size() - 1; directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            return -1; // 找不到这个节点的父节点，退出循环
        else if (temp->find(directories[directoryIdx], 'd')) {
            // 找到了这个节点,并且是个目录，进入之，如果是个文件也退出
            temp = temp->find(directories[directoryIdx], 'd');
        }
    }
    
    MemoryNode* parent = temp;
    temp = temp->find(directories[directoryIdx], 'd');
    if (temp != nullptr && temp->subNode.size() == 0) { //能找到就删除
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

// 找到返回指向它的指针，找不到就返回空指针
MemoryNode* Directory::find(string name, char type){
    for (int i = 0; i < subNode.size(); i++) {
        if (subNode[i]->name == name && subNode[i]->type == type) {
            return subNode[i];
        }
    }
    return nullptr;
}

int Directory::remove(string options, vector<string> params){
    // 默认是移除文件，加了参数之后可以移除目录

    // 路径分割
    string path = params[0];
    vector<string> directories = directoryDealer(path);

    // 是否从根节点开始已经在开始的时候分配好了
    // 这里直接进入 然后删除
    int directoryIdx = 0;

    MemoryNode* temp = this;

    // 先进入要删除的节点的父节点
    for (directoryIdx = 0; directoryIdx < directories.size() - 1; directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            return -1; // 找不到这个节点的父节点，退出循环
        else if (temp->find(directories[directoryIdx], 'd')) {
            // 找到了这个节点,并且是个目录，进入之，如果是个文件也退出
            temp = temp->find(directories[directoryIdx], 'd');
        }
    }

    MemoryNode* parent = temp;
    temp = temp->find(directories[directoryIdx], '-');
    if (temp != nullptr && temp->subNode.size() == 0) { //能找到就删除
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

    // 路径分割
    string path = params[0];
    vector<string> directories = directoryDealer(path);
   
    // 是否从根节点开始已经在开始的时候分配好了
    // 这里直接进入 + 建立
    int directoryIdx = 0;

    MemoryNode* temp = this;
    
    // 先进入已存在的节点
    for (directoryIdx = 0; directoryIdx < directories.size(); directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            break; // 找不到这个节点，退出循环
        else if (temp->find(directories[directoryIdx], 'd')) {
            // 找到了这个节点,并且是个目录，进入之，如果是个文件也退出
            temp = temp->find(directories[directoryIdx], 'd');
        }
        else break;
    }
    // 开始建立节点
    Directory* newTemp;
    while (directoryIdx < directories.size()) {
        // 用名字建立
        newTemp = new Directory(directories[directoryIdx++]);
        temp->subNode.push_back(newTemp);
        temp = newTemp;
    }
    return 1;
}

// 创建文件
int Directory::touch(string options, vector<string> params) {

    // 路径分割
    string path = params[0];
    vector<string> directories = directoryDealer(path);

    // 是否从根节点开始已经在开始的时候分配好了
    // 这里直接进入 + 建立
    int directoryIdx = 0;

    MemoryNode* temp = this;

    // 先进入已存在的节点
    for (directoryIdx = 0; directoryIdx < directories.size() - 1; directoryIdx++) {
        if (!temp->find(directories[directoryIdx], 'd'))
            break; // 找不到这个节点，退出循环
        else if (temp->find(directories[directoryIdx], 'd')) {
            // 找到了这个节点,并且是个目录，进入之，如果是个文件也退出
            temp = temp->find(directories[directoryIdx], 'd');
        }
    }
    // 开始建立文件
    File* newTemp;
    if (temp->find(directories[directoryIdx], '-')) {
        return -1; // 文件已存在
    }
    else {
        temp->subNode.push_back(new File(directories[directoryIdx]));
        temp->updateDate = getCurrentTimeString();
    }
    return 1;
}

vector<string> Directory::directoryDealer(string directory) {

    // 将要分割的目录
    string toBeSplit = directory;

    // 分割后的目录
    vector<string> directories;

    // 长目录是否从根开始
    int startFromRoot = 0;

    // 从根目录开始
    if (toBeSplit[0] == '/') startFromRoot = 1;
    // 截取目录控制符
    int lastInx = startFromRoot;
    // 长目录情况，分割目录
    for (int i = startFromRoot; i < toBeSplit.length(); i++) {
        if (toBeSplit[i] == '/') {
            directories.push_back(toBeSplit.substr(lastInx, i - lastInx));
            lastInx = i + 1;
        }
    }
    if (lastInx <= toBeSplit.length() - 1) {
        // 目录结尾不是 ’/‘
        directories.push_back(toBeSplit.substr(lastInx, toBeSplit.length() - lastInx));
    }
    return directories;
}

int Directory::findAll(string options, vector<string> params){
    if (this->find(params[0], '-') || this->find(params[0], 'd')) {
        // 查找路径， 查找模式
        cout << params[1] << params[0] << endl;
    }
    for (int i = 0; i < this->subNode.size(); i++) {
        //更新查找路径， 并继续在新的路径下面查找
        if (this->subNode[i]->type == 'd') {
            // 更新路径
            if (params[1][params[1].length() - 1] == '/') {
                params[1] = params[1]+ this->subNode[i]->name + "/";
            } else params[1] = params[1] + "/" + this->subNode[i]->name + "/";
            // 继续查找
            this->subNode[i]->findAll(options, params);
        }
    }
    return 0;
}
