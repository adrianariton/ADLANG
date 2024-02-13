#pragma once
#include "Token.h"
#include <optional>
#include <queue>
#include <stack>
#include <vector>
enum ExpressionType {
    _EXTERN_FUNCTION,
    _SYSCALL_FUNCTION,
    _DOUBLE_OPERATOR,
};

template <typename T> struct v_queue : std::queue<T, std::vector<T>> {
    using std::queue<T, std::vector<T>>::queue;
    // in G++, the variable name is `c`, but it may or may not differ
    std::vector<T> &to_vector()
    {
        return this->c;
    }
};

struct Node {
    Token identifier, op, punctuator;
    ExpressionType type;

    std::vector<Node> expressions;
};

class Parser {
public:
    explicit Parser(std::vector<Token> toks)
            : m_tokens(toks)
    {
    }

    inline std::vector<Token> postfix()
    {
        m_index = 0;
        v_queue<Token> outputQueue;
        std::stack<Token> operatorStack;

        while (peek().has_value()) {
            auto tok = consume();
            tok.logtok();
            if (tok.type == LITERAL || tok.type == ARRAY_LITERAL ||
                tok.type == NIL || tok.subtype == VARIABLE) {
                /* Number */
                outputQueue.push(tok);
            } else if (tok.type == IDENTIFIER || tok.type == KEYWD) {
                /* Function */
                operatorStack.push(tok);
            } else if (tok.type == OPERATOR) {
                while ((!operatorStack.empty()) &&
                       (operatorStack.top().subtype != OPENBRACK) &&
                       (operatorStack.top().type == OPERATOR &&
                        precedence(tok.value) <=
                                precedence(operatorStack.top().value))) {
                    auto op2 = operatorStack.top();
                    operatorStack.pop();
                    outputQueue.push(op2);
                }
                if (tok.subtype != _COMMA)
                    operatorStack.push(tok);
            } else if (tok.subtype == OPENBRACK) {
                operatorStack.push(tok);
            } else if (tok.subtype == CLOSEDBRACK) {
                while (!operatorStack.empty() &&
                       operatorStack.top().subtype != OPENBRACK) {
                    if (operatorStack.empty())
                        return {};
                    auto op2 = operatorStack.top();
                    operatorStack.pop();
                    outputQueue.push(op2);
                }

                if (operatorStack.top().subtype != OPENBRACK)
                    return {};

                operatorStack.pop();

                if (!operatorStack.empty())
                    if (!(operatorStack.top().type == OPERATOR) &&
                        !(operatorStack.top().subtype == OPENBRACK &&
                          operatorStack.top().subtype == CLOSEDBRACK)) {
                        auto poptok = operatorStack.top();
                        outputQueue.push(poptok);
                        operatorStack.pop();
                    }
            }
        }
        while (!operatorStack.empty()) {
            if (operatorStack.top().subtype == OPENBRACK)
                return {};

            auto poptok = operatorStack.top();
            outputQueue.push(poptok);
            operatorStack.pop();
        }
        return outputQueue.to_vector();
    }

private:
    const std::vector<Token> m_tokens;
    size_t m_index = 0;

    [[nodiscard]] std::optional<Token> peek()
    {
        if (m_index >= m_tokens.size()) {
            return {};
        }
        return m_tokens.at(m_index);
    }

    Token consume()
    {
        return m_tokens.at(m_index++);
    }

    std::optional<Token> try_consume(TokenType ttype)
    {
        if (peek().has_value()) {
            if (peek().value().type == ttype)
                return consume();
        }
        return {};
    }

    std::optional<Token> try_consume(TokenSubType ttype)
    {
        if (peek().has_value()) {
            if (peek().value().subtype == ttype)
                return consume();
        }
        return {};
    }
};