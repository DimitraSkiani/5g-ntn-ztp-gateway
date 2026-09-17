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
    std::cout << "Identity valid: " << identityValid << std::endl;
    std::cout << "Token valid: " << tokenValid << std::endl;
    std::cout << "Service authorized: " << serviceAuthorized << std::endl;
    std::cout << "NTN context valid: " << ntnContextValid << std::endl;
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

    processRequest(request);
    processRequest(normalRequest);

    return 0;
}