#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


#include "global.h"

using namespace std;

int main(int args, char** argv) {


    if (args == 1)
    {
        cerr << "no input files compilation terminated" << endl;
        exit(0);
    }
    else if (args == 2)
    {
        if (strcmp(argv[1], "-exit") == 0) exit(0);
        else  if (strcmp(argv[1], "-help") == 0) {
            printf("this is help");
        }
        else
        {
            cerr << "Unavailable instructions" << endl; exit(0);
        }
    }
    else if (args == 3)
    {
        if (strcmp(argv[1], "-lex") == 0)
        {
            // filename = (char*)malloc(100);
            // strcpy(filename, argv[2]);
            filename = (char*)"demo.c";
            fopen_s(&source, "demo.c", "r+");
            /*if (source != NULL)
            {
                cerr << "args:2 - No such file or dictionary!" << endl;
                exit(0);
            }*/
            lex = new Lex(filename);
            lex->analysis();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s) ===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            lex->LexShow();
        }

        else {
            cerr << "Unavailable instructions" << endl; exit(0);
        }
    }
    else if (args == 5 && ((strcmp(argv[3], "-o") == 0) || (strcmp(argv[3], ">") == 0)))
    {
        if (strcmp(argv[1], "-lex") == 0)
        {
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            source = fopen(filename, "r+");
            if (source != NULL)
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            lexFile = (char*)malloc(100);
            strcpy(lexFile, argv[4]);
            lex = new Lex(filename);
            lex->analysis();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s)===" << endl; exit(0); }
            cout << "\t===Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            lex->LexShow(true);
        }

        else {
            cerr << "Unavailable instructions" << endl; exit(0);
        }
    }
    else {
        cerr << "Wrong instruction format!" << endl;
    }
	return 0;
}