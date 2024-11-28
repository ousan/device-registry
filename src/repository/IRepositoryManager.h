#pragma once

class IRepositoryManager{
    public:
    virtual void initializeRepositories() = 0;
    virtual std::shared_ptr<IDeviceRepository> getDeviceRepository() = 0;
    virtual std::shared_ptr<ILocationRepository> getLocationRepository() = 0;
};