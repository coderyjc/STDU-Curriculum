#pragma once
#ifndef KEYWORDS_H_INCLUDED
#define KEYWORDS_H_INCLUDED
#include<hash_map>
#include<string>

#include "TokenType.h"

using namespace __gnu_cxx;


class Keywords
{
public:
    struct str_hash
    {
        size_t operator()(const string& str) const
        {
            return __stl_hash_string(str.c_str());
        }
    };
    hash_map<string, _TokenType, str_hash> keywords;
    Keywords()
    {
        keywords["int"] = _INT;
        keywords["char"] = _CHAR;
        keywords["void"] = _VOID;
        keywords["extern"] = _EXTERN;
        keywords["if"] = _IF;
        keywords["else"] = _ELSE;
        keywords["switch"] = _SWITCH;
        keywords["case"] = _CASE;
        keywords["default"] = _DEFAULT;
        keywords["while"] = _WHILE;
        keywords["do"] = _DO;
        keywords["for"] = _FOR;
        keywords["break"] = _BREAK;
        keywords["continue"] = _CONTINUE;
        keywords["return"] = _RETURN;
        keywords["double"] = _DOUBLE;
        keywords["float"] = _FLOAT;
        keywords["typedef"] = _TYPEDEF;
        keywords["enum"] = _ENUM;
        keywords["register"] = _REGISTER;
        keywords["signed"] = _SIGNED;
        keywords["const"] = _CONST;
        keywords["read"] = _READ;
        keywords["printf"] = _PRINTF;
        keywords["write"] = _WRITE;
    }
    _TokenType getTag(string name)
    {
        return keywords.find(name) != keywords.end() ? keywords[name] : ID;
    }
};

#endif // KEYWORDS_H_INCLUDED
