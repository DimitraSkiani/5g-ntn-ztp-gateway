#pragma once

constexpr int INVALID_IDENTITY_RISK = 40;
constexpr int INVALID_TOKEN_RISK = 50;
constexpr int UNAUTHORIZED_SERVICE_RISK = 40;
constexpr int INVALID_NTN_CONTEXT_RISK = 20;

int calculateRiskScore(
    bool identityValid,
    bool tokenValid,
    bool serviceAuthorized,
    bool ntnContextValid);