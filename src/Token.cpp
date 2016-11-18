#include "Token.h"

Token::Token(const Tag tag_) : tag(tag_) {}

Token::~Token() {}

Number::Number(const int val_) : Token(NUM), val(val_) {}

Number::~Number() {}

Operator::Operator(const char &val_) : Token(OPERATOR), val(val_) {}

Operator::~Operator() {}
