#pragma once

#include <string>

#include "models/AccessRequest.h"

void logAccessDecision(
    const AccessRequest &request,
    int riskScore,
    const std::string &decision,
    const std::string &reason);