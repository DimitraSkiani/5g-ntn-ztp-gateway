#include "logging/AuditLogger.h"

#include <iostream>

void logAccessDecision(
    const AccessRequest &request,
    int riskScore,
    const std::string &decision,
    const std::string &reason)
{
    std::cout << "AUDIT LOG" << std::endl;

    std::cout << "UE=" << request.ueId
              << " SERVICE=" << request.requestedService
              << " RISK=" << riskScore
              << " DECISION=" << decision
              << " REASON=" << reason
              << std::endl;
}