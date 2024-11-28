#pragma once

#include "httplib.h"

#include "LocationService.h"
#include "DeviceService.h"


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
        server.Get("/hi", [](const httplib::Request & /*req*/, httplib::Response &res) {
            res.set_content("Hello World!", "application/json");
        });
        server.Get("/devices", [&](const httplib::Request & /*req*/, httplib::Response &res) {
            std::string response = deviceService->getAllDevices();
            res.set_content(response, "application/json");
        });
    
        server.Get("/locations", [&](const httplib::Request & /*req*/, httplib::Response &res) {
            std::string response = locationService->getAllLocations();
            res.set_content(response, "application/json");
        });

        server.Post("/location", [&](const httplib::Request & req, httplib::Response &res) {
            auto result = _locationService->addLocation(req.body);
            res.status = result ?  httplib::StatusCode::OK_200 : httplib::StatusCode::Unauthorized_401;
            res.set_content("Completed", "text/plain");
        });
    
    }
    
    void start()
    {
        server.listen(ipAddress,port);
    }
    
    private:
        httplib::Server server;
        const std::shared_ptr<ILocationService>& locationService;
        const std::shared_ptr<IDeviceService>& deviceService;
};
