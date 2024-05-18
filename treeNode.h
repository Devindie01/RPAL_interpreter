#pragma once

#include "lexer.h"
#include <stack>

class treeNode
{

public:
    enum Type
    {
        LAMBDA,
        WHERE,
        TAU,
        AUG,
        TERNARY,
        OR,
        AND_LOGICAL,
        NOT,
        GR,
        GE,
        LS,
        LE,
        EQ,
        NE,
        ADD,
        SUBTRACT,
        NEG,
        MULTIPLY,
        DIVIDE,
        EXPONENTIAL,
        AT,
        GAMMA,
        TRUE,
        FALSE,
        NIL,
        DUMMY,
        WITHIN,
        AND,
        REC,
        BINDING,
        FCN_FORM,
        PARANTHESES,
        COMMA,
        LET,
        IDENTIFIER,
        STRING,
        INTEGER,
        YSTAR
    };

    std::string nodeString;
    treeNode *childNode = NULL;
    treeNode *siblingNode = NULL;
    std::vector<treeNode *> children;
    int type;
};