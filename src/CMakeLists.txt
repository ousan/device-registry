cmake_minimum_required(VERSION 3.14...3.31)
project(device-registry)

add_subdirectory(cpp-httplib)
add_subdirectory(json)

include_directories("/usr/local/include/mongocxx/v_noabi")
include_directories("/usr/local/include/bsoncxx/v_noabi")
include_directories("/usr/local/include/libmongoc-1.0")
include_directories("/usr/local/include/libbson-1.0")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/controller)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/repository)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/service)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/model)

#set(HEADERS
#   ${HEADERS}
#   ${CMAKE_CURRENT_SOURCE_DIR}/controller/HttpServer.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/service/IService.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/service/DeviceService.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/service/LocationService.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/repository/IRepository.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/repository/DeviceRepository.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/repository/LocationRepository.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/model/Device.h
#   ${CMAKE_CURRENT_SOURCE_DIR}/model/Location.h
#)

add_executable(device-registry device-registry.cpp)

target_link_libraries(device-registry mongocxx bsoncxx httplib::httplib nlohmann_json::nlohmann_json)
