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
        
        std::vector<Device> getAllDevices(){
            std::cout << "getAllDevices" << std::endl;
            Location loc("1","2","3");
            Device test("device id ","device name","device type","device serialnumber","device serialnumber");
            Device test2("device-2 id ","device-2 name","device-2 type","device-2 serialnumber","device serialnumber");
            Device test3("device-3 id ","device-3 name","device-3 type","device-3 serialnumber","device serialnumber");
            std::vector<Device> dList{test,test2,test3};
            return dList;
        }

        const Device getDevice(std::string id){
            std::cout << "getDevice" << std::endl;
            
            Device test("device id ","device name","device type","device serialnumber","device serialnumber");
            return test;
        }


};
