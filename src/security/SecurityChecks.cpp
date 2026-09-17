#include "security/SecurityChecks.h"

#include <vector>
#include <string>

bool validateIdentity(const AccessRequest &request)
{
    std::vector<std::string> knownUes = {
        "UE-001",
        "UE-002",
        "UE-003"};

    for (const std::string &ue : knownUes)
    {
        if (ue == request.ueId)
        {
            return true;
        }
    }

    return false;
}

bool validateToken(const AccessRequest &request)
{
    std::vector<std::string> validTokens = {
        "valid-token-001",
        "valid-token-002",
        "valid-token-003"};

    for (const std::string &token : validTokens)
    {
        if (token == request.token)
        {
            return true;
        }
    }

    return false;
}

bool isServiceAuthorized(const AccessRequest &request)
{
    if (request.ueId == "UE-001" &&
        request.requestedService == "telemetry")
    {
        return true;
    }

    if (request.ueId == "UE-001" &&
        request.requestedService == "diagnostics")
    {
        return true;
    }

    if (request.ueId == "UE-002" &&
        request.requestedService == "telemetry")
    {
        return true;
    }

    return false;
}

bool validateNtnContext(const AccessRequest &request)
{
    if (request.servingGnb != "gNB-01")
    {
        return false;
    }

    if (request.satellite != "SAT-01")
    {
        return false;
    }

    if (request.location != "Athens")
    {
        return false;
    }

    if (request.abnormalMobility)
    {
        return false;
    }

    return true;
}