#include <iostream>
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

bool validateIdentity(const AccessRequest &request)
{
    return request.ueId == "UE-001";
}

int main()
{
    AccessRequest request;

    request.ueId = "UE-001";
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