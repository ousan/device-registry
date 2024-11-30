#pragma once

#include <nlohmann/json.hpp>
enum class StatusCode {
    DEVICE_CREATED = 2011,
    LOCATION_CREATED = 2012,
    DATA_FILTERED = 2001,
    NO_RESULTS = 2002,
    DEVICE_DELETED = 2041,
    LOCATION_DELETED = 2042,
    INVALID_DEVICE_TYPE = 4001,
    MISSING_REQUIRED_FIELDS = 4002,
    DEVICE_NOT_FOUND = 4041,
    DEVICE_FOUND = 4042,
    LOCATION_NOT_FOUND = 4043,
    LOCATION_FOUND = 4044,
    LOCATION_NOT_ADDED = 4045,
    DATABASE_CONNECTION_FAILED = 5001,
    DATA_PERSISTENCE_ERROR = 5002,
    UNKNOWN_ERROR = 5003,
    DUPLICATE_SERIAL_NUMBER = 4091,
    LOCATION_IN_USE = 4092,
    INVALID_DATE_RANGE = 4003,
    REQUEST_RECEIVED = 1001,
    PROCESSING = 1002,
    SUCCESS = 1003
};
/*
json generateStatusCodeMap() {
    std::map<StatusCode, std::pair<std::string, std::string>> statusDescriptions = {
        {StatusCode::DEVICE_CREATED, {"DEVICE_CREATED", "The device was successfully created."}},
        {StatusCode::LOCATION_CREATED, {"LOCATION_CREATED", "The location was successfully created."}},
        {StatusCode::DATA_FILTERED, {"DATA_FILTERED", "The data was successfully filtered."}},
        {StatusCode::NO_RESULTS, {"NO_RESULTS", "No results found for the query."}},
        {StatusCode::DEVICE_DELETED, {"DEVICE_DELETED", "The device was successfully deleted."}},
        {StatusCode::LOCATION_DELETED, {"LOCATION_DELETED", "The location was successfully deleted."}},
        {StatusCode::INVALID_DEVICE_TYPE, {"INVALID_DEVICE_TYPE", "The provided device type is invalid."}},
        {StatusCode::MISSING_REQUIRED_FIELDS, {"MISSING_REQUIRED_FIELDS", "Some required fields are missing."}},
        {StatusCode::DEVICE_NOT_FOUND, {"DEVICE_NOT_FOUND", "The specified device was not found."}},
        {StatusCode::LOCATION_NOT_FOUND, {"LOCATION_NOT_FOUND", "The specified location was not found."}},
        {StatusCode::DATABASE_CONNECTION_FAILED, {"DATABASE_CONNECTION_FAILED", "Failed to connect to the database."}},
        {StatusCode::DATA_PERSISTENCE_ERROR, {"DATA_PERSISTENCE_ERROR", "An error occurred while saving data to the database."}},
        {StatusCode::UNKNOWN_ERROR, {"UNKNOWN_ERROR", "An unknown error occurred."}},
        {StatusCode::DUPLICATE_SERIAL_NUMBER, {"DUPLICATE_SERIAL_NUMBER", "A device with the given serial number already exists."}},
        {StatusCode::LOCATION_IN_USE, {"LOCATION_IN_USE", "The location cannot be deleted because it is in use."}},
        {StatusCode::INVALID_DATE_RANGE, {"INVALID_DATE_RANGE", "The provided date range is invalid."}},
        {StatusCode::REQUEST_RECEIVED, {"REQUEST_RECEIVED", "The request has been received and is being processed."}},
        {StatusCode::PROCESSING, {"PROCESSING", "The operation is currently being processed."}}
    };

    json statusCodeJson;
    for (const auto& [code, desc] : statusDescriptions) {
        statusCodeJson["codes"][desc.first] = {
            {"code", static_cast<int>(code)},
            {"message", desc.second}
        };
    }

    return statusCodeJson;
}*/