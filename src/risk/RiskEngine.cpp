#include "risk/RiskEngine.h"

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