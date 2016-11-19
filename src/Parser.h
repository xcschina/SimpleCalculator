#pragma once

#include "Lexer.h"
#include <sstream>

/*
Syntax parser to convert an infix expression to a postfix expression.
*/
class Parser {
public:
    Parser();

    /*
    Convert an infix expression from the input stream to its postfix expression.

    @return the postfix expression
    @throw runtime_error if conversion fails
    */
    std::string scan();

    /*
    Test the function of the class.
    */
    static void test();

private:
    Lexer lexer;
    Token* lookahead;
    std::ostringstream stream;

    /*
    Derivation function according to SDT.
    */
    void expr();
    void A();
    void restA();
    void B();
    void restB();
    void factor();

    /*
    Read next token and store it in lookahead field.
    */
    void readNext();
};

