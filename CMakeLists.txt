cmake_minimum_required(VERSION 3.14...3.31)
project(device-registry)

add_subdirectory(cpp-httplib)
add_subdirectory(json)

include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")

add_executable(device-registry device-registry.cpp)

target_link_libraries(device-registry mongocxx bsoncxx httplib::httplib nlohmann_json::nlohmann_json)
