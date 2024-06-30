#pragma once
#include<unordered_map>
#include<string>

#include "TokenType.h"


class Keywords
{
public:
    unordered_map<string, _TokenType> keywords;
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
