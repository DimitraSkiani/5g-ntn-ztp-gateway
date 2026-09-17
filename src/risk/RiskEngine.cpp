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
        riskScore += INVALID_IDENTITY_RISK;
    }

    if (!tokenValid)
    {
        riskScore += INVALID_TOKEN_RISK;
    }

    if (!serviceAuthorized)
    {
        riskScore += UNAUTHORIZED_SERVICE_RISK;
    }

    if (!ntnContextValid)
    {
        riskScore += INVALID_NTN_CONTEXT_RISK;
    }

    return riskScore;
}