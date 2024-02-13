#pragma once
#include "Token.h"
#include "utils.h"
#include <optional>
#include <stack>
class Tokenizer {
public:
    explicit Tokenizer(std::string src)
            : m_src(std::move(src))
    {
    }
    inline std::vector<Token> tokenize()
    {
        std::vector<Token> tokens = {};
        std::string buf = "";

        while (peek().has_value()) {
            char c = consume();
            if ((c == ' ' || c == '\n')) {
                if (buf.size() > 0) {
                    tokens.push_back(Token(buf));
                }
                buf.clear();
            } else if (punct(c)) {
                if (tokens.size() > 0 &&
                    is_punct(tokens.at(tokens.size() - 1).value)) {
                    std::string possible_op =
                            (tokens.at(tokens.size() - 1).value + c);
                    if (findop(possible_op)) {
                        tokens.at(tokens.size() - 1)
                                .update(tokens.at(tokens.size() - 1).value + c);
                        continue;
                    }
                }
                if (buf.size() > 0) {
                    tokens.push_back(Token(buf));
                    buf.clear();
                }
                if (c != ' ' && c != '\n')
                    tokens.push_back(Token(ctostr(c)));
            } else {
                buf += c;
            }
        }

        if (buf.size() > 0)
            tokens.push_back(Token(buf));
        m_index = 0;

        for (int i = 0; i < tokens.size() - 1; ++i) {
            if (tokens.at(i).type == IDENTIFIER && tokens.at(i).type != KEYWD &&
                tokens.at(i + 1).subtype != OPENBRACK)
                tokens.at(i).subtype = VARIABLE;
        }

        return tokens;
    }

private:
    const std::string m_src;
    size_t m_index = 0;
    [[nodiscard]] std::optional<char> peek()
    {
        if (m_index >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index);
    }

    char consume()
    {
        return m_src.at(m_index++);
    }
};