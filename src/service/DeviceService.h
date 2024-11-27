#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <nlohmann/json.hpp>
#include "IService.h"
#include "Device.h"
#include "DeviceRepository.h"

class DeviceService : public IDeviceService{
public:
    DeviceService(const std::shared_ptr<IDeviceRepository>& _repo)
    :repo(_repo)
    {}

    std::string getName() override{
        return "DeviceService";
    }

    const std::string getAllDevices(){
        std::vector<Device> list = repo->getAllDevices();
        
        nlohmann::json json_obj;
        for(auto device : list){
            nlohmann::json obj;
            obj["name"] = device.name;
            obj["id"] = device.id;
            obj["type"] = device.type;
            obj["serialNumber"] = device.serialNumber;
            obj["location"] = device.location;
            json_obj.push_back(obj);
        }
        return json_obj.dump();
    }

    const std::string getDevice(std::string id){
        std::cout << "Service getDevice" << std::endl;
        return "repo->getDevice(id)";
    }
    
private:
    const std::shared_ptr<IDeviceRepository>& repo;
};