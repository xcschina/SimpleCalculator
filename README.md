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
Postfix: 8 # 20 4 / 3 5 - 20 * + - 3 + 4 + 88 8 / + 1 - 3 +
 Answer: 47

  Infix: ( 60 /(2*(3+4)+(5- 2)/ 3)-1-1) * 8-(20/4+(3-5) *20+3+ (- 4) +88/8-(2-3))
Postfix: 60 2 3 4 + * 5 2 - 3 / + / 1 - 1 - 8 * 20 4 / 3 5 - 20 * + 3 + 4 # + 88 8 / + 2 3 - - -
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

### Steps:

* [Lexical analysis](#lexical-analysis)
* [Syntactic analysis](#syntactic-analysis)
* [Calculate postfix expression](#calculate-postfix-expression)

### Lexical analysis

Run [Lexer::test()](./src/Lexer.cpp) to test the lexer.

[Lexer.scan()](./src/Lexer.cpp): scan one token from input stream and return it.

Token declaration: [Token.h](./src/Token.h) [Token.cpp](./src/Token.cpp)

### Syntactic analysis

Run [Parser::test()](./src/Parser.cpp) to test the parser.

[Parser.scan()](./src/Parser.cpp): convert an infix expression from the input stream to its postfix expression.

**Notice** that in the postfix expression, unary operator '@' and '#' denote the positive operator '+' and the negative operator '-' respectively.

#### Grammar

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
       | ε

A -> B restB

restB -> * B  { appendToPostfix('*'); } restB
       | / B  { appendToPostfix('/'); } restB
       | ε

B -> + B  { appendToPostfix('@'); }
   | - B  { appendToPostfix('#'); }
   | factor

factor -> ( expr )
        | num  { appendToPostfix(num); }
```

First and Follow:

| Nonterminal | First | Follow |
|:-----------:|-------|--------|
|expr|+, -, (, num|$, )|
|A|+, -, (, num|$, ), +, -|
|restA|+, -, ε|$, )|
|B|+, -, (, num|$, ), +, -, *, /|
|restB|*, /, ε|$, ), +, -, |
|factor|(, num|$, ), +, -, *, /|

Predictive table(empty block denotes error):

|   | + | - | * | / | ( | ) | num | $ |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|:---:|:-:|
|expr|expr -> A restA|expr -> A restA| | |expr -> A restA| |expr -> A restA| |
|A|A -> B restB|A -> B restB| | |A -> B restB| |A -> B restB| |
|restA|restA -> + A restA|restA -> - A restA| | | |restA -> ε| |restA -> ε|
|B|B -> + B|B -> - B| | |B -> factor| |B -> factor| |
|restB|restB -> ε|restB -> ε|restB -> * B restB|restB -> / B restB| |restB -> ε| |restB -> ε|
|factor| | | | |factor -> ( expr )| |factor -> num| |

### Calculate postfix expression

Refer to [postfix algorithm](https://en.wikipedia.org/wiki/Reverse_Polish_notation).

## License

See the [LICENSE](./LICENSE.md) file for license rights and limitations.
