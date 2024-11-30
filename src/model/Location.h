#pragma once

#include <string>

struct Location{
    Location() = default;
    Location(const std::string& _id, 
             const std::string& _name, 
             const std::string& _type)
    :name(_name), id(_id), type(_type)
    {}
    
    std::string id;
    std::string type;
    std::string name;
};