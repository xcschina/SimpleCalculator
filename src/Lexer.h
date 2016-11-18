#pragma once

#include "Token.h"
#include <cstdio>

class Lexer {
public:
    Lexer();

    /*
    Scan one token from input stream.

    @return the first token of input stream. Notice that it
            is allocated dynamically so remember to free it.
    */
    Token* scan();

    /*
    Run a test program.
    */
    static void test();

private:
    char cur;  // Current character
};
