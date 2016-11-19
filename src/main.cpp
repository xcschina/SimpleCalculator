#include "Parser.h"
#include <stack>

using namespace std;

// Run the calculator program
void calculator();

// Return the result of a postfix expression
int computePostfix(const list<Token*> &postfixTokens);

int main() {
    {
        // Test lexical analyzer
        //Lexer::test();

        // Test syntactic analyzer
        //Parser::test();

        // Run calculator
        calculator();
    }
    checkMemoryLeaks();
    return 0;
}

void calculator() {
    Parser parser;
    printf("Input an infix expression: ");
    try {
        auto postfixTokens = parser.scan();
        printf("Answer: %d\n", computePostfix(postfixTokens));
    } catch (const std::runtime_error &e) {
        printf("Runtime error: %s\n", e.what());
    }
}

int computePostfix(const list<Token*> &postfixTokens) {
    list<Token*> alloc;
    stack<const Token*> s;
    for (const auto &token : postfixTokens) {
        if (token->tag == Token::Tag::NUM) {
            s.push(token);
        } else if (token->tag == Token::Tag::OPERATOR) {
            auto oper = dynamic_cast<const Operator*>(token);
            auto num1 = dynamic_cast<const Number*>(s.top());
            s.pop();
            if (oper->val == '@') {
                s.push(num1);
            } else if (oper->val == '#') {
                auto negNum = new Number(-num1->val);
                alloc.push_back(negNum);
                s.push(negNum);
            } else {
                auto num2 = dynamic_cast<const Number*>(s.top());
                s.pop();
                int res = 0;
                switch (oper->val) {
                    case '+':
                        res = num2->val + num1->val;
                        break;
                    case '-':
                        res = num2->val - num1->val;
                        break;
                    case '*':
                        res = num2->val * num1->val;
                        break;
                    case '/':
                        res = num2->val / num1->val;
                        break;
                    default:
                        break;
                }
                auto resNum = new Number(res);
                alloc.push_back(resNum);
                s.push(resNum);
            }
        }
    }
    auto ansNum = dynamic_cast<const Number*>(s.top());
    s.pop();
    if (!ansNum) {
        throw std::runtime_error("computePostfix(): incorrect postfix expression");
    }
    int ans = ansNum->val;
    for (Token *token : alloc) {  // Clean resources
        delete token;
    }
    return ans;
}
