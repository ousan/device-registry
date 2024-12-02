cmake_minimum_required(VERSION 3.14...3.31)
project(device-registry)

add_subdirectory(3rd-party/cpp-httplib)
add_subdirectory(3rd-party/json)
add_subdirectory(3rd-party/spdlog)

include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/controller)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/repository)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/service)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/model)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/utils)

add_executable(device-registry device-registry.cpp)

target_link_libraries(device-registry mongocxx bsoncxx httplib::httplib nlohmann_json::nlohmann_json spdlog::spdlog_header_only)
