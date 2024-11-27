#include "DeviceRepository.h"
#include "DeviceService.h"
#include "LocationRepository.h"
#include "LocationService.h"
#include "HttpServer.h"

int main() {
    
    std::shared_ptr<IDeviceRepository> deviceRepository = std::make_shared<DeviceRepository>(); //TODO make unique
    std::shared_ptr<ILocationRepository> locationRepository = std::make_shared<LocationRepository>();

    std::shared_ptr<IDeviceService> deviceService = std::make_shared<DeviceService>(deviceRepository);
    std::shared_ptr<ILocationService> locationService = std::make_shared<LocationService>(locationRepository);

    HttpServer server(locationService,deviceService);
    server.start();
    return 0;
}