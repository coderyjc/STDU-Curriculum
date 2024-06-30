#pragma warning(disable:4996)

#include <string>
#include <algorithm>
#include <ctime>

#include "FileSystem.h"

// ��ʼ��
void FileSystem::init() {
    // ��·��Ϊ /
    this->currentPath = "/";
    // �����µĸ�ָ��
    this->root = new Directory();
    // ��ǰ�ڵ�˫�˶���
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
    cout << "�������û���: ";
    string userName;
    cin >> userName;
    this->user.userName = userName;
    cin.get();
    cout << "��ǰʱ�䣺" << getCurrentTimeString() << endl;
    this->commendLine();
    return 1;
}

void FileSystem::commendLine() {

    string command;

    while (true) {
        cout << "[" + this->user.userName + "@localhost " + currentPath + "] # ";
        // ����������
        getline(cin, command);
        if ("exit" == command) {
            // �����˳�
            cout << "Bye";
            break;
        }
        if (-1 == execute(command)) {
            cout << "ERROR!" << endl;
        }
    }
}

// ���������
int FileSystem::execute(string command) {

    /**
     * ���� = ָ�� + ѡ�� + ����
     * ָ�� - ��һ��string�洢
     * ѡ�� - �����ñ����ķ�ʽ����Ϊ���ࣩ
     * ���� - ��vector����Ϊ�����кܶ����
     */
     // ָ��
    string instruction;
    // ��ʱ����ѡ��
    string options;
    // ����
    vector<string> params;

    int flag = 0; // ��û�з��ֿո���������ˣ����ǵڼ����ˣ�
    int lastIdx = 0; // ��һ���ո��λ��

    // �ַ�������ϴӦ����������У�����ж���Ŀո�������ȥ��


    // ɨһ���ַ�������ȡָ�ѡ��Ͳ���
    for (int i = 0; i < command.length(); i++) {
        if (command[i] == ' ') {
            // ���ֿո�
            if (!flag) {
                // ��һ�η��ֿո񣬽�ȡinstruction
                instruction = command.substr(0, i);
                flag++;
                lastIdx = ++i;
            }
            else {
                if (command[lastIdx] == '-') {
                    // ˵����ѡ��
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
    // ˢ��һ��û�з��ֿո���ָ����� ����
    if (!flag) {
        instruction = command;
    }
    else {
        // ����пո����Ȼ���������һ���ո�֮���ѡ����߲���
        // ��ʱ��Ҫ�������н�ȡ���ж�
        if (command[lastIdx] == '-') {
            options += command.substr(++lastIdx, command.length() - lastIdx);
        }
        else {
            params.push_back(command.substr(lastIdx, command.length() - lastIdx));
        }
    }

    // ��ϴ��ɣ�����ָ��ַ���
    return commandDispatcher(instruction, options, params);
}


int FileSystem::commandDispatcher(string instruction, string options, vector<string> parameters) {

    if ("ls" == instruction) { // �鿴�ļ��б�
        if (this->currentNode.back()->type != 'd') return -1;
        else this->currentNode.back()->list(options, parameters);
    }
    else if ("mkdir" == instruction) {  // ����Ŀ¼
        if (parameters.size() != 1) return -1;
        if (parameters[0][0] == '/') return this->root->makeDirectory(options, parameters);
        else return this->currentNode.back()->makeDirectory(options, parameters);
    }
    else if ("cd" == instruction) { // ��ָ��Ŀ¼
        if (parameters.size() != 1) return -1;
        else if (parameters[0] == "." || parameters[0] == "./" || options[0] != '\0') return 0;
        else {
            return this->changeDirectory(options, parameters);
        }
    }
    else if ("touch" == instruction) { // �����ļ�
        if (parameters.size() != 1) return -1;
        if (parameters[0][0] == '/') return this->root->touch(options, parameters);
        else return this->currentNode.back()->touch(options, parameters);
    }
    else if ("rmdir" == instruction) { // ɾ��ָ����Ϊ�յ�Ŀ¼
        if (parameters.size() != 1|| parameters[0] == "/") return -1;
        if (parameters[0][0] == '/') return this->root->removeDirectory(options, parameters);
        else return this->currentNode.back()->removeDirectory(options, parameters);
    }
    else if ("rm" == instruction) { // ɾ���ļ�
        if (parameters.size() != 1 || parameters[0] == "/") return -1;
        if (parameters[0][0] == '/') return this->root->remove(options, parameters);
        else return this->currentNode.back()->remove(options, parameters);
    }
    else if ("tree" == instruction) { // �г�ָ��Ŀ¼��Ŀ¼���ṹ
        if (parameters[0] == "/")
            return this->root->tree(options, parameters, 0);
        else {
            // �Ƚ���ָ��Ŀ¼�����г�Ŀ¼
            return treeSingleTree(options, parameters);
        }
    }
    else if ("find" == instruction) {
        // ��ָ��Ŀ¼�����Ŀ¼��������ļ�����Ŀ¼
        // ��һ��������ģʽ���ڶ�����·��
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

    // Ŀ��·��
    string toBeSplit = parameters[0];

    // �ָ���Ŀ¼
    vector<string> directories;

    if (toBeSplit == "..") {
        // ��ǰ�Ѿ��ڸ�Ŀ¼��
        if (currentPath == "/") return -1;
        else {
            // cd .. : ������һ��Ŀ¼
            for (int i = currentPath.length() - 1; i >= 0; i--) {
                if (currentPath[i] == '/' && i != currentPath.length() - 1) {
                    // ��ǰ·����ǰ��ȡ
                    currentPath = currentPath.substr(0, i + 1);
                    // ��ǰ�ڵ�ջ��ջ
                    currentNode.pop_back();
                    return 1;
                }
            }
        }
    } else directories = this->directoryDealer(toBeSplit);

    // �Ӹ�Ŀ¼��ʼ��
    int startFromRoot = toBeSplit[0] == '/' ? 1 : 0;

    // ��ȡ����Ŀ¼�ļ��ϣ���ʼ����Ŀ¼���ȱ��浱ǰĿ¼
    string rollBack = currentPath;

    // ����� / ��ͷ�����Ȱ�����Ŀ¼��ջ������currĿ¼�ÿ�, ��root�Ž�ȥ
    if (startFromRoot == 1) {
        currentPath = "/";
        currentNode.clear();
        currentNode.push_back(root);
    }

    MemoryNode* temp = this->currentNode.back();
    // Ȼ���������
    for (int i = 0; i < directories.size(); i++) {
        // �������ϼ�Ŀ¼�򱾼�Ŀ¼
        if (directories[i] == ".") continue;
        if (directories[i] == "..") { // �����ϼ�Ŀ¼
            if (currentPath == "/") return -1; 
            else {
                // cd .. : ������һ��Ŀ¼
                for (int j = currentPath.length() - 1; j >= 0; j--) {
                    if (currentPath[j] == '/' && j != currentPath.length() - 1) {
                        // ��ǰ·����ǰ��ȡ
                        currentPath = currentPath.substr(0, j + 1);
                        // ��ǰ�ڵ�ջ��ջ
                        currentNode.pop_back();
                        break;
                    }
                }
            }
            continue;
        }
        temp = temp->find(directories[i], 'd');
        if (temp == nullptr) { // ��ָ�룬Ҳ����û�ҵ�����ʱӦ�ûع������� -1
            // ���Ŀ¼
            currentPath = "/";
            currentNode.clear();
            currentNode.push_back(root);
            if (rollBack == "/") return -1; // �ع�����Ŀ¼
            // ���½��뵱ǰĿ¼
            temp = this->root;
            directories = this->directoryDealer(rollBack);
            for (int i = 0; i < directories.size(); i++) {
                currentNode.push_back(temp->find(directories[i], 'd'));
                temp = temp->find(directories[i], 'd');
            }
            return -1; // ����״̬��
        } else {
            currentPath = currentPath + directories[i] + "/";
            currentNode.push_back(temp);
        }
    }
}

vector<string> FileSystem::directoryDealer(string directory){

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

int FileSystem::treeSingleTree(string options, vector<string> parameters) {
    // ���г���Ŀ¼
    string path = parameters[0];

    // temp ָ��ǰ���ڵĽڵ�
    MemoryNode* temp = this->currentNode.back();
    
    // ��ȡ��Ҫ�г��ļ���Ŀ¼
    vector<string> directories = this->directoryDealer(path);

    // Ȼ���������
    for (int i = 0; i < directories.size(); i++) {
        temp = temp->find(directories[i], 'd');
        if (temp == nullptr) { // ��ָ�룬Ҳ����û�ҵ�����ʱӦ�ûع������� -1
            return -1; // ����״̬��
        }
    }
    temp->tree(options, parameters, 0);
    return 1;
}

int FileSystem::searchSingleDirectory(string options, vector<string> parameters){
    // ���г���Ŀ¼
    string path = parameters[1];

    // temp ָ��ǰ���ڵĽڵ�
    MemoryNode* temp = this->currentNode.back();

    // ��ȡ��Ҫ�����Ŀ¼
    vector<string> directories = this->directoryDealer(path);

    // Ȼ���������
    for (int i = 0; i < directories.size(); i++) {
        temp = temp->find(directories[i], 'd');
        if (temp == nullptr) { // ��ָ�룬Ҳ����û�ҵ�
            return -1; // ����״̬��
        }
    }
    temp->findAll(options, parameters);
    return 1;
}
