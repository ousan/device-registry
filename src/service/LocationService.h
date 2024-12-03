#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IService.h"
#include "Location.h"
#include "LocationRepository.h"
#include <nlohmann/json.hpp>
#include "spdlog/spdlog.h"

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
        spdlog::debug("Service requested all locations!");
        
        std::vector<Location> list ;
        nlohmann::json json_obj;
        
        StatusCode sc = repo->getAllLocations(list);
        if(StatusCode::LOCATION_FOUND == sc){
            for(auto location : list){
                json_obj.push_back(getLocationJsonObj(location));
            }
        }else{
            json_obj = StatusCodeHandler::getDescriptionAsJson(sc);
        }

        response = json_obj.dump();

        return sc;
    }

    const StatusCode getLocation(const std::string& id, std::string& locationResponse) const override{
        spdlog::debug("getLocation {}  !", id);
        
        Location loc; 
        nlohmann::json json_obj;
        
        StatusCode sc = repo->getLocation(id,loc);
        if(StatusCode::LOCATION_FOUND == sc){
            json_obj = getLocationJsonObj(loc);
        }else{
            json_obj = StatusCodeHandler::getDescriptionAsJson(sc);
        }
        locationResponse = json_obj.dump();
        return sc;
    }

    const StatusCode addLocation(const std::string& req) override{
        spdlog::debug("addLocation {}  !", req);
        nlohmann::json json_data = nlohmann::json::parse(req);
        Location loc ("", json_data["name"], json_data["type"]);
        StatusCode sc = repo->addLocation(loc); 
        return sc;
    }
    
    const StatusCode deleteLocation(const std::string& id) override{
        spdlog::debug("deleteLocation {}  !", id);
        return repo->deleteLocation(id);
    }
private:
    const std::shared_ptr<ILocationRepository>& repo;
};