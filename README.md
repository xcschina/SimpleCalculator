# Simple-Calculator

A simple calculator program based on lexical analysis and syntactic analysis.

Operator support: +, -, *, /, (, )

Operand support: integers(including negative)

## Getting Started

### Compile and run

```bash
$ make
$ make run
```

### Some test samples

```
  Infix: - 8 -(20/4+(3 - 5) *20)+3+ 4+88 /8-1+3
Postfix: -8 20 4 / 3 5 - 20 * + - 3 + 4 + 88 8 / + 1 - 3 +
 Answer: 47

  Infix: ( 60 /(2*(3+4)+(5- 2)/ 3)-1-1) * 8-(20/4+(3-5) *20+3+ (- 4) +88/8-(2-3))
Postfix: 60 2 3 4 + * 5 2 - 3 / + / 1 - 1 - 8 * 20 4 / 3 5 - 20 * + 3 + -4 + 88 8 / + 2 3 - - -
 Answer: 40

  Infix: (6*((5   +((2+3)  *8))+ 3))
Postfix: 6 5 2 3 + 8 * + 3 + *
 Answer: 288

  Infix: (-3) *(- 20+(-(2*(3+5))- (8+7)))
Postfix: 3 # 20 # 2 3 5 + * # 8 7 + - + *
 Answer: 153

  Infix: - 3 *( -1+(-(1 -2)) )
Postfix: 3 # 1 # 1 2 - # + *
 Answer: 0
```

## Algorithm Description

### 1. Lexical analysis

Token declaration: [Token.h](./src/Token.h) [Token.cpp](./src/Token.cpp)

[Lexer.scan()](./src/Lexer.cpp): scan one token from input stream and return it.

Run [Lexer::test()](./src/Lexer.cpp) to test the lexer.

### 2. Syntactic analysis

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

### 3. Calculate postfix expression

Refer to [postfix algorithm](https://en.wikipedia.org/wiki/Reverse_Polish_notation).

## License

See the [LICENSE](./LICENSE.md) file for license rights and limitations.
