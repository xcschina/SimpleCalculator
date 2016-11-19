#pragma once

#include "Lexer.h"
#include <sstream>
#include <list>

/*
Syntax parser to convert an infix expression to a postfix expression.
*/
class Parser {
public:
    Parser();
    ~Parser();

    /*
    Convert an infix expression from the input stream to its postfix expression.

    @return the token list of the postfix expression
    @throw runtime_error if conversion fails
    */
    const std::list<Token*>& scan();

    /*
    Clean memory resources.
    */
    void reset();

    /*
    Test the function of the class.
    */
    static void test();

private:
    Lexer lexer;
    Token* lookahead;
    std::list<Token*> postfixTokens;

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

