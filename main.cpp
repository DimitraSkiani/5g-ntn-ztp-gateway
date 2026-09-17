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

int calculateRiskScore(
    bool identityValid,
    bool tokenValid,
    bool serviceAuthorized,
    bool ntnContextValid)
{
    int riskScore = 0;

    if (!identityValid)
    {
        riskScore += 40;
    }

    if (!tokenValid)
    {
        riskScore += 50;
    }

    if (!serviceAuthorized)
    {
        riskScore += 40;
    }

    if (!ntnContextValid)
    {
        riskScore += 20;
    }

    return riskScore;
}

std::string makeDecision(
    int riskScore,
    bool identityValid,
    bool tokenValid,
    bool serviceAuthorized,
    bool ntnContextValid)
{
    if (!identityValid || !tokenValid || !serviceAuthorized)
    {
        return "DENY";
    }

    if (!ntnContextValid && riskScore < 60)
    {
        return "REQUIRE REAUTHENTICATION";
    }

    if (riskScore >= 60)
    {
        return "DENY";
    }

    return "ALLOW";
}

int main()
{
    AccessRequest request;

    request.ueId = "UE-001";
    request.token = "valid-token-001";
    request.requestedService = "telemetry";
    request.servingGnb = "gNB-01";
    request.satellite = "SAT-01";
    request.location = "Athens";
    request.abnormalMobility = true;

    bool identityValid = validateIdentity(request);
    bool tokenValid = validateToken(request);
    bool serviceAuthorized = isServiceAuthorized(request);
    bool ntnContextValid = validateNtnContext(request);
    int riskScore = calculateRiskScore(
        identityValid,
        tokenValid,
        serviceAuthorized,
        ntnContextValid);
    std::string decision = makeDecision(
        riskScore,
        identityValid,
        tokenValid,
        serviceAuthorized,
        ntnContextValid);

    std::cout << "Zero Trust NTN Gateway" << std::endl;
    std::cout << "UE: " << request.ueId << std::endl;
    std::cout << "Service: " << request.requestedService << std::endl;
    std::cout << "Identity valid: " << identityValid << std::endl;
    std::cout << "Token valid: " << tokenValid << std::endl;
    std::cout << "Service authorized: " << serviceAuthorized << std::endl;
    std::cout << "NTN context valid: " << ntnContextValid << std::endl;
    std::cout << "Risk score: " << riskScore << std::endl;
    std::cout << "Decision: " << decision << std::endl;

    return 0;
}