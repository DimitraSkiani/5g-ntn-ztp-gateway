#include <iostream>
#include <string>
#include <vector>
#include "models/AccessRequest.h"
#include "security/SecurityChecks.h"
#include "risk/RiskEngine.h"
#include "decision/DecisionEngine.h"
#include "logging/AuditLogger.h"

void processRequest(const AccessRequest &request)
{
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

    std::string reason = getDecisionReason(
        identityValid,
        tokenValid,
        serviceAuthorized,
        ntnContextValid);

    logAccessDecision(
        request,
        riskScore,
        decision,
        reason);

    std::cout << "Zero Trust NTN Gateway" << std::endl;
    std::cout << "UE: " << request.ueId << std::endl;
    std::cout << "Service: " << request.requestedService << std::endl;
    std::cout << "Identity valid: " << (identityValid ? "YES" : "NO") << std::endl;
    std::cout << "Token valid: " << (tokenValid ? "YES" : "NO") << std::endl;
    std::cout << "Service authorized: " << (serviceAuthorized ? "YES" : "NO") << std::endl;
    std::cout << "NTN context valid: " << (ntnContextValid ? "YES" : "NO") << std::endl;
    std::cout << "Risk score: " << riskScore << std::endl;
    std::cout << "Decision: " << decision << std::endl;
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

    AccessRequest normalRequest;

    normalRequest.ueId = "UE-001";
    normalRequest.token = "valid-token-001";
    normalRequest.requestedService = "telemetry";
    normalRequest.servingGnb = "gNB-01";
    normalRequest.satellite = "SAT-01";
    normalRequest.location = "Athens";
    normalRequest.abnormalMobility = false;

    AccessRequest invalidTokenRequest;

    invalidTokenRequest.ueId = "UE-001";
    invalidTokenRequest.token = "invalid-token";
    invalidTokenRequest.requestedService = "telemetry";
    invalidTokenRequest.servingGnb = "gNB-01";
    invalidTokenRequest.satellite = "SAT-01";
    invalidTokenRequest.location = "Athens";
    invalidTokenRequest.abnormalMobility = false;

    AccessRequest unauthorizedServiceRequest;

    unauthorizedServiceRequest.ueId = "UE-001";
    unauthorizedServiceRequest.token = "valid-token-001";
    unauthorizedServiceRequest.requestedService = "admin";
    unauthorizedServiceRequest.servingGnb = "gNB-01";
    unauthorizedServiceRequest.satellite = "SAT-01";
    unauthorizedServiceRequest.location = "Athens";
    unauthorizedServiceRequest.abnormalMobility = false;

    AccessRequest invalidIdentityRequest;

    invalidIdentityRequest.ueId = "UE-999";
    invalidIdentityRequest.token = "valid-token-001";
    invalidIdentityRequest.requestedService = "telemetry";
    invalidIdentityRequest.servingGnb = "gNB-01";
    invalidIdentityRequest.satellite = "SAT-01";
    invalidIdentityRequest.location = "Athens";
    invalidIdentityRequest.abnormalMobility = false;

    processRequest(request);
    processRequest(normalRequest);
    processRequest(invalidTokenRequest);
    processRequest(unauthorizedServiceRequest);
    processRequest(invalidIdentityRequest);

    return 0;
}