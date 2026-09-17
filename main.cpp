#include <iostream>
#include <string>
#include <vector>

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

int main()
{
    AccessRequest request;

    request.ueId = "UE-999";
    request.token = "valid-token";
    request.requestedService = "telemetry";
    request.servingGnb = "gNB-01";
    request.satellite = "SAT-01";
    request.location = "Athens";
    request.abnormalMobility = false;

    bool identityValid = validateIdentity(request);

    std::cout << "Zero Trust NTN Gateway" << std::endl;
    std::cout << "UE: " << request.ueId << std::endl;
    std::cout << "Service: " << request.requestedService << std::endl;
    std::cout << "Identity valid: " << identityValid << std::endl;

    return 0;
}