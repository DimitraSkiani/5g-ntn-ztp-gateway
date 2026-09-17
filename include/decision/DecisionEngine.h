#pragma once

#include <string>

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