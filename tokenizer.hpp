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
    inline std::vector<Token> tokenize(bool old_format=false)
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
                        tokens.at(tokens.size() - 1).logtok();
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

        if (tokens.size() == 0)
            return tokens;

        if (buf.size() > 0)
            tokens.push_back(Token(buf));
        m_index = 0;

        for (int i = 0; i < tokens.size() - 1; ++i) {
            if (tokens.at(i).type == IDENTIFIER && tokens.at(i).type != KEYWD &&
                tokens.at(i + 1).subtype != OPENBRACK && tokens.at(i).subtype != _OLD_FORMAT_SPECIFIER)
                tokens.at(i).subtype = VARIABLE;
        }


        bool do_add_nil = true;

        if (tokens.at(0).subtype == _MAKE)
            do_add_nil = false;
        if (tokens.at(0).subtype == _OLD_FORMAT_SPECIFIER) {
            do_add_nil = false;
            tokens.erase(tokens.begin());
        }
        if (do_add_nil == false)
            return tokens;
        std::vector<Token> new_toks;
                std::cout<<";; OLD  TOKENS _ \n";

        for (auto & tok : tokens)
            tok.logtok(); 
        std::cout<<";; ADDING NEW TOKENS _ \n";
        for (auto& tok: tokens) {
            if (tok.type == IDENTIFIER) {
                new_toks.push_back(Token("_"));
            }
            new_toks.push_back(tok);
        }
        for (auto & tok : new_toks)
            tok.logtok(); 

        std::cout<<";; ADDED NEW TOKENS _ \n";

        return new_toks;
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