# Simple-Calculator

A simple calculator program based on lexical analysis and syntactic analysis.

Operator support: '+', '-', '*', '/', '(', ')'.

Operand support: integers(including negative).

## Algorithm Description

### Lexical analysis

Token declaration: [Token.h](./src/Token.h) [Token.cpp](./src/Token.cpp)

[Lexer.scan()](./src/Lexer.cpp): scan one token from input stream and return it.

Run [Lexer::test()](./src/Lexer.cpp) to test the lexer.

### Syntactic analysis

[Parser.scan()](./src/Parser.cpp): convert an infix expression from the input stream to its postfix expression.

Run [Parser::test()](./src/Parser.cpp) to test the parser.

**Grammar:**

CFG(Context-free grammar):

```
expr -> expr + A
      | expr - A
      | A

A -> A * B
   | A / B
   | B

B -> + B
   | - B
   | factor

factor -> ( expr )
        | num
```

SDT(Syntax-directed translation scheme):

```
expr -> expr + A  { appendToPostfix('+'); }
      | expr - A  { appendToPostfix('-'); }
      | A

A -> A * B  { appendToPostfix('*'); }
   | A / B  { appendToPostfix('/'); }
   | B

B -> + B  { appendToPostfix('@'); }
   | - B  { appendToPostfix('#'); }
   | factor

factor -> ( expr )
        | num  { appendToPostfix(num); }
```

Remove left-recursive:

```
expr -> A restA

restA -> + A  { appendToPostfix('+'); } restA
       | - A  { appendToPostfix('-'); } restA
       | e

A -> B restB

restB -> * B  { appendToPostfix('*'); } restB
       | / B  { appendToPostfix('/'); } restB
       | e

B -> + B  { appendToPostfix('@'); }
   | - B  { appendToPostfix('#'); }
   | factor

factor -> ( expr )
        | num  { appendToPostfix(num); }
```

**Notice that in the postfix expression, unary operator '@' and '#' denotes the positive operator '+' and the negative operator '-' respectively.**

## License

See the [LICENSE](./LICENSE.md) file for license rights and limitations.
