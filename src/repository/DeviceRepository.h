#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IRepository.h"
#include "Device.h"
#include "spdlog/spdlog.h"

#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/oid.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/database.hpp"
#include "mongocxx/uri.hpp"
#include <mongocxx/instance.hpp>

constexpr char kDeviceCollectionName[] = "Devices";
//constexpr char kMongoDbUri[] = "mongodb://mongodb:27017";
//constexpr char kDatabaseName[] = "Device_Registry";

class DeviceRepository : public IDeviceRepository{
public:
    DeviceRepository(const std::string& kMongoDbUri, const std::string& kDatabaseName)
    :uri(mongocxx::uri(kMongoDbUri)),
        client(mongocxx::client(uri)),
        db(client[kDatabaseName]) 
        {
        }

    std::string getName() override {
        return "Device";
    }
    
    const StatusCode getAllDevices(std::vector<Device>& dList) const override{
          
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
    
    const StatusCode deleteDevice(const std::string& id) override{
        spdlog::debug("DeleteDevice {}  !", id);
        return StatusCode::DEVICE_DELETED;
    }

    const StatusCode addDevice(Device& device){
        spdlog::debug("addDevice {}  !", device.name);
        return StatusCode::DEVICE_CREATED;
    }
private:
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
};
