#pragma once

int calculateRiskScore(
    bool identityValid,
    bool tokenValid,
    bool serviceAuthorized,
    bool ntnContextValid);