#include "Parser.h"
#include <stdexcept>

using std::string;

Parser::Parser() : lookahead(nullptr) {}

string Parser::scan() {
    readNext();
    expr();
    return stream.str();
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
                stream << "+ ";
                continue;
            } else if (oper->val == '-') {
                readNext();
                A();
                stream << "- ";
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
            stream << "@ ";
            return;
        } else if (oper->val == '-') {
            readNext();
            B();
            stream << "# ";
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
                stream << "* ";
                continue;
            } else if (oper->val == '/') {
                readNext();
                B();
                stream << "/ ";
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
        stream << num->val << " ";
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
        printf("Postfix expression: %s\n", parser.scan().c_str());
    } catch (const std::runtime_error &e) {
        printf("runtime_error: %s\n", e.what());
    }
}
