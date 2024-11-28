#pragma once

#include <string>
#include "Device.h"
#include "Location.h"
#include <nlohmann/json.hpp>

class IRepository{
    public: 
        virtual std::string getName() = 0;
};

class IDeviceRepository : public IRepository{
    public: 
        virtual const Device getDevice(std::string id) = 0;
        virtual std::vector<Device> getAllDevices() = 0;
};

class ILocationRepository : public IRepository{
    public: 
        virtual const Location getLocation(std::string id) = 0;
        virtual std::vector<Location> getAllLocations() = 0;
        virtual bool addLocation(const Location&) = 0;
};