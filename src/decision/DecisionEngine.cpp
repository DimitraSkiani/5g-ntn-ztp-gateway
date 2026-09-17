#include "decision/DecisionEngine.h"

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

std::string getDecisionReason(
    bool identityValid,
    bool tokenValid,
    bool serviceAuthorized,
    bool ntnContextValid)
{
    if (!identityValid)
    {
        return "Invalid UE identity";
    }

    if (!tokenValid)
    {
        return "Invalid token";
    }

    if (!serviceAuthorized)
    {
        return "Unauthorized service";
    }

    if (!ntnContextValid)
    {
        return "Abnormal NTN context";
    }

    return "All security checks passed";
}