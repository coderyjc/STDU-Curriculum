#include "Directory.h"

void Directory::list(string options, vector<string> params) {
    if ("a" == options || "" == options) {
        for (auto node : subNode) {
            cout << node.name << '\t';
        }
    }
    else if ("l" == options || "al" == options) {
        for (auto node : subNode) {
            cout << node.type << node.authority << '\t'
                << node.name << '\t'
                << node.user << '\t'
                << node.updateDate << '\t'
                << node.createDate << '\t'
                << node.name << endl;
        }
    }
}

int Directory::makeDirectory(string options, vector<string> params) {

    string path = params[0];
    vector<string> dirNames;
    // Â·¾¶·Ö¸î
    /**
     * ./
     * /usr/dir1/dir2
     * usr/dir1/dir2
     * usr
     */
    for (int i = 0; i < path.length(); ++i) {


    }


}

int Directory::touch(string options, vector<string> params) {



}
