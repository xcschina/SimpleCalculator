#include "Lexer.h"
#include <cctype>

using std::string;

Lexer::Lexer() : cur(' ') {}

Token* Lexer::scan() {
    while (cur == '\n' || cur == ' ' || cur == '\t') {
        // New-line character denotes the end of input
        if (cur == '\n' || scanf("%c", &cur) != 1) {
            return nullptr;
        }
    }
    if (isdigit(cur)) {  // Check number
        int num = 0;
        do {
            num = 10 * num + (cur - '0');
        } while (scanf("%c", &cur) == 1 && isdigit(cur));
        return new Number(num);
    }
    auto token = new Operator(cur);  // Check operator
    cur = ' ';
    return token;
}

void Lexer::test() {
    Lexer lexer;
    int cnt = 1;
    printf("Input an expression: ");
    while (1) {
        auto token = lexer.scan();
        printf("\nToken #%d:\n", cnt++);
        if (token == nullptr) {
            printf(" Type: END_INPUT\n");
            break;
        } else {
            switch (token->tag) {
                case Token::Tag::NUM:
                    printf(" Type: NUMBER\n");
                    printf("Value: %d\n", (dynamic_cast<Number*>(token))->val);
                    break;
                case Token::Tag::OPERATOR:
                    printf(" Type: OPERATOR\n");
                    printf("Value: %c\n", (dynamic_cast<Operator*>(token))->val);
                    break;
                default:
                    break;
            }
            delete token;
            token = nullptr;
        }
    }
}
