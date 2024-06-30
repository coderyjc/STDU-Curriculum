//
// Created by Administrator on 2021/7/1.
//

#include "FileSystem.h"

int main(){
    auto *system = new FileSystem();
    system->login();
    delete system;
    return 0;
}