#include <iostream>
#include<string.h>
#include<iomanip>
#include<stdio.h>
#include<windows.h>
#include<fstream>

#include"global.h"
#include"Parser.h"

using namespace std;

int main(int args, char** argv)
{
    if (args == 1)
    {
        cerr << "no input files compilation terminated" << endl;
        exit(0);
    }
    else if (args == 2)
    {
		if (strcmp(argv[1], "-exit") == 0) exit(0);
		else  if (strcmp(argv[1], "-help") == 0) {

			highlight("-lex ", KEYWORDS); highlight("sourceFile.c", PARAMETER); highlight("\n\t standard output the result of lexical analysis", EXPLANATION); cout << endl;
			highlight("-lex ", KEYWORDS); highlight("sourceFile.c", PARAMETER); highlight(" -o ", KEYWORDS); highlight("lexfile.txt", PARAMETER);
			highlight("\n\t output the result of lexical analysis to lexFile.txt", EXPLANATION); cout << endl;

			highlight("-parse ", KEYWORDS); highlight("sourceFile.c", PARAMETER); highlight("\n\t standard output the Parsing processing", EXPLANATION); cout << endl;
			highlight("-parse ", KEYWORDS); highlight("sourceFile.c", PARAMETER); highlight(" -o ", KEYWORDS); highlight("parsefile.txt", PARAMETER);
			highlight("\n\t output the Paring processing to parsefile.txt", EXPLANATION); cout << endl;


			highlight("-intercode ", KEYWORDS); highlight("sourceFile.c", PARAMETER); highlight("\n\t standard output the intermediate code", EXPLANATION); cout << endl;
			highlight("-intercode ", KEYWORDS); highlight("sourceFile.c", PARAMETER); highlight(" -o ", KEYWORDS); highlight("intercode.txt", PARAMETER);
			highlight("\n\t output the intermediate code to intercode.txt", EXPLANATION); cout << endl;

			highlight("-S ", KEYWORDS); highlight("sourceFile.c", PARAMETER); highlight(" -o ", KEYWORDS); highlight("assembleFile.asm[DEFAULT]", PARAMETER);
			highlight("\n\t output the generated assembly language file to assembleFile.asm DEFAULT  means a given name by system", EXPLANATION); cout << endl;
			highlight("-exit ", KEYWORDS); highlight("\n\t to exit the processing", EXPLANATION); cout << endl;
			highlight("-help ", KEYWORDS); highlight("\n\t introduction to the instruction set", EXPLANATION);
			highlight("", NORMAL);
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
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            if (!(source = fopen(filename, "r+")))
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            lex = new Lex(filename);
            lex->analysis();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s) ===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            lex->LexShow();
        }
        else if (strcmp(argv[1], "-parse") == 0)
        {
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            if (!(source = fopen(filename, "r+")))
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            Parser* parser = new Parser(filename);
            parser->analyze();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s)===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            parser->DrawTree();
        }
        else if (strcmp(argv[1], "-intercode") == 0)
        {
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            if (!(source = fopen(filename, "r+")))
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            Parser* parser = new Parser(filename);
            parser->analyze();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s)===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            symtab->ShowIR();
        }
        else if (strcmp(argv[1], "-S") == 0)
        {
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            if (!(source = fopen(filename, "r+")))
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            Parser* parser = new Parser(filename);
            parser->analyze();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s)===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            file = fopen("temp.s", "w+");
            if ((file = freopen("CON", "w", file)) == NULL) { cerr << "File redirect failed" << endl; exit(0); }
            symtab->genAsm();
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
            if (!(source = fopen(filename, "r+")))
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
        else if (strcmp(argv[1], "-parse") == 0)
        {
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            if (!(source = fopen(filename, "r+")))
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            Parser* parser = new Parser(filename);
            parser->analyze();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s)===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            parseFile = (char*)malloc(100);
            strcpy(parseFile, argv[4]);
            parser->DrawTree(true);
        }
        else if (strcmp(argv[1], "-intercode") == 0)
        {
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            if (!(source = fopen(filename, "r+")))
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            Parser* parser = new Parser(filename);
            parser->analyze();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s)===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            intercodeFile = (char*)malloc(100);
            strcpy(intercodeFile, argv[4]);
            symtab->ShowIR(true);
        }
        else if (strcmp(argv[1], "-S") == 0)
        {
            filename = (char*)malloc(100);
            strcpy(filename, argv[2]);
            if (!(source = fopen(filename, "r+")))
            {
                cerr << "No such file or dictionary!" << endl;
                exit(0);
            }
            Parser* parser = new Parser(filename);
            parser->analyze();
            if (errorNum > 0) { cout << "\t=== Build finished: " << errorNum << " error(s), " << warnNum << " warning(s)===" << endl; exit(0); }
            cout << "\t=== Build finished: 0 error(s), " << warnNum << " warning(s) ===" << endl;
            if (strcmp(argv[4], "DEFAULT") == 0) { targetFile = strcat(lex->getFileName(false), ".s"); }
            else {
                targetFile = (char*)malloc(100);
                strcpy(targetFile, argv[4]);
            }
            if ((file = fopen(targetFile, "w")) == NULL) { cout << "cannot create the file" << endl; exit(0); }
            symtab->genAsm();
        }
        else {
            cerr << "Unavailable instructions" << endl; exit(0);
        }
    }
    else {
        cerr << "Wrong instruction format!" << endl;
    }
}
