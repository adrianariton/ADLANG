#pragma once
#include "Token.h"
#include <functional>
#include <map>
#include <stdlib.h>

#define filler_lam [](std::vector<Token> a) { return 0; }

std::map<std::string, std::function<int(std::vector<Token>)>> operatorresolve()
{
    std::map<std::string, std::function<int(std::vector<Token>)>> m;
    m.emplace("+", [](std::vector<Token> a) {
        return stoi(a.at(0).value) + stoi(a.at(1).value);
    });
    m.emplace("-", [](std::vector<Token> a) {
        return stoi(a.at(1).value) - stoi(a.at(0).value);
    });
    m.emplace("/", [](std::vector<Token> a) {
        return stoi(a.at(1).value) / stoi(a.at(0).value);
    });
    m.emplace("*", [](std::vector<Token> a) {
        return stoi(a.at(0).value) * stoi(a.at(1).value);
    });

    return m;
}

Token resolve(Token tok, std::vector<Token> params)
{
    return Token(std::to_string(operatorresolve()[tok.value](params)));
}