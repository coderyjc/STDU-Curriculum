//
// Created by Administrator on 2021/7/1.
//

#include <string>


#include "FileSystem.h"

// 初始化
void FileSystem::init() {
    // 初始化用户名和密码
    this->user = User("root", "333", 0);
    // 根路径为 /
    this->currentPath = "/";
    // 开辟新的根指针
    this->root = MemoryNode();
    // 当前节点双端队列
    this->currentNode.push_back(this->root);
}

bool FileSystem::login() {
    this->commendLine();
    cout << "请输入用户名: ";
    string userName;
    cin >> userName;
    cout << "请输入密码: ";
    string userPwd;
    cin >> userPwd;
    cin.get();
    if("root" == userName && "333" == userPwd)
        this->commendLine();
    else{
        cout << "用户名或密码错误，登录失败" << endl;
        cout << "程序退出" << endl;
        return false;
    }
}

void FileSystem::commendLine() {

    string command;

    while (true){
        cout << "[" + this->user.userName + "@localhost " + currentPath + "] # ";
        // 读入命令行
        getline(cin, command);
        if("exit" == command){
            // 程序退出
            cout << "Bye";
            break;
        }

        if(-1 == execute(command)){
            cout << "ERROR!";
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
    for(int i = 0; i < command.length(); i++){
        if(command[i] == ' '){
            // 发现空格
            if(!flag){
                // 第一次发现空格，截取instruction
                instruction = command.substr(0, i);
                flag++;
                lastIdx = ++i;
            } else {
                if(command[lastIdx] == '-'){
                    // 说明是选项
                    lastIdx += 1;
                    options += command.substr(lastIdx, i - lastIdx);
                } else {
                    params.push_back(command.substr(lastIdx, i - lastIdx));
                }
                lastIdx = ++i;
            }
        }
    }
    // 刷了一边没有发现空格，则指令就是 命令
    if(!flag){
        instruction = command;
    }
    else {
        // 如果有空格，则必然会留下最后一个空格之后的选项或者参数
        // 这时候要对它进行截取和判断
        if (command[lastIdx] == '-'){
            options += command.substr(++lastIdx, command.length() - lastIdx);
        } else {
            params.push_back(command.substr(lastIdx, command.length() - lastIdx));
        }
    }

    // 至此，指令、选项、参数都已经完成提取



    return 0;
}

void FileSystem::commandDispatcher(string instruction, string options, vector<string> parameters) {



}

