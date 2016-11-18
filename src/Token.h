#pragma once

#include "Base.h"
#include <string>

class Token {
public:
    enum Tag {
        NUM,
        OPERATOR
    };

    const Tag tag;

    Token(const Tag tag_);
    virtual ~Token();
};

class Number : public Token {
public:
    const int val;
    Number(const int val_);
    virtual ~Number();
};

class Operator : public Token {
public:
    const char val;
    Operator(const char &val_);
    virtual ~Operator();
};
