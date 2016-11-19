#include "Parser.h"

int main() {
    {
        // Test lexical analyzer
        //Lexer::test();

        // Test syntactic analyzer
        Parser::test();
    }
    checkMemoryLeaks();
    return 0;
}
