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
    delete lookahead;
    lookahead = nullptr;
}

void Parser::syntaxErr() const {
    throw std::runtime_error("syntax error");
}

void Parser::expr() {
    switch (lookahead->tag) {
        case Token::END_INPUT:
            syntaxErr();
            break;
        case Token::OPERATOR: {
            auto oper = dynamic_cast<Operator*>(lookahead);
            if (oper->val == '*' || oper->val == '/' || oper->val == ')') {
                syntaxErr();
            }
            break;
        }
        default:
            break;
    }
    A();
    restA();
}

void Parser::A() {
    switch (lookahead->tag) {
        case Token::END_INPUT:
            syntaxErr();
            break;
        case Token::OPERATOR: {
            auto oper = dynamic_cast<Operator*>(lookahead);
            if (oper->val == '*' || oper->val == '/' || oper->val == ')') {
                syntaxErr();
            }
            break;
        }
        default:
            break;
    }
    B();
    restB();
}

void Parser::restA() {
    switch (lookahead->tag) {
        case Token::NUM:
            syntaxErr();
            break;
        case Token::OPERATOR: {
            auto oper = dynamic_cast<Operator*>(lookahead);
            switch (oper->val) {
                case '+':
                    readNext();
                    A();
                    postfixTokens.push_back(new Operator('+'));
                    restA();
                    break;
                case '-':
                    readNext();
                    A();
                    postfixTokens.push_back(new Operator('-'));
                    restA();
                    break;
                case '*':
                case '/':
                case '(':
                    syntaxErr();
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}

void Parser::B() {
    switch (lookahead->tag) {
        case Token::END_INPUT:
            syntaxErr();
            break;
        case Token::NUM:
            factor();
            break;
        case Token::OPERATOR: {
            auto oper = dynamic_cast<Operator*>(lookahead);
            switch (oper->val) {
                case '+':
                    readNext();
                    B();
                    postfixTokens.push_back(new Operator('@'));
                    break;
                case '-':
                    readNext();
                    B();
                    postfixTokens.push_back(new Operator('#'));
                    break;
                case '(':
                    factor();
                    break;
                default:
                    syntaxErr();
                    break;
            }
            break;
        }
        default:
            break;
    }
}

void Parser::restB() {
    switch (lookahead->tag) {
        case Token::NUM:
            syntaxErr();
            break;
        case Token::OPERATOR: {
            auto oper = dynamic_cast<Operator*>(lookahead);
            switch (oper->val) {
                case '*':
                    readNext();
                    B();
                    postfixTokens.push_back(new Operator('*'));
                    restB();
                    break;
                case '/':
                    readNext();
                    B();
                    postfixTokens.push_back(new Operator('/'));
                    restB();
                    break;
                case '(':
                    syntaxErr();
                    break;
                default:
                    break;
            }
            break;
        }
        default:
            break;
    }
}

void Parser::factor() {
    switch (lookahead->tag) {
        case Token::END_INPUT:
            syntaxErr();
            break;
        case Token::NUM: {
            auto num = dynamic_cast<Number*>(lookahead);
            postfixTokens.push_back(new Number(num->val));
            readNext();
            break;
        }
        case Token::OPERATOR: {
            auto oper = dynamic_cast<Operator*>(lookahead);
            if (oper->val == '(') {
                readNext();
                expr();
                auto oper1 = dynamic_cast<Operator*>(lookahead);
                if (!oper1 || oper1->val != ')') {
                    syntaxErr();
                }
                readNext();
            } else {
                syntaxErr();
            }
            break;
        }
        default:
            break;
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
        auto postfixTokens = parser.scan();
        printf("Postfix tokens: ");
        for (const auto &token : postfixTokens) {
            switch (token->tag) {
                case Token::NUM:
                    printf("%d ", (dynamic_cast<Number*>(token))->val);
                    break;
                case Token::OPERATOR:
                    printf("%c ", (dynamic_cast<Operator*>(token))->val);
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    } catch (const std::runtime_error &e) {
        printf("Runtime error: %s\n", e.what());
    }
}
