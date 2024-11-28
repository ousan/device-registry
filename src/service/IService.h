#pragma once

#include <memory>

#include "IRepository.h"

class IService{
public:
    virtual std::string getName() = 0;
};

class IDeviceService: public IService{
public:
    virtual const std::string getAllDevices() = 0;
    virtual const std::string getDevice(std::string id) = 0;
};

class ILocationService: public IService{
public:
    virtual const std::string getAllLocations() = 0;
    virtual const std::string getLocation(std::string id) = 0;
    virtual bool addLocation(const std::string&) = 0;
};