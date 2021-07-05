#pragma warning(disable:4996)

#include <string>
#include <algorithm>
#include <ctime>

#include "FileSystem.h"

// 初始化
void FileSystem::init() {
    // 根路径为 /
    this->currentPath = "/";
    // 开辟新的根指针
    this->root = new Directory();
    // 当前节点双端队列
    this->currentNode.push_back(this->root);
}

string FileSystem::getCurrentTimeString(){
    time_t nowtime;
    nowtime = time(NULL);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&nowtime));
    return tmp;
}

bool FileSystem::login() {
    cout << "请输入用户名: ";
    string userName;
    cin >> userName;
    this->user.userName = userName;
    cin.get();
    cout << "当前时间：" << getCurrentTimeString() << endl;
    this->commendLine();
    return 1;
}

void FileSystem::commendLine() {

    string command;

    while (true) {
        cout << "[" + this->user.userName + "@localhost " + currentPath + "] # ";
        // 读入命令行
        getline(cin, command);
        if ("exit" == command) {
            // 程序退出
            cout << "Bye";
            break;
        }
        if (-1 == execute(command)) {
            cout << "ERROR!" << endl;
        }
    }
}

// 命令解析器
int FileSystem::execute(string command) {

    /**
     * 命令 = 指令 + 选项 + 参数
     * 指令 - 用一个string存储
     * 选项 - 考虑用遍历的方式（因为不多）
     * 参数 - 用vector，因为可能有很多参数
     */
     // 指令
    string instruction;
    // 临时保存选项
    string options;
    // 参数
    vector<string> params;

    int flag = 0; // 有没有发现空格，如果发现了，这是第几个了？
    int lastIdx = 0; // 上一个空格的位置

    // 字符串的清洗应该在这里进行，如果有多余的空格，在这里去掉


    // 扫一遍字符串，获取指令、选项和参数
    for (int i = 0; i < command.length(); i++) {
        if (command[i] == ' ') {
            // 发现空格
            if (!flag) {
                // 第一次发现空格，截取instruction
                instruction = command.substr(0, i);
                flag++;
                lastIdx = ++i;
            }
            else {
                if (command[lastIdx] == '-') {
                    // 说明是选项
                    lastIdx += 1;
                    options += command.substr(lastIdx, i - lastIdx);
                }
                else {
                    params.push_back(command.substr(lastIdx, i - lastIdx));
                }
                lastIdx = ++i;
            }
        }
    }
    // 刷了一边没有发现空格，则指令就是 命令
    if (!flag) {
        instruction = command;
    }
    else {
        // 如果有空格，则必然会留下最后一个空格之后的选项或者参数
        // 这时候要对它进行截取和判断
        if (command[lastIdx] == '-') {
            options += command.substr(++lastIdx, command.length() - lastIdx);
        }
        else {
            params.push_back(command.substr(lastIdx, command.length() - lastIdx));
        }
    }

    // 至此，指令、选项、参数都已经完成提取
    // 对指令进行排序简化
    string newOption = "" + options[0];
    sort(options.begin(), options.end());
    // 指令清洗，相同的字母去掉
    if (options.length() != 1) {
        for (int i = 1; i < options.length(); ++i) {
            if (options[i] != options[i - 1]) {
                newOption += options[i];
            }
        }
    }

    options = newOption;
    // 清洗完成，进入指令分发器
    return commandDispatcher(instruction, options, params);
}


int FileSystem::commandDispatcher(string instruction, string options, vector<string> parameters) {

    if ("ls" == instruction) { // 查看文件列表
        if (this->currentNode.back()->type != 'd') return -1;
        else this->currentNode.back()->list(options, parameters);
    }
    else if ("mkdir" == instruction) {  // 创建目录
        if (parameters.size() != 1) return -1;
        if (parameters[0][0] == '/') return this->root->makeDirectory(options, parameters);
        else return this->currentNode.back()->makeDirectory(options, parameters);
    }
    else if ("cd" == instruction) { // 打开指定目录
        if (parameters.size() != 1) return -1;
        else if (parameters[0] == "." || parameters[0] == "./" || options[0] != '\0') return 0;
        else {
            return this->changeDirectory(options, parameters);
        }
    }
    else if ("touch" == instruction) { // 创建文件
        if (parameters.size() != 1) return -1;
        if (parameters[0][0] == '/') return this->root->touch(options, parameters);
        else return this->currentNode.back()->touch(options, parameters);
    }
    else if ("rmdir" == instruction) { // 删除指定不为空的目录
        if (parameters.size() != 1|| parameters[0] == "/") return -1;
        if (parameters[0][0] == '/') return this->root->removeDirectory(options, parameters);
        else return this->currentNode.back()->removeDirectory(options, parameters);
    }
    else if ("rm" == instruction) { // 删除文件
        if (parameters.size() != 1 || parameters[0] == "/") return -1;
        if (parameters[0][0] == '/') return this->root->remove(options, parameters);
        else return this->currentNode.back()->remove(options, parameters);
    }
    else if ("tree" == instruction) { // 列出指定目录的目录树结构
        if (parameters[0] == "/")
            return this->root->tree(options, parameters, 0);
        else {
            // 先进入指定目录，再列出目录
            return treeSingleTree(options, parameters);
        }
    }
    else if ("find" == instruction) {
        // 在指定目录和这个目录下面查找文件或者目录
        // 第一个参数是模式，第二个是路径
        if (parameters.size() != 2) return -1;
        else return searchSingleDirectory(options, parameters);
    }
    else if ("pwd" == instruction) {
        cout << currentPath << endl;
    }
    else if ("" == instruction) {
        return 1;
    } return 0;
}


int FileSystem::changeDirectory(string options, vector<string> parameters) {

    // 目标路径
    string toBeSplit = parameters[0];

    // 分割后的目录
    vector<string> directories;

    if (toBeSplit == "..") {
        // 当前已经在根目录了
        if (currentPath == "/") return -1;
        else {
            // cd .. : 返回上一层目录
            for (int i = currentPath.length() - 1; i >= 0; i--) {
                if (currentPath[i] == '/' && i != currentPath.length() - 1) {
                    // 当前路径向前截取
                    currentPath = currentPath.substr(0, i + 1);
                    // 当前节点栈出栈
                    currentNode.pop_back();
                    return 1;
                }
            }
        }
    } else directories = this->directoryDealer(toBeSplit);

    // 从根目录开始？
    int startFromRoot = toBeSplit[0] == '/' ? 1 : 0;

    // 获取到了目录的集合，开始进入目录，先保存当前目录
    string rollBack = currentPath;

    // 如果是 / 开头，就先把所有目录出栈，并将curr目录置空, 将root放进去
    if (startFromRoot == 1) {
        currentPath = "/";
        currentNode.clear();
        currentNode.push_back(root);
    }

    MemoryNode* temp = this->currentNode.back();
    // 然后逐个进入
    for (int i = 0; i < directories.size(); i++) {
        // 遇到了上级目录或本级目录
        if (directories[i] == ".") continue;
        if (directories[i] == "..") { // 返回上级目录
            if (currentPath == "/") return -1; 
            else {
                // cd .. : 返回上一层目录
                for (int j = currentPath.length() - 1; j >= 0; j--) {
                    if (currentPath[j] == '/' && j != currentPath.length() - 1) {
                        // 当前路径向前截取
                        currentPath = currentPath.substr(0, j + 1);
                        // 当前节点栈出栈
                        currentNode.pop_back();
                        break;
                    }
                }
            }
            continue;
        }
        temp = temp->find(directories[i], 'd');
        if (temp == nullptr) { // 空指针，也就是没找到，此时应该回滚并返回 -1
            // 清空目录
            currentPath = "/";
            currentNode.clear();
            currentNode.push_back(root);
            if (rollBack == "/") return -1; // 回滚到根目录
            // 重新进入当前目录
            temp = this->root;
            directories = this->directoryDealer(rollBack);
            for (int i = 0; i < directories.size(); i++) {
                currentNode.push_back(temp->find(directories[i], 'd'));
                temp = temp->find(directories[i], 'd');
            }
            return -1; // 返回状态码
        } else {
            currentPath = currentPath + directories[i] + "/";
            currentNode.push_back(temp);
        }
    }
}

vector<string> FileSystem::directoryDealer(string directory){

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

int FileSystem::treeSingleTree(string options, vector<string> parameters) {
    // 待列出的目录
    string path = parameters[0];

    // temp 指向当前所在的节点
    MemoryNode* temp = this->currentNode.back();
    
    // 获取将要列出文件的目录
    vector<string> directories = this->directoryDealer(path);

    // 然后逐个进入
    for (int i = 0; i < directories.size(); i++) {
        temp = temp->find(directories[i], 'd');
        if (temp == nullptr) { // 空指针，也就是没找到，此时应该回滚并返回 -1
            return -1; // 返回状态码
        }
    }
    temp->tree(options, parameters, 0);
    return 1;
}

int FileSystem::searchSingleDirectory(string options, vector<string> parameters){
    // 待列出的目录
    string path = parameters[1];

    // temp 指向当前所在的节点
    MemoryNode* temp = this->currentNode.back();

    // 获取将要进入的目录
    vector<string> directories = this->directoryDealer(path);

    // 然后逐个进入
    for (int i = 0; i < directories.size(); i++) {
        temp = temp->find(directories[i], 'd');
        if (temp == nullptr) { // 空指针，也就是没找到
            return -1; // 返回状态码
        }
    }
    temp->findAll(options, parameters);
    return 1;
}
