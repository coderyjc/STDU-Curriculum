#include "FileSystem.h"

int main() {
    auto* system = new FileSystem();
    system->login();
    delete system;
    return 0;
}