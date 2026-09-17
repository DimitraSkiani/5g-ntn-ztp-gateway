#pragma once

#include <string>

struct AccessRequest
{
    std::string ueId;
    std::string token;
    std::string requestedService;
    std::string servingGnb;
    std::string satellite;
    std::string location;
    bool abnormalMobility;
};