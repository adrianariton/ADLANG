#ifndef TOKEN_H
#define TOKEN_H
#include "utils.h"
#include <vector>
enum TokenType {
    OPERATOR, // Arithmetical operators, Relational operators,  Logical
              // operators, Unary operators, Assignment operators, Conditional
              // operators, Comma operator
    IDENTIFIER, // var names
    KEYWD, // key words: return , if , for
    PUNCTUATOR,
    /**
    - Brackets [   ]	Opening and closing brackets indicate single and
    multidimensional array subscript.
    - Parentheses (   )	Opening and closing brackets indicate functions calls,;
    function parameters for grouping expressions etc.
    - Braces {   }	Opening and closing braces indicate the start and end of
    a compound statement.
    - Comma ,	It is used as a separator in a function argument list.
    - Semicolon ;	It is used as a statement terminator.
    - Colon :	It indicates a labeled statement or conditional operator symbol.
    - Asterisk *	It is used in pointer declaration or as multiplication
    operator.
    - Equal sign =	It is used as an assignment operator.
    - Pound sign #	It is used as pre-processor directive.
    */
    LITERAL, // integers chars, floats etc
    ARRAY_LITERAL, // arrays like strings [...]
    NIL,
    STACK_POS
};

enum TokenSubType {
    _NONE,
    OPENBRACK,
    CLOSEDBRACK,
    _COMMA,
    _COMMA_TO,
    _SYSCALL,
    VARIABLE,
    NUMERIC,
    REG,
    _KEYWD,
    _MAKE,
    _MAKE_FUNC,
    _REFF,
    _IF,
    _WHILE,
    _FOR
};

enum RegType {
    REGPTR,
    REGDEREF
};

class Token {
public:
    TokenType type;
    TokenSubType subtype;
    RegType regtype;
    std::string value;
    bool skippable = false;

    Token(TokenType type, std::string value);
    Token(std::string value);
    void logtok();
    void logtok_NODEBUG();
    void update(std::string value);
    std::string val();
private:
    void determineSubtype();
    void determineType();
};
#endif