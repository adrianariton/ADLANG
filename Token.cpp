#include "Token.h"
#include "config.hpp"
#include <vector>
#include <cstring>
Token::Token(TokenType type, std::string value) {
    this->value = value;
    this->type = type;
}


void Token::update(std::string value) {
    this->value = value;
    
    if (is_keywd(value))
        this->type = KEYWD;
    else if (is_number(value)) {
        this->type = LITERAL;
    }
    else if (is_stringliteral(value))
        this->type = LITERAL;
    else if (is_op(value))
        this->type = OPERATOR;
    else if (is_punct(value))
        this->type = PUNCTUATOR;
    else
        this->type = IDENTIFIER;
    this->subtype = _NONE;

    if (is_number(value)) {
        this->subtype = NUMERIC;
    }

    if (!(*this).value.compare("("))
        this->subtype = OPENBRACK;
    else  if (!(*this).value.compare(")"))
        this->subtype = CLOSEDBRACK;
    
    else  if (!(*this).value.compare(","))
        this->subtype = _COMMA;
    
    else  if (!(*this).value.compare("call"))
        this->subtype = _SYSCALL;
        
    if (!(*this).value.compare("nil"))
        this->type = NIL;
    if (!(*this).value.compare("_"))
        this->type = NIL;
    if ((this->value).rfind("$$", 0) == 0) {
        this->subtype = REG;
    }
    if ((this->value).rfind("$$[", 0) == 0) {
        this->regtype = REGDEREF;
    } else {
        this->regtype = REGPTR;
    }
    if (!(*this).value.compare("=>"))
        this->subtype = _COMMA_TO;
    
    if (!(*this).value.compare("@")) {
        this->type = NIL;
        this->subtype = _KEYWD;
    }
    if (!(*this).value.compare("make")) {
        this->type = NIL;
        this->subtype = _MAKE;
    }
    if (!(*this).value.compare("func")) {
        this->type = IDENTIFIER;
        this->subtype = _MAKE_FUNC;
    }
    if (!(*this).value.compare("&")) {
        this->type = IDENTIFIER;
        this->subtype = _REFF;
    }

    if (!(*this).value.compare("??")) {
        this->type = IDENTIFIER;
        this->skippable = true;
    }
    if (is_keywd(value)) {
        this->type = KEYWD;
    }
    if (!(*this).value.compare("if")) {
        this->type = IDENTIFIER;
        this->subtype = _IF;
    }
    if (!(*this).value.compare("while")) {
        this->type = IDENTIFIER;
        this->subtype = _WHILE;
    }
    this->logtok();
}

Token::Token(std::string value)
{
    this->value = value;
    this->update(value);
}

std::string Token::val() {
    if ((this->value).rfind("$$", 0) == 0) {
        return (this->value).substr(2);
    }
    return this->value;
    
}

void Token::logtok()
{
    if (Config::conf().get(LOG_OUTPUT))
        std::cout<<"\t\t;; Token{"<<(this->value)<<", "<<(this->type)<< ", "<<(this->subtype)<<", |"<<(this->regtype)<<"}\n";
}

void Token::logtok_NODEBUG()
{
    std::cout<<"\t\t;; Token{"<<(this->value)<<", "<<(this->type)<< ", "<<(this->subtype)<<", |"<<(this->regtype)<<"}\n";
}

