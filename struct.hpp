#pragma once
#include <vector>
enum StructType {
    PRIMITIVE,
    COMPLEX,
};

class Struct {
public:
    Struct(std::string _name, std::map<std::string, Struct> dependencies)
    {
        this->type = COMPLEX;
        this->_name = _name;
        this->dependencies = dependencies;
    }

    Struct(std::string _name)
    {
        this->type = PRIMITIVE;
        this->_name = _name;
        this->dependencies = {};
    }

    Struct(const Struct &s)
    {
        this->type = s.type;
        this->_name = s._name;
        this->dependencies = s.dependencies;
    }

    Struct()
    {
        Struct("none");
    }

    std::string operator()()
    {
        return this->_name;
    }
    bool is_primitive()
    {
        return this->type == PRIMITIVE;
    }
    std::optional<std::map<std::string, Struct>> deps()
    {
        if (this->is_primitive())
            return {};
        return this->dependencies;
    }

    std::string name()
    {
        return _name;
    }

private:
    std::string _name;
    std::map<std::string, Struct> dependencies;
    StructType type;
};

inline std::vector<Struct> primitive_structs()
{
    static std::vector<Struct> v({ Struct("number"), Struct("function") });
    return v;
}

inline Struct stype(std::string iden)
{
    return Struct(iden);
}