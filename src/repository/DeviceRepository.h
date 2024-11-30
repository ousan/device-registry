#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IRepository.h"
#include "Device.h"

class DeviceRepository : public IDeviceRepository{
    
public:
    std::string getName() override {
        return "Device";
    }
    
    const StatusCode getAllDevices(std::vector<Device>& dList) const override{
        std::cout << "getAllDevices" << std::endl;
  
        Device test("device id ","device name","device type","device serialnumber","device location");
        dList.push_back(test);
        
        Device test2("device-2 id ","device-2 name","device-2 type","device-2 serialnumber","device-2 location");
        dList.push_back(test2);
        
        Device test3("device-3 id ","device-3 name","device-3 type","device-3 serialnumber","device-3 location");
        dList.push_back(test3);
        
        return StatusCode::DEVICE_FOUND;
    }

    const StatusCode getDevice(const std::string& id, Device& device) const override{
        std::cout << "getDevice" << std::endl;
        
        Device test("device id ","device name","device type","device serialnumber","device serialnumber");
        device = test;
        return StatusCode::DEVICE_FOUND;
    }
};
