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

using bsoncxx::type;
constexpr char kLocationName[] = "Name";
constexpr char kLocationType[] = "Type";

constexpr char kCollectionName[] = "Locations";
constexpr char kMongoDbUri[] = "mongodb://mongodb:27017";
constexpr char kDatabaseName[] = "Device_Registry";

class LocationRepository : public ILocationRepository{
    public:
        LocationRepository()
        : uri(mongocxx::uri(kMongoDbUri)),
          client(mongocxx::client(uri)),
          db(client[kDatabaseName]) 
        {
        }
        
        std::string getName() override {
            return "LocationRepository";
        }

        std::vector<Location> getAllLocations() override{
            std::cout << "getAllLocations" << std::endl;
            std::vector<Location> locationList;
            mongocxx::collection collection = db[kCollectionName];
            mongocxx::cursor cursor = collection.find({});
            
            for (auto&& doc : cursor) {
                bsoncxx::document::element id_ele = doc["_id"];
                bsoncxx::document::element name = doc["Name"];
                bsoncxx::document::element type = doc["Type"];
                if (id_ele.type() == type::k_oid) {
                    std::string oid = id_ele.get_oid().value.to_string();
                    std::cout << "OID: " << oid << 
                                    " curve name: " << name.get_utf8().value <<
                                    " curve type: " << type.get_utf8().value << std::endl;
                    Location loc (oid,std::string(name.get_utf8().value), std::string(type.get_utf8().value));
                    locationList.push_back(loc);
                } else {
                    std::cout << "Error: _id was not an object ID." << std::endl;
                }
            }

            return locationList;
        }

        const Location getLocation(std::string id) override{
            std::cout << "getLocation" << std::endl;
            Location loc("location id","location name","location type");
            
            return loc;
        }

        bool addLocation(const Location& loc) override{
            mongocxx::collection collection = db[kCollectionName];
            auto builder = bsoncxx::builder::stream::document{};
            bsoncxx::v_noabi::document::value doc_value =
                builder << kLocationName << loc.name 
                        << kLocationType << loc.type
                        << bsoncxx::builder::stream::finalize;
            try {
                bsoncxx::stdx::optional<mongocxx::result::insert_one> maybe_result = collection.insert_one(doc_value.view());
                if (maybe_result) {
                    return maybe_result->inserted_id().get_oid().value.to_string().size() != 0;
                }else{
                    std::cout << "Maybe result failed" << std::endl;
                }
            } catch (const std::exception &e) {
                std::cerr << "Exception: " << e.what() << std::endl;
                return false;
            }
            return false;
        }

private:
    mongocxx::uri uri;
    mongocxx::client client;
    mongocxx::database db;
};
