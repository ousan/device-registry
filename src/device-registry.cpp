#include "DeviceRepository.h"
#include "DeviceService.h"
#include "LocationRepository.h"
#include "LocationService.h"
#include "HttpServer.h"
#include "RepositoryManager.h"
#include <mongocxx/instance.hpp>



int main() {
    mongocxx::instance instance;
    
    std::shared_ptr<IRepositoryManager> rm = std::make_shared<RepositoryManager>();
    rm->initializeRepositories();
    
    std::shared_ptr<IDeviceRepository> deviceRepository = rm->getDeviceRepository();
    std::shared_ptr<IDeviceService> deviceService = std::make_shared<DeviceService>(deviceRepository);
    

    std::shared_ptr<ILocationRepository> locationRepository = rm->getLocationRepository();
    std::shared_ptr<ILocationService> locationService = std::make_shared<LocationService>(locationRepository);
    

    HttpServer server(locationService,deviceService);
    server.start();
    return 0;
}