#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IService.h"
#include "Location.h"
#include "LocationRepository.h"
#include <nlohmann/json.hpp>

class LocationService : public ILocationService{
public:
    LocationService(const std::shared_ptr<ILocationRepository>& _repo)
    :repo(_repo)
    {}

    std::string getName() override{
        return "LocationService";
    }

    const nlohmann::json getLocationJsonObj(const Location& loc)const {
        nlohmann::json obj;
        obj["name"] = loc.name;
        obj["id"] = loc.id;
        obj["type"] = loc.type;
        return obj;
    }

    const StatusCode getAllLocations(std::string& response) const override{
        std::cout << "Service getAllLocations" << std::endl;
        std::vector<Location> list ;
        StatusCode sc = repo->getAllLocations(list);
        if(StatusCode::LOCATION_FOUND == sc){
            nlohmann::json json_obj;
            for(auto location : list){
                json_obj.push_back(getLocationJsonObj(location));
            }
            response = json_obj.dump();
        }

        return sc;
    }

    const StatusCode getLocation(const std::string& id, std::string& locationResponse) const override{
        std::cout << "Service getLocation" << std::endl;
        Location loc; 
        StatusCode sc = repo->getLocation(id,loc);
        if(StatusCode::LOCATION_FOUND == sc)
            locationResponse = getLocationJsonObj(loc).dump();
        return sc;
    }

    const StatusCode addLocation(const std::string& req) override{
        std::cout <<"addLocation" << std::endl;
        nlohmann::json json_data = nlohmann::json::parse(req);
        Location loc ("", json_data["name"], json_data["type"]);
        StatusCode sc = repo->addLocation(loc); 
        return sc;
    }
    
private:
    const std::shared_ptr<ILocationRepository>& repo;
};