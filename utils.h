#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
bool findop(std::string op);

static std::vector<const char *> keywds();

static std::vector<const char *> ops();
// #define DEBUG 1
// #define DEBUG 1
template <typename F>
int forline(const char* filename, F && func)
{
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    char* line = NULL;
    size_t len = 0;
    while ((getline(&line, &len, fp)) != -1) {
        (std::forward<F&&>(func))(&line);
    }
    fclose(fp);
    if (line)
        free(line);
    return 0;
}
bool alnum(char ch);

bool alpha(char ch);

bool punct(char ch);

bool digit(char ch);

bool is_keywd(std::string s);

bool is_number(std::string s);

bool is_stringliteral(std::string s);

bool is_punct(std::string s);

bool is_op(std::string s);

std::string ctostr(char c);
static std::vector<int> ops_prec();
int precedence(std::string op);
template<typename TKey, typename TValue, typename Predicate>
std::optional<TValue> mapfindfirst (const std::map<TKey, TValue> & m, 
             Predicate && p)
{
    typename std::map<TKey,TValue>::const_iterator it = m.begin();
    typename std::map<TKey,TValue>::const_iterator end = m.end();

    for( ; it != end ; ++it)
    {
        TKey key = it->first;
        if ((std::forward<Predicate&&>(p))(key))
            return it->second;
    }   
    return {};  
}