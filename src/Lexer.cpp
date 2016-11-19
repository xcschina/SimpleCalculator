#include "Lexer.h"
#include <cctype>

using std::string;

Lexer::Lexer() : cur(' ') {}

Token* Lexer::scan() {
    while (cur == '\n' || cur == ' ' || cur == '\t') {
        // New-line character denotes the end of input
        if (cur == '\n' || scanf("%c", &cur) != 1) {
            return new Token(Token::END_INPUT);
        }
    }
    if (isdigit(cur)) {  // Number
        int num = 0;
        do {
            num = 10 * num + (cur - '0');
        } while (scanf("%c", &cur) == 1 && isdigit(cur));
        return new Number(num);
    }
    auto token = new Operator(cur);  // Operator
    cur = ' ';
    return token;
}

void Lexer::test() {
    Lexer lexer;
    int cnt = 1;
    bool end = false;
    printf("Input an expression: ");
    while (!end) {
        auto token = lexer.scan();
        printf("\nToken #%d:\n", cnt++);
        switch (token->tag) {
            case Token::NUM:
                printf(" Type: NUMBER\n");
                printf("Value: %d\n", (dynamic_cast<Number*>(token))->val);
                break;
            case Token::OPERATOR:
                printf(" Type: OPERATOR\n");
                printf("Value: %c\n", (dynamic_cast<Operator*>(token))->val);
                break;
            case Token::END_INPUT:
                printf(" Type: END_INPUT\n");
                end = true;
                break;
            default:
                break;
        }
        delete token;
        token = nullptr;
    }
}
