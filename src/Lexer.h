#pragma once

#include "Token.h"
#include <cstdio>

/*
Lexical analyser to get tokens from input stream.
*/
class Lexer {
public:
    Lexer();

    /*
    Scan one token from input stream.

    @return the first token of input stream. Notice that it
            is allocated dynamically so remember to free it.
            Return nullptr if it meets the new line character.
    */
    Token* scan();

    /*
    Test the function of the class.
    */
    static void test();

private:
    char cur;  // Current character
};
