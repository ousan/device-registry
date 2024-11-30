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

    const StatusCode getAllDevices(std::string& deviceList) const override{
        std::vector<Device> list; 
        StatusCode sc = repo->getAllDevices(list);
        
        if(StatusCode::DEVICE_FOUND == sc){
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
            deviceList = json_obj.dump();
        }

        return sc;
    }

    const StatusCode getDevice(const std::string& id, std::string& device) const override{
        std::cout << "Service getDevice" << std::endl;
        return StatusCode::SUCCESS;
    }
    
private:
    const std::shared_ptr<IDeviceRepository>& repo;
};