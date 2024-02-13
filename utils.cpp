#include "utils.h"
bool findop(std::string op)
{
    for (int i = 0; i < ops().size(); ++i) {
        if (ops()[i] == op)
            return true;
    }
    return false;
}
static std::vector<const char *> keywds()
{
    return std::vector<const char *>({ "end", "return", "out", "if", "else",
                                       "for", "while", "loop", "let", "set" });
}

static std::vector<const char *> ops()
{
    return std::vector<const char *>(
            { "&", "*", "-", "+",  "/",  "**", "++", "--", "//", "and", "=", "clone",
              "~", "^", ">=", "<=", ">",  "<",  "==", ",",  "=>",  "<-", "??" });
}

static std::vector<int> ops_prec()
{
    return std::vector<int>({ 0, 2, 1, 1, 2, 0, 0, 0, 0,  1,  0, 0,
                              0, 3, 0, 0, 0, 0, 0, -1, 90, 90, 0 });
}

int precedence(std::string op)
{
    for (int i = 0; i < ops().size(); ++i) {
        if (!op.compare(ops()[i])) {
            return ops_prec()[i];
        }
    }
    return 0;
}

bool alnum(char ch)
{
    return std::isalnum(static_cast<unsigned char>(ch));
}

bool alpha(char ch)
{
    return std::isalpha(static_cast<unsigned char>(ch));
}

bool punct(char ch)
{
    return std::ispunct(static_cast<unsigned char>(ch));
}

bool digit(char ch)
{
    return std::isdigit(static_cast<unsigned char>(ch));
}

bool is_keywd(std::string s)
{
    for (auto &keywd : keywds()) {
        if (!s.compare(keywd))
            return true;
    }
    return false;
}

bool is_number(std::string s)
{
    bool neg = (s.at(0) == '-');
    int i = 0;
    for (char &c : s) {
        i++;
        if (i == 1 && neg)
            continue;
        if (digit(c) || c == '.')
            return true;
    }

    return false;
}

bool is_stringliteral(std::string s)
{
    if (s.at(0) == '\"' && s.at(s.size() - 1) == '\"')
        return true;
    return false;
}

bool is_punct(std::string s)
{
    if (punct(s.at(0)) && s.size() == 1)
        return true;
    return false;
}

bool is_op(std::string s)
{
    for (auto &keywd : ops()) {
        if (!s.compare(keywd))
            return true;
    }
    return false;
}

std::string ctostr(char c)
{
    std::string s(1, c);
    return s;
}
