#pragma once

#include <cstdint>
#include <string>
#include <iostream>

#include "IRepositoryManager.h"
#include "LocationRepository.h"
#include "DeviceRepository.h"

//This manager is used to handle *Mongo* database queries
class RepositoryManager : public IRepositoryManager{
public:
    
    void initializeRepositories() override{
        //deviceRepository = std::make_shared<DeviceRepository>(uri,client,db);
        locationRepository = std::make_shared<LocationRepository>();
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