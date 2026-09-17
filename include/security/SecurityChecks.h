#pragma once

#include "models/AccessRequest.h"

bool validateIdentity(const AccessRequest &request);

bool validateToken(const AccessRequest &request);

bool isServiceAuthorized(const AccessRequest &request);

bool validateNtnContext(const AccessRequest &request);