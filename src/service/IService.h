#pragma once

#include <memory>

#include "IRepository.h"
#include "StatusCode.h"

class IService{
public:
    virtual std::string getName() = 0;
};

class IDeviceService: public IService{
public:
    virtual const StatusCode getAllDevices(std::string& deviceList) const = 0;
    virtual const StatusCode getDevice(const std::string& id, std::string& device) const = 0;
};

class ILocationService: public IService{
public:
    virtual const StatusCode getAllLocations(std::string& locationList) const = 0;
    virtual const StatusCode getLocation(const std::string& id, std::string& location) const = 0;
    virtual const StatusCode addLocation(const std::string&) = 0;
};