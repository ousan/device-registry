#pragma once

#include <string>
#include "Location.h"

struct Device{
    Device(const std::string& _id, 
           const std::string& _name, 
           const std::string& _type, 
           const std::string& _serialNumber, 
           const std::string& _location)
    :name(_name), id(_id), type(_type), serialNumber(_serialNumber), location(_location)
    {}
    
    std::string id;
    std::string type;
    std::string name;
    std::string serialNumber;
    std::string location;
};