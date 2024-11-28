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

    const std::string getAllLocations() override{
        std::vector<Location> list = repo->getAllLocations();
        
        nlohmann::json json_obj;
        for(auto location : list){
            nlohmann::json obj;
            obj["name"] = location.name;
            obj["id"] = location.id;
            obj["type"] = location.type;
            json_obj.push_back(obj);
        }
        return json_obj.dump();
    }

    const std::string getLocation(std::string id) override{
        std::cout << "Service getLocation" << std::endl;
        return "repo->getLocation(id);";
    }

    bool addLocation(const std::string& req) override{
        nlohmann::json json_data = nlohmann::json::parse(req);
        //std::cout << data.dump(4) << std::endl;
        std::cout <<"Add Location Req :" << req << std::endl;
        Location loc ("", json_data["name"], json_data["type"]);
        return repo->addLocation(loc);
    }
    
private:
    const std::shared_ptr<ILocationRepository>& repo;
};