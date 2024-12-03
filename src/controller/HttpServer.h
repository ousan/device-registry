#pragma once

#include "httplib.h"

#include "LocationService.h"
#include "DeviceService.h"
#include "StatusCode.h"
#include "spdlog/spdlog.h"

constexpr char deviceEndpoint[] = "/devices";
constexpr char locationEndpoint[] = "/location";

constexpr char ipAddress[] = "0.0.0.0";
constexpr int port = 8085;

class HttpServer{
    public:
    HttpServer(const std::shared_ptr<ILocationService>& _locationService,
               const std::shared_ptr<IDeviceService>& _deviceService)
                :locationService(_locationService), deviceService(_deviceService)
    {
        

        server.Get("/devices", [&](const httplib::Request & /*req*/, httplib::Response &res) {
            spdlog::debug("Requested All Devices!");
            
            std::string response;
            res.status = 200; 
            StatusCode sc = deviceService->getAllDevices(response);
            spdlog::debug("Http Response {} !", response);
            if(StatusCode::DEVICE_FOUND != sc){
                res.status = 404;
            }
            res.set_content(response, "application/json");
        });
    
        server.Get("/locations", [&](const httplib::Request & /*req*/, httplib::Response &res) {
            spdlog::debug("Requested All Locations!");
            std::string response;
            res.status = 200; 
            StatusCode sc = locationService->getAllLocations(response);
            spdlog::debug("Http Response {} !", response);
            if(sc != StatusCode::LOCATION_FOUND){
                res.status = 404;
            }
            res.set_content(response, "application/json");
        });

        server.Post("/location", [&](const httplib::Request & req, httplib::Response &res) {
            auto sc = _locationService->addLocation(req.body);
            res.status = 200; 
            if(sc != StatusCode::LOCATION_NOT_CREATED){
                res.status = 400;
                res.set_content("Not Completed", "text/plain");
                return;
            }
            res.set_content("Completed", "text/plain");
        });

        server.Get("/location", [&](const httplib::Request & req, httplib::Response &res) {
            
            std::string error_message;
            if (!validateQueryParams(location_expected_params,req.params,error_message)) {
                 res.status = 400;  // Bad Request
                 res.set_content(error_message, "text/plain");
                 return;  
            }
            std::string response;
            auto sc = locationService->getLocation("req.params",response);
            if(sc != StatusCode::LOCATION_NOT_FOUND){
                res.status = 404;               
                res.set_content(response, "application/json");
                return;
            }
            res.set_content("Completed", "text/plain");
        });
    }
    
    void start()
    {
        server.listen(ipAddress,port);
    }
    
    // Function to validate query parameters
    bool validateQueryParams(const std::unordered_map<std::string, std::regex>& expected_params, 
                         const httplib::Params &params, 
                         std::string &error_message) {
        
        for (const auto &[key, value] : params) {
            auto it = expected_params.find(key);
            if (it == expected_params.end()) {
                error_message = "Invalid key: " + key;
                return false;
            }
            if(!std::regex_match(value, it->second)){
                error_message = "Invalid value for parameter: " + key;
                return false;
            }

            
        }
        return true;
    }

    private:
        httplib::Server server;
        const std::shared_ptr<ILocationService>& locationService;
        const std::shared_ptr<IDeviceService>& deviceService;
        std::unordered_map<std::string, std::regex> location_expected_params = {
            {"id", std::regex(R"(^[a-zA-Z0-9]+$)" )},     // id must be alphanumeric
            {"name", std::regex(R"(^[a-zA-Z0-9]+$)" )},   // name must be alphanumeric
            {"type", std::regex(R"(^[a-zA-Z0-9]+$)" )}    // type must be alphanumeric
        };

        std::unordered_map<std::string, std::regex> device_expected_params = {
            {"id", std::regex(R"(^[a-zA-Z0-9]+$)" )},     // id must be alphanumeric
            {"name", std::regex(R"(^[a-zA-Z0-9]+$)" )},   // name must be alphanumeric
            {"type", std::regex(R"(^[a-zA-Z0-9]+$)" )},    // type must be alphanumeric
            {"sn", std::regex(R"(^[a-zA-Z0-9]+$)" )}      // sn must be alphanumeric
        };
};
