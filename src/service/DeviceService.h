#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <nlohmann/json.hpp>
#include "IService.h"
#include "Device.h"
#include "DeviceRepository.h"
#include "spdlog/spdlog.h"

class DeviceService : public IDeviceService{
public:
    DeviceService(const std::shared_ptr<IDeviceRepository>& _repo)
    :repo(_repo)
    {}

    std::string getName() override{
        return "DeviceService";
    }

    const nlohmann::json getDeviceJsonObj(const Device& device)const {
        nlohmann::json obj;
        obj["name"] = device.name;
        obj["id"] = device.id;
        obj["type"] = device.type;
        obj["serialNumber"] = device.serialNumber;
        obj["location"] = device.location;
        return obj;
    }

    const StatusCode getAllDevices(std::string& deviceList) const override{
        spdlog::debug("Service - Requested All Devices!");
        std::vector<Device> list; 
        nlohmann::json json_obj;
        StatusCode sc = repo->getAllDevices(list);
                
        if(StatusCode::DEVICE_FOUND == sc){
            for(auto device : list){
                json_obj.push_back(getDeviceJsonObj(device));
            }
        }else{//
            json_obj = StatusCodeHandler::getDescriptionAsJson(sc);
        }
        deviceList = json_obj.dump();
        

        return sc;
    }

    const StatusCode getDevice(const std::string& id, std::string& deviceResponse) const override{
        spdlog::debug("getDevice {}  !", id);
        
        Device device; 
        nlohmann::json json_obj;
        
        StatusCode sc = repo->getDevice(id,device);
        if(StatusCode::DEVICE_FOUND == sc){
            json_obj = getDeviceJsonObj(device);
        }else{
            json_obj = StatusCodeHandler::getDescriptionAsJson(sc);
        }
        deviceResponse = json_obj.dump();
        
        return sc;
    }
    
    const StatusCode addDevice(const std::string& req) override{
        spdlog::debug("addDevice {}  !", req);
        nlohmann::json json_data = nlohmann::json::parse(req);
        Device dev ("", json_data["name"], json_data["type"], json_data["serialnumber"], json_data["location"]);
        return repo->addDevice(dev);
    }

    const StatusCode deleteDevice(const std::string& id) override{
        spdlog::debug("deleteDevice {}  !", id);
        return repo->deleteDevice(id);
    }

private:
    const std::shared_ptr<IDeviceRepository>& repo;
};