#pragma once
#include "Token.h"
#include "struct.hpp"
class Var {
public:
    Var(std::string name, Struct type)
            : m_type(type)
            , m_name(name)
    {
    }

    Var(std::string name, int param_no_)
            : m_name(name)
            , param_no(param_no_)
    {
        m_type = stype("function");
    }
    Var(Token tok, std::vector<Token> params)
    {
        if (tok.type != IDENTIFIER)
            exit(-1);
        if (params.size() != 1)
            exit(-99);
        Token rvalue = params.at(0);
        if (rvalue.type == LITERAL) {
            m_type = stype("number");
            m_name = tok.value;
        }
    }
    Var(Token tok)
    {
        if (tok.type != IDENTIFIER)
            exit(-1);
        m_type = stype("number"); // TODO change
        m_name = tok.value;
    }
    void set_return(int val)
    {
        return_no = val;
    }
    void set_param_no(int val)
    {
        return_no = val;
    }
    void movetype(std::string tp)
    {
        m_type = stype(tp);
        is_fun_ptr = true;
    }
    int get_return()
    {
        return return_no;
    }
    Struct type()
    {
        return m_type;
    }
    std::string name()
    {
        return m_name;
    }

    std::string name() const
    {
        return m_name;
    }
    friend bool operator<(Var const &a, Var const &b)
    {
        return a.name().compare(b.name());
    }

    bool is_function_ptr()
    {
        return is_fun_ptr;
    }

private:
    Struct m_type;
    std::string m_name;
    int param_no = 0;
    int return_no = 0;
    bool is_fun_ptr = false;
};