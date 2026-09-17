#pragma once

#include <string>
constexpr int DENY_RISK_THRESHOLD = 60;

std::string makeDecision(
    int riskScore,
    bool identityValid,
    bool tokenValid,
    bool serviceAuthorized,
    bool ntnContextValid);

std::string getDecisionReason(
    bool identityValid,
    bool tokenValid,
    bool serviceAuthorized,
    bool ntnContextValid);