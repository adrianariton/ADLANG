#pragma once
#include <map>

enum Configs { ARCHITECTURE, LOG_OUTPUT };

class Config {
public:
    static Config &conf()
    {
        static Config instance;
        return instance;
    }
    std::map<Configs, int> get()
    {
        return value;
    }

    int get(Configs s)
    {
        return value[s];
    }
    void set(Configs conf, int value_)
    {
        value.emplace(conf, value_);
    }

private:
    Config() = default;
    ~Config() = default;
    std::map<Configs, int> value;
};