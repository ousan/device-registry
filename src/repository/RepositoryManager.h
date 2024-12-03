#pragma once

#include <cstdint>
#include <string>
#include <iostream>

#include "IRepositoryManager.h"
#include "LocationRepository.h"
#include "DeviceRepository.h"
#include <mongocxx/instance.hpp>

constexpr char kMongoDbUri[] = "mongodb://mongodb:27017";
constexpr char kDatabaseName[] = "Device_Registry";

//This manager is used to handle *Mongo* database queries
class RepositoryManager : public IRepositoryManager{
public:
    public:
    RepositoryManager()
    {
        mongocxx::instance instance;
    }
    void initializeRepositories() override{
        deviceRepository = std::make_shared<DeviceRepository>(std::string(kMongoDbUri),std::string(kDatabaseName));
        locationRepository = std::make_shared<LocationRepository>(std::string(kMongoDbUri),std::string(kDatabaseName));
    }

    std::shared_ptr<IDeviceRepository> getDeviceRepository(){
        return deviceRepository;
    }

    std::shared_ptr<ILocationRepository> getLocationRepository(){
        return locationRepository;
    }
    
private:
   
    std::shared_ptr<IDeviceRepository> deviceRepository; 
    std::shared_ptr<ILocationRepository> locationRepository;
};