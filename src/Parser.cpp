#include "Parser.h"
#include <stdexcept>

using std::string;

Parser::Parser() : lookahead(nullptr) {}

Parser::~Parser() {
    reset();
}

const std::list<Token*>& Parser::scan() {
    reset();
    readNext();
    expr();
    return postfixTokens;
}


void Parser::reset() {
    for (Token *token : postfixTokens) {
        delete token;
    }
    postfixTokens.clear();
    lookahead = nullptr;
}

void Parser::expr() {
    A();
    restA();
}

void Parser::A() {
    B();
    restB();
}

void Parser::restA() {
    while (lookahead) {
        if (lookahead->tag == Token::Tag::OPERATOR) {
            auto oper = dynamic_cast<Operator*>(lookahead);
            if (oper->val == '+') {
                readNext();
                A();
                postfixTokens.push_back(new Operator('+'));
                continue;
            } else if (oper->val == '-') {
                readNext();
                A();
                postfixTokens.push_back(new Operator('-'));
                continue;
            }
        }
        break;
    }
}

void Parser::B() {
    if (!lookahead) {
        throw std::runtime_error("Parser.B(): syntax error");
    }
    if (lookahead->tag == Token::Tag::OPERATOR) {
        auto oper = dynamic_cast<Operator*>(lookahead);
        if (oper->val == '+') {
            readNext();
            B();
            postfixTokens.push_back(new Operator('@'));
            return;
        } else if (oper->val == '-') {
            readNext();
            B();
            postfixTokens.push_back(new Operator('#'));
            return;
        }
    }
    factor();
}

void Parser::restB() {
    while (lookahead) {
        if (lookahead->tag == Token::Tag::OPERATOR) {
            auto oper = dynamic_cast<Operator*>(lookahead);
            if (oper->val == '*') {
                readNext();
                B();
                postfixTokens.push_back(new Operator('*'));
                continue;
            } else if (oper->val == '/') {
                readNext();
                B();
                postfixTokens.push_back(new Operator('/'));
                continue;
            }
        }
        break;
    }
}

void Parser::factor() {
    if (!lookahead) {
        throw std::runtime_error("Parser.factor(): syntax error, require 'factor'");
    }
    if (lookahead->tag == Token::Tag::OPERATOR) {
        auto oper = dynamic_cast<Operator*>(lookahead);
        if (oper->val == '(') {
            readNext();
            expr();
            if (!lookahead) {
                throw std::runtime_error("Parser.factor(): syntax error");
            }
            auto oper1 = dynamic_cast<Operator*>(lookahead);
            if (!oper1 || oper1->val != ')') {
                throw std::runtime_error("Parser.factor(): syntax error, require ')'");
            }
            readNext();
        }
    } else if (lookahead->tag == Token::Tag::NUM) {
        auto num = dynamic_cast<Number*>(lookahead);
        postfixTokens.push_back(new Number(num->val));
        readNext();
    }
}

void Parser::readNext() {
    delete lookahead;
    lookahead = lexer.scan();
}

void Parser::test() {
    Parser parser;
    printf("Input an infix expression: ");
    try {
        int cnt = 1;
        auto postfixTokens = parser.scan();
        printf("\nPostfix tokens:\n");
        for (const auto &token : postfixTokens) {
            printf("Token #%d:\n", cnt++);
            switch (token->tag) {
                case Token::Tag::NUM:
                    printf(" Type: NUMBER\n");
                    printf("Value: %d\n\n", (dynamic_cast<Number*>(token))->val);
                    break;
                case Token::Tag::OPERATOR:
                    printf(" Type: OPERATOR\n");
                    printf("Value: %c\n\n", (dynamic_cast<Operator*>(token))->val);
                    break;
                default:
                    break;
            }
        }
    } catch (const std::runtime_error &e) {
        printf("Runtime error: %s\n", e.what());
    }
}
