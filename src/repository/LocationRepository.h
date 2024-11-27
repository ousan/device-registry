#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IRepository.h"
#include "Location.h"

class LocationRepository : public ILocationRepository{
    
    public:
        std::string getName() override {
            return "Device";
        }

        std::vector<Location> getAllLocations(){
            std::cout << "getAllLocations" << std::endl;
            Location loc("location id","location name","location type");
            Location loc2("location-2 id","location-2 name","location-2 type");
            Location loc3("location-3 id","location-3 name","location-3 type");
            std::vector<Location> test{loc,loc2,loc3};
            return test;
        }

        const Location getLocation(std::string id){
            std::cout << "getLocation" << std::endl;
            Location loc("location id","location name","location type");
            
            return loc;
        }


};
