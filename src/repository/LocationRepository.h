#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "IRepository.h"
#include "Location.h"
#include "bsoncxx/builder/stream/document.hpp"
#include "bsoncxx/json.hpp"
#include "bsoncxx/oid.hpp"
#include "mongocxx/client.hpp"
#include "mongocxx/database.hpp"
#include "mongocxx/uri.hpp"
#include <mongocxx/instance.hpp>
#include "spdlog/spdlog.h"

using bsoncxx::type;
constexpr char kLocationName[] = "Name";
constexpr char kLocationType[] = "Type";

constexpr char kLocationCollectionName[] = "Locations";
//constexpr char kMongoDbUri[] = "mongodb://mongodb:27017";
//constexpr char kDatabaseName[] = "Device_Registry";

class LocationRepository : public ILocationRepository{
public:
    LocationRepository(const std::string& kMongoDbUri, const std::string& kDatabaseName)
    : uri(mongocxx::uri(kMongoDbUri)),
        client(mongocxx::client(uri)),
        db(client[kDatabaseName]) 
    {
    }
    
    std::string getName() override {
        return "LocationRepository";
    }

    const StatusCode getAllLocations(std::vector<Location>& dList) const override{
        mongocxx::collection collection = db[kLocationCollectionName];
        mongocxx::cursor cursor = collection.find({});
        StatusCode sc = StatusCode::LOCATION_NOT_FOUND;
        for (auto&& doc : cursor) {
            bsoncxx::document::element id_ele = doc["_id"];
            bsoncxx::document::element name = doc["Name"];
            bsoncxx::document::element type = doc["Type"];
            if (id_ele.type() == type::k_oid) {
                std::string oid = id_ele.get_oid().value.to_string();
                spdlog::debug("OID: {} Curve Name: {} Curve Type:{}", oid, name.get_utf8().value, type.get_utf8().value);
                Location loc (oid,std::string(name.get_utf8().value), std::string(type.get_utf8().value));
                dList.push_back(loc);
            } else {
                spdlog::error("Error: _id was not an object ID");
            }
        }

        return sc;
    }

    const StatusCode getLocation(const std::string& id, Location& location) const override{
        std::cout << "getLocation" << std::endl;
        Location loc("test location id","location name","location type");
        location = loc;
        return StatusCode::LOCATION_FOUND;
    }

    const StatusCode addLocation(Location& loc) override{
        mongocxx::collection collection = db[kLocationCollectionName];
        auto builder = bsoncxx::builder::stream::document{};
        bsoncxx::v_noabi::document::value doc_value =
            builder << kLocationName << loc.name 
                    << kLocationType << loc.type
                    << bsoncxx::builder::stream::finalize;
        try {
            bsoncxx::stdx::optional<mongocxx::result::insert_one> maybe_result = collection.insert_one(doc_value.view());
            if (maybe_result) {
                bool res = maybe_result->inserted_id().get_oid().value.to_string().size() != 0;

                return res ? StatusCode::LOCATION_CREATED : StatusCode::LOCATION_NOT_CREATED;
            }else{
                std::cout << "Maybe result failed" << std::endl;
                return StatusCode::LOCATION_NOT_CREATED;
            }
        } catch (const std::exception &e) {
            std::cerr << "Exception: " << e.what() << std::endl;
            return StatusCode::LOCATION_NOT_CREATED;
        }
        return StatusCode::LOCATION_NOT_CREATED;;
    }

    const StatusCode deleteLocation(const std::string& id) override{
        spdlog::debug("DeleteLocation {}  !", id);
        return StatusCode::LOCATION_DELETED;
    }
private:
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
};
