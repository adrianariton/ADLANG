#pragma once
#include "Token.h"
#include "resolver.hpp"
#include "var.hpp"
#include <optional>
#include <queue>
#include <stack>
#include <vector>
#define BPOFF 1
#define IS_VTYPE_FUNCTION(vtype) (!(vtype.value().name().compare("function")))
#define IS_FUNCTIONAL(tok) \
    (!(findvartype(tok.value).value().name().compare("function")))

int stoisafe(std::string a)
{
    if (!a.compare("??"))
        return -1;
    return std::stoi(a);
}

enum JMP_STATE {
    EQ,
    NE,
    ALL
};

enum SCOPE_TYPE {
    FUNCT_SCOPE,
    IF_SCOPE,
    FOR_SCOPE,
    WHILE_SCOPE
};

class Translator {
public:
    explicit Translator(std::vector<Token> toks)
            : m_tokens(toks)
    {
    }
    void update(std::vector<Token> toks)
    {
        m_tokens.clear();
        for (auto &t : toks) {
            m_tokens.push_back(t);
        }
    }
    void update(int _line)
    {
        line = _line;
    }

    void init()
    {
        print_start();
    }
    void translate()
    {
        std::vector<Token> st;
        m_index = 0;
        while (peek().has_value()) {
            auto tok = consume();
            tok.logtok();

            if (tok.skippable) {
                st.push_back(tok);
            }
            else if (tok.type == IDENTIFIER && tok.subtype == _SYSCALL) {
                std::vector<Token> params;

                int identifiers = 1;
                int nils = 0;
                while (!st.empty() && nils < identifiers) {
                    if (st.at(st.size() - 1).type == NIL)
                        nils++;
                    if (nils == identifiers)
                        break;
                    if (st.at(st.size() - 1).type == IDENTIFIER)
                        identifiers++;
                    params.push_back(st.at(st.size() - 1));
                    st.pop_back();
                }
                st.pop_back();

                auto res = handle_function(tok, params);
                if (res.has_value()) {
                    st.push_back(res.value());
                }
            } else if (tok.type == KEYWD || tok.type == IDENTIFIER) {
                std::cout<<";; resolving... \n";
                std::vector<Token> params;
                if (!is_fun_decl()) {
                    while (!st.empty() && st.at(st.size() - 1).type != NIL) {
                        params.push_back(st.at(st.size() - 1));
                        st.pop_back();
                    }

                    // if modifier, push make as param
                    if (!st.empty() && (st.at(st.size() - 1).type == NIL) 
                            && (st.at(st.size() - 1).subtype == _MAKE)) {
                        params.push_back(Token("make"));        
                    } 
                    
                    if (!st.empty())
                        st.pop_back();
                    if (tok.type == KEYWD) {
                        auto return_tokens = handle_keywd(tok, params);
                        if (return_tokens.has_value()) {
                            for (auto rtok : return_tokens.value())
                                st.push_back(rtok);
                        }
                        continue;
                    }

                    
                }

                auto res = handle_function(tok, params);
                if (res.has_value()) {
                    std::cout<<";; stpush ";
                    res.value().logtok();
                    std::cout<<"\n\n";
                    st.push_back(res.value());
                }

            } else if (tok.subtype == _COMMA_TO) {
                // suntem in scope
                std::cout << ";;";
                for (auto k : scopes.back().second) {
                    std::cout << " @param:" << (k.first.name()) << " ";
                }
                std::cout << "\n";
                activate_scope();
            } else if (tok.type == OPERATOR) {
                std::vector<Token> params;
                for (int i = 0; i < 2; ++i) {
                    params.push_back(st.at(st.size() - 1));
                    st.pop_back();
                }
                if (auto res = handle_operator(tok, params)) {
                    res.value().logtok();
                    st.push_back(res.value());
                } else {
                    auto res1 = handle_operator_asm(tok, params);
                    if (res1.has_value()) {
                        st.push_back(res1.value());
                    }
                }
            }

            else {
                st.push_back(tok);
            }
        }
    }

private:
    int line = 0;
    std::vector<Token> m_tokens;
    size_t m_index = 0;
    size_t m_stack_top = 0;
    std::map<Var, int> variables;
    std::vector<std::pair<std::string, std::map<Var, int>>> scopes;
    std::vector<std::pair<std::string, SCOPE_TYPE>> scope_types;
    std::vector<size_t> scopes_stack_tops;
    bool scope_is_active = false;
    int fun_params = 0;

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

    void change_scope(std::string scope_name, SCOPE_TYPE scope_type = FUNCT_SCOPE)
    {
        auto p = std::pair<std::string, std::map<Var, int>>(scope_name, {});
        scopes.push_back(p);
        scopes_stack_tops.push_back(0);
        scope_is_active = false;
        fun_params = 0;
        auto type = std::pair<std::string, SCOPE_TYPE>(scope_name, scope_type);
        scope_types.push_back(type);
    }

    void change_scope_copy(std::string scope_name, SCOPE_TYPE scope_type = FUNCT_SCOPE)
    {
        if (scopes.empty()) {
            std::map<Var, int> vcopy = variables;
            auto last = std::pair<std::string, std::map<Var, int>>(scope_name, vcopy);
            scopes.push_back(last);
            scopes_stack_tops.push_back(m_stack_top);
            auto type = std::pair<std::string, SCOPE_TYPE>(scope_name, scope_type);
            scope_types.push_back(type);
            return;
        }

        std::pair<std::string, std::map<Var, int>> last = scopes.back();
        last.first = scope_name;
        scopes.push_back(last);
        int lasttop = scopes_stack_tops.back();
        scopes_stack_tops.push_back(lasttop);
        auto type = std::pair<std::string, SCOPE_TYPE>(scope_name, scope_type);
        scope_types.push_back(type);
    }

    void enter_fundefscope(std::string scope_name)
    {
        change_scope(scope_name);
    }

    void enter_ifscope()
    {
        change_scope_copy(".F" + std::to_string(line), IF_SCOPE);
    }

    void update_scope(std::vector<Token> params)
    {
        int index = 0;
        for (int i = 0; i < params.size(); ++i) {
            auto v = Var(params.at(i));
            scopes.back().second.emplace(v, i);
            scopes_stack_tops.back() += 1;
        }
    }

    void end_scope()
    {
        if (get_current_scope_type() == IF_SCOPE) {
            std::string lbl = get_current_scope_name();
            std::cout<<lbl<<":\n";
            exit_scope(true);
        }
    }

    void exit_scope(bool just_pop = false)
    {
        scopes.pop_back();
        scopes_stack_tops.pop_back();
        if (!just_pop) {
            scope_is_active = false;
            fun_params = 0;
        }
    }

    void activate_scope()
    {
        scope_is_active = true;
        std::cout << ";; activating scope: " << scopes.back().first
                  << " #params=" << scopes.back().second.size() << "\n";
        add_fun(scopes.back().first, scopes.back().second.size());
    }

    bool scope_isactive()
    {
        return scope_is_active;
    }

    std::optional<std::map<Var, int>::iterator> getvariter(std::string val, int offset = 0)
    {
        for (std::map<Var, int>::iterator iter = vars(offset).begin();
             iter != vars(offset).end(); ++iter) {
            Var t = iter->first;
            if (!((Var)t).name().compare(val))
                return iter;
        }
        return {};
    }

    std::optional<std::map<Var, int>::iterator> findvariter(std::string val, int& offset)
    {
        offset = 0;
        for (offset = 0; offset <= scopes_stack_tops.size(); ++offset) {
            for (std::map<Var, int>::iterator iter = vars(offset).begin();
                iter != vars(offset).end(); ++iter) {
                Var t = iter->first;
                if (!((Var)t).name().compare(val))
                    return iter;
            }
        }
        return {};
    }

    std::optional<int> getvaraddr(std::string val, int offset = 0)
    {
        auto iter = getvariter(val, offset);
        if (iter.has_value())
            return iter.value()->second;
        return {};
    }

    std::optional<Struct> getvartype(std::string val, int offset = 0)
    {
        auto var = getvarvar(val, offset);
        if (var.has_value())
            return var.value().type();
        return {};
    }

    std::optional<Struct> findvartype(std::string val, int offset = 0)
    {
        auto var = findvarvar(val);
        if (var.has_value())
            return var.value().type();
        return {};
    }

    std::optional<Var> getvarvar(std::string val, int offset = 0)
    {
        auto iter = getvariter(val, offset);
        if (iter.has_value())
            return iter.value()->first;
        return {};
    }

    std::optional<Var> findvarvar(std::string val)
    {
        int offset = 0;
        auto iter = findvariter(val, offset);
        if (iter.has_value())
            return iter.value()->first;
        return {};
    }

    int countvarvar(std::string val, int offset = 0)
    {
        int k = 0;
        for (std::map<Var, int>::iterator iter = vars(offset).begin();
             iter != vars(offset).end(); ++iter) {
            Var t = (iter->first);
            if (!((Var)t).name().compare(val))
                k++;
        }
        return k;
    }

    void setvarret(std::string val, int ret, int offset = 0)
    {
        for (std::map<Var, int>::iterator iter = vars(offset).begin();
             iter != vars(offset).end(); ++iter) {
            Var t = (iter->first);
            auto k = (iter->second);
            if (!((Var)t).name().compare(val)) {
                vars(offset).erase(iter);
                t.set_return(ret);
                vars(offset).insert({ t, k });
                return;
            }
        }
    }

    void setvarparams(std::string val, int params, int offset = 0)
    {
        for (std::map<Var, int>::iterator iter = vars(offset).begin();
             iter != vars(offset).end(); ++iter) {
            Var t = (iter->first);
            auto k = (iter->second);
            if (!((Var)t).name().compare(val)) {
                vars(offset).erase(iter);
                t.set_param_no(params);
                vars(offset).insert({ t, k });
                return;
            }
        }
    }

    void setvarasfun(std::string val, int offset = 0)
    {
        for (std::map<Var, int>::iterator iter = vars(offset).begin();
             iter != vars(offset).end(); ++iter) {
            Var t = (iter->first);
            auto k = (iter->second);
            if (!((Var)t).name().compare(val)) {
                vars(offset).erase(iter);
                t.movetype("function");
                vars(offset).insert({ t, k });
                return;
            }
        }
    }

    std::optional<std::string> getvarstackaddr(std::string val, int offset = 0,  int align = 16)
    {
        auto o_ind = getvaraddr(val, offset);
        if (o_ind.has_value()) {
            if (o_ind.value() < 0)
                return "[x29 , #" + std::to_string((-align * o_ind.value())) +
                       "]";

            return "[x29 , #-" + std::to_string((align * o_ind.value())) + "]";
        }
        return {};
    }

    std::optional<std::string> stacktop(int align = 16)
    {
        return "[x29 , #-" + std::to_string((align * sttop())) + "]";
    }

    std::optional<Token> stacktoptok(int align = 16)
    {
        return "$$" + stacktop().value();
    }

    void add_var(Token tok, std::vector<Token> params)
    {
        vars().insert({ Var(tok, params), sttop() });
    }

    void add_var(Token tok)
    {
        vars().insert({ Var(tok), sttop() });
    }

    void add_fun(std::string name, int param_no)
    {
        vars(1).insert({ Var(name, param_no), 0 });
    }

    void set_var(Token tok, size_t ind)
    {
        vars().insert({ Var(tok), ind });
    }

    void set_var(Token tok, size_t ind, bool asfun)
    {
        vars().insert({ Var(tok), ind });
    }

    void ldr(std::string val, std::string reg)
    {
        /* load var into reg */
        auto x = getvarstackaddr(val);
        if (x.has_value())
            std::cout << "\t"
                      << "ldr"
                      << " " << reg << ", " << x.value() << " ;; [" << val
                      << "]"
                      << "\n";
    }

    void str(std::string val, std::string reg)
    {
        /* load reg back into var */
        auto x = getvarstackaddr(val);
        if (x.has_value())
            std::cout << "\t"
                      << "str"
                      << " " << reg << ", " << x.value() << " ;; [" << val
                      << "]"
                      << "\n";
    }

    void mov(std::string val, std::string reg)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "mov"
                  << " " << reg << ", #" << val << "\n";
    }

    void ldr(Token tok, std::string reg)
    {
        if (tok.subtype == REG) {
            if (tok.regtype == REGDEREF)
                std::cout << "\t"
                          << "ldr"
                          << " " << reg << ", " << tok.val() << "\n";
            else
                std::cout << "\t"
                          << "mov"
                          << " " << reg << ", " << tok.val() << "\n";
        } else if (tok.subtype == NUMERIC) {
            mov(tok.value, reg);
        } else {
            ldr(tok.value, reg);
        }
    }

    void str(Token tok, std::string reg)
    {
        /* load reg back into var */
        if (tok.subtype == REG) {
            std::cout << "\t"
                      << "str"
                      << " " << reg << ", " << tok.val() << "\n";
        } else {
            str(tok.value, reg);
        }
    }

    void cmp(std::string reg1, std::string reg2)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "cmp"
                  << " " << reg1 << ", " << reg2 << "\n";
    }

    void cmpt0(Token tok)
    {
        /* load val into reg */
        if (tok.subtype == REG)
        {
            ldr(tok, "x14");
            std::cout<<"\tcmp x14, #0\n";
        }
        else

        std::cout << "\t"
                  << "cmp"
                  << " " << tok.val() << ", " << "#0" << "\n";
    }

    void jmp(std::string label, JMP_STATE state = ALL)
    {
        /* load val into reg */
        if (state == ALL)
        std::cout<<"b "<<label<<"\n";

        if (state == NE)
        std::cout<<"b.ne "<<label<<"\n";
        if (state == EQ)
        std::cout<<"b.eq "<<label<<"\n";
    }

    void cmp(std::string output, std::string reg1, std::string reg2)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "cmp"
                  << " " << reg1 << ", " << reg2 << "\n";
        std::cout << "\tcset " << output << ", eq\n";
    }

    void addto(std::string reg1, std::string reg2)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "add"
                  << " " << reg1 << ", " << reg1 << ", " << reg2 << "\n";
    }

    void addto(std::string reg1, int reg2)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "add"
                  << " " << reg1 << ", " << reg1 << ", #" << reg2 << "\n";
    }

    void add(std::string reg1, std::string reg2, std::string reg3)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "add"
                  << " " << reg1 << ", " << reg2 << ", " << reg3 << "\n";
    }

    void subfrom(std::string reg1, std::string reg2)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "sub"
                  << " " << reg1 << ", " << reg1 << ", " << reg2 << "\n";
    }

    void subfrom(std::string reg1, int off)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "sub"
                  << " " << reg1 << ", " << reg1 << ", #" << off << "\n";
    }

    void addsp(int off, int align = 16)
    {
        addto("sp", off * align);
        sttop() -= off;
    }

    void sub(std::string reg1, std::string reg2, std::string reg3)
    {
        /* load val into reg */
        std::cout << "\t"
                  << "sub"
                  << " " << reg1 << ", " << reg2 << ", " << reg3 << "\n";
    }

    void set_var(Token tok, std::vector<Token> params)
    {
        auto rvalue = params.at(0);
        std::string action = "ldr";
        std::string c = "";
        if (rvalue.type == LITERAL && rvalue.subtype != REG) {
            action = "mov";
            c = "#";
        }
        auto x = getvarstackaddr(tok.val());
        if (x.has_value()) {
            std::cout << "\t" << action << " "
                      << "x15"
                      << ", " << c << rvalue.val() << "\n";
            std::cout << "\t"
                      << "str"
                      << " "
                      << "x15"
                      << ", " << x.value() << "\n";
        }
    }

    void pop_stack(std::string reg, int align = 16)
    {
        // std::cout<<"\tpop "<<reg<<"\n";
        std::cout << "\tldr " << reg << ", [sp], #" << align << " ;; pop "
                  << reg << "\n";
        sttop()--;
    }
    void push_reg(std::string reg, int align = 16)
    {
        std::cout << "\tstr " << reg << " , [sp, #-" << align << "]! ;; push "
                  << reg << "\n";
        sttop()++;
    }
    void push_stack(Token tok)
    {

        if ((findvarvar(tok.val()).has_value() && 
                        IS_FUNCTIONAL(tok))) {
            // if (findvarvar(tok.val()).value().is_function_ptr()) {
                std::cout<<"\tadr x15, "<<tok.val()<<"\n";
                push_reg("x15");
                return;
            // }
        }
        std::string val = "=";
        std::string action = "ldr";
        if (tok.type == LITERAL && tok.subtype == NUMERIC) {
            val = "#";
            action = "mov";
        }

        if (tok.subtype == REG && tok.regtype == REGPTR) {
            action = "mov";
        }
        if (tok.subtype == REG)
            val = "";
        std::cout << "\t\t;; begin push \n";
        std::cout << "\t" << action << " "
                  << " x15, " << (val + tok.val()) << "\n";
        push_reg("x15");
    }

    std::map<Var, int> &vars()
    {
        if (scopes.empty()) {
            return variables;
        }
        return scopes.back().second;
    }

    std::map<Var, int> &vars(size_t offset)
    {
        if (offset == 0)
            return vars();
        if (scopes.size() >= offset) {
            return variables;
        }
        return scopes.at(scopes.size() - 1 - offset).second;
    }

    size_t &sttop()
    {
        if (scopes_stack_tops.empty()) {
            return m_stack_top;
        }
        return scopes_stack_tops.back();
    }

    void begin_fun()
    {
        std::cout << "\tstp x29, x30, [sp, #-16]!\n";
        std::cout << "\tmov x29, sp\n";
    }
    void end_fun(int movsp = 1)
    {
        if (movsp) {
            std::cout << "\tmov sp, x29\n";
            std::cout << "\tldp x29, x30, [sp], #16\n";
        } else {
            std::cout << "\tldp x29, x30, [sp], #16\n";
        }

        std::cout << "\tret\n";
        std::cout << ("end" + scopes.back().first) << ":\n";
    }

    void log_scope()
    {
        if (scopes.empty())
            return;
        std::cout << "\tb " << ("end" + scopes.back().first) << "\n";
        std::cout << ";; begin scope " << scopes.back().first << "\n\n";
        std::cout << scopes.back().first << ":\n";
    }

    std::string get_current_scope_name()
    {
        if (scopes.empty())
            return "main";
        return scopes.back().first;
    }

    SCOPE_TYPE get_current_scope_type()
    {
        if (scopes.empty())
            return FUNCT_SCOPE;
        return scope_types.back().second;
    }

    void push_stack_tok(Token tok)
    {
        if (tok.type == LITERAL) {
            push_stack(tok);
        }

        else if (tok.type == IDENTIFIER) {
            auto stack_index = mapfindfirst(vars(), [tok](Var x) {
                return !x.name().compare(tok.value);
            });
            push_stack(tok);
        }
    }

    void print_start()
    {
        std::cout << ".data\n";
        std::cout << ".text\n";
        std::cout << ".globl _start\n";
        std::cout << "_start:\n";
        std::cout << "\tmov x29, sp\n";
        std::cout << "\tmov x7, x29 ;; store original base pointer\n";
    }

    void print_syscall(Token tok, std::vector<Token> params)
    {
        for (int i = 0; i < params.size() - 1; ++i) {
            auto param = params.at(i);
            char c = '#';
            if (param.type == IDENTIFIER)
                c = '=';
            std::cout << "\tmov   x" << (params.size() - 2 - i) << ", " << c
                      << params.at(i).value << "\n";
        }
        std::cout << "\tmov   x16, #" << params.at(params.size() - 1).value
                  << "\n";
        std::cout << "\tsvc #0\n";
    }

    bool check_operator(Token tok, std::vector<Token> params)
    {
        if (params.size() != 2)
            return false;
        if (params.at(0).type == LITERAL && params.at(1).type == LITERAL &&
            (params.at(0).subtype != REG && params.at(1).subtype != REG))
            return true;
        return false;
    }

    std::optional<Token> handle_operator(Token tok, std::vector<Token> params)
    {
        if (!check_operator(tok, params))
            return {};
        return resolve(tok, params);
    }

    std::optional<Token> handle_operator_asm(Token tok,
                                             std::vector<Token> params)
    {
        // only handle binaries for now
        if (params.size() != 2) {
            return {};
        }

        auto rvalue = params.at(0);
        auto lvalue = params.at(1);
        ldr(lvalue, "x14");
        ldr(rvalue, "x15");
        if (tok.value == "++") {
            addto("x14", "x15");
            str(lvalue, "x14");
            return {};
        }

        else if (tok.value == "--") {
            subfrom("x14", "x15");
            str(lvalue, "x14");
            return {};
        }

        else if (tok.value == "+") {
            add("x13", "x14", "x15");
            push_reg("x13");
            return stacktoptok();
        }

        else if (tok.value == "-") {
            sub("x13", "x14", "x15");
            push_reg("x13");
            return stacktoptok();
        }

        else if (tok.value == "==") {
            cmp("x13", "x14", "x15");
            push_reg("x13");
            ldr(lvalue, "x14");
            ldr(rvalue, "x15");
            cmp("x14", "x15");
            return stacktoptok();
        }
        return {};
    }

    bool is_fun_decl()
    {
        if (peek().has_value())
            return (peek().has_value() && peek().value().subtype == _KEYWD);
        return false;
    }

    void callfun(Token tok)
    {
        auto o_var = getvarvar(tok.val());
        if (o_var.has_value() && o_var.value().is_function_ptr()) {
            auto o_addr = getvarstackaddr(tok.val());
            if (o_addr.has_value()) {
                ldr(tok.val(), "x14");
                std::cout<< "\tblr " << "x14" << "\n";
                return;
            }

        }
        std::cout << "\tbl " << tok.value << "\n";
    }

    std::optional<std::vector<Token>> handle_keywd(Token tok,
                                                   std::vector<Token> params)
    {

        if (!tok.value.compare("end")) {
            end_scope();
        } else if (!tok.value.compare("return")) {
            std::vector<Token> res;
            std::cout << ";; @return: " << params.size()
                      << " of: " << (scopes.back().first) << "\n";
            for (int i = params.size() - 1; i >= 0; --i) {
                ldr(params.at(i), "x" + std::to_string(params.size() - 1 - i));
            }
            // return x0, x1, x2, ..., x11
            setvarret(scopes.back().first, params.size(), 1);
            std::cout
                    << ";; set ret: "
                    << (getvarvar(scopes.back().first, 1).value().get_return())
                    << "\n";
            end_fun();
            exit_scope();
            return res;
        }
        return {};
    }

    std::optional<Token> handle_syscall(Token tok, std::vector<Token> params)
    {
        std::string c = "#";
        std::string act = "mov";
        if (params.at(params.size() - 1).subtype == REG) {
            c = "";
            act = "ldr";
        }
        std::cout << "\t" << act << "   x16, " << c
                  << params.at(params.size() - 1).val() << "\n";
        params.pop_back();
        for (auto &param : params) {
            push_stack_tok(param);
        }
        for (int i = 0; i < params.size(); ++i) {
            pop_stack("x" + std::to_string(i));
        }
        std::cout << "\tsvc #0\n";
        return Token("$$x0");
    }

    void make_tok(Token tok, std::vector<Token> params)
    {
        std::cout<<";; MAKE_TOK: PARAMS#: "<<(params.size())<<"\n";
        // tok.logtok();

        params.at(0).logtok();
        params.at(1).logtok();
        params.at(2).logtok();

        std::string variable = params.at(2).val();
        
        int ret_no = stoisafe(params.at(1).val());
        int param_no = stoisafe(params.at(0).val());

        setvarasfun(variable);
        setvarret(variable, ret_no);
        setvarret(variable, param_no);

        std::cout<<";; make "<<variable<<" :: ret "<<ret_no<<" :: pno "<<param_no<<"\n";

        std::cout<<";; DONE MAKE_TOK\n";
    }

    bool handle_conditionals(Token tok, std::vector<Token> params)
    {
            std::cout<<";; ENTERING IF "<<get_current_scope_name()<<"\n";

        if (tok.subtype == _IF)
        {
            std::cout<<";; OKOK\n";
            enter_ifscope();
                        std::cout<<";; OKOK\n";

            std::cout<<";; ENTERING IF "<<get_current_scope_name()<<"\n";

            cmpt0(stacktoptok().value());
            jmp(get_current_scope_name(), EQ);
            return true;
        }
        return false;
    }

    std::optional<Token> handle_function(Token tok, std::vector<Token> params)
    {
        tok.logtok();

        bool res_ = handle_conditionals(tok, params);
        if (res_)
            return {};

        if (is_fun_decl()) {
            // function declaration
            enter_fundefscope(tok.val());
            update_scope(params);
            log_scope();
            begin_fun();
        }

        else if (tok.subtype == _MAKE_FUNC) {
            make_tok(tok, params);
        }

        else if (tok.subtype == _SYSCALL) {
            return handle_syscall(tok, params);
        }
        // if is function and found in parent or current scope // or is var and in current scope
        else if ((findvarvar(tok.val()).has_value() && 
                        IS_FUNCTIONAL(tok)) || getvarstackaddr(tok.value).has_value()) {
            auto o_addr = getvarstackaddr(tok.value);
            // ... call variable
            std::cout << ";; VAR " << tok.val() << " HERE\n";
            std::cout << ";; PARAMS SIZE: " << params.size() << "\n";
            for (auto par : params) {
                par.logtok_NODEBUG();
            }
            std::cout << "\n";

            // is variable assignment / retrieval
            if (!IS_FUNCTIONAL(tok) && o_addr.has_value()) {
                std::cout<<";; IS_VAR "<<tok.val()<<"\n";
                if (params.size() == 0) {
                    // variable is already existant
                    // return its register
                    std::string addr = o_addr.value();
                    return Token("$$" + addr);
                } else if (params.size() == 1) {
                    // probably new assignment
                    if (params.at(0).subtype == _MAKE) {
                        std::cout<<";; IDENTITY\n";
                        return tok;
                    } else {
                        set_var(tok, params);
                    }
                }
            }

            // function call
            else {

                if (params.size() == 0) {
                    //get address of function
                    return tok;
                }
                if (params.at(0).subtype == _MAKE) {
                    std::cout<<";; IDENTITY\n";
                    return tok;
                } 
                // if function
                std::cout << ";; FCT CALL " << tok.val() << ": @return "
                          << findvarvar(tok.val()).value().get_return()<<" @#params: "<<(params.size())<<"\n";
                // push params
                for (int i = 0; i < params.size(); ++i) {
                    push_stack(params.at(i));
                }
                int ret = findvarvar(tok.value).value().get_return();
                std::cout << ";; ret nr: " << ret << "\n";
                // breakpoint (call function)
                callfun(tok);
                // pop params
                addsp(params.size());
                // push return value (x0)
                push_reg("x0");

                if (ret == 0)
                    return {};
                if (ret == 1) {
                    return stacktoptok().value();
                }
            }

        }

        else {
            std::cout << ";; VAR " << tok.val() << " NOT HERE\n";
            std::cout << ";; VAR " << tok.val() << " NOT HERE "<<params.size()<<"\n";

            if (params.size() == 0) {
                // function declaration header params
                set_var(tok, (-(fun_params + BPOFF)));
                fun_params++;
                return {};
            }

            
            // declare variable
            auto rvalue = params.at(0);

            push_stack_tok(rvalue);
            add_var(tok, params);
        }
        return {};
    }
};