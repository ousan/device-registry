#pragma once

#include <string>
#include "Device.h"
#include "Location.h"
#include "StatusCode.h"

class IRepository{
    public: 
        virtual std::string getName() = 0;
};

class IDeviceRepository : public IRepository{
    public: 
        virtual const StatusCode getDevice(const std::string& id, Device& device) const = 0;
        virtual const StatusCode getAllDevices(std::vector<Device>& dList) const = 0;
};

class ILocationRepository : public IRepository{
    public: 
        virtual const StatusCode getLocation(const std::string& id, Location& location) const = 0;
        virtual const StatusCode getAllLocations(std::vector<Location>& dList) const = 0;
        virtual const StatusCode addLocation(const Location& loc) = 0;
};