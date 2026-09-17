# Zero Trust Policy Enforcement Gateway for 5G/6G NTN

 ## Overview 

This project implements a lightweight Zero Trust Policy Enforcement Gateway for simulated access requests from User Equipment (UE) connected through a 5G/6G Non-Terrestrial Network (NTN). 
The gateway evaluates each access request using multiple security and contextual checks and produces one of three decisions:

- ALLOW
- DENY
- REQUIRE REAUTHENTICATION

The implementation is designed as a local simulation and does not require an operational 5G Core, gNB, satellite network, or external authentication infrastructure.

The project is implemented in C++17.


## Architecture

The gateway follows a simple Zero Trust request evaluation flow:


The gateway acts as the Policy Enforcement Point (PEP). The access decision is based on the results of the security checks and the calculated risk score.


## Project Structure

```text
5g-ntn-ztp-gateway/
├── include/
│   ├── models/
│   │   └── AccessRequest.h
│   ├── security/
│   │   └── SecurityChecks.h
│   ├── risk/
│   │   └── RiskEngine.h
│   ├── decision/
│   │   └── DecisionEngine.h
│   └── logging/
│       └── AuditLogger.h
├── src/
│   ├── security/
│   │   └── SecurityChecks.cpp
│   ├── risk/
│   │   └── RiskEngine.cpp
│   ├── decision/
│   │   └── DecisionEngine.cpp
│   └── logging/
│       └── AuditLogger.cpp
├── main.cpp
├── CMakeLists.txt
└── README.md
```


## Components

### Access Request Model

`AccessRequest` represents a simulated access request from a UE.

The request contains:

* UE identity
* token
* requested service
* serving gNB
* satellite
* location
* abnormal mobility indicator

### Security Checks

The security module performs four checks:

1. UE identity validation
2. Token validation
3. Service authorization
4. NTN context validation

The current implementation uses simulated identities and tokens because the assignment does not require integration with a real authentication infrastructure.

### Risk Engine

The Risk Engine calculates a simple dynamic risk score based on failed security checks.

### Decision Engine

The Decision Engine combines the individual validation results with the risk score and produces the final access decision.

### Audit Logger

The Audit Logger records the main information associated with each access decision:

* UE identity
* requested service
* risk score
* decision
* reason for the decision

---

## Zero Trust Decision Flow

For every access request, the gateway performs the following steps:

1. Validate the UE identity.
2. Validate the provided token.
3. Check whether the UE is authorized to access the requested service.
4. Validate the NTN context.
5. Calculate a risk score based on failed checks.
6. Produce an access decision.
7. Record the decision in the audit log.

The gateway does not automatically trust a request based only on the UE identity or token. Multiple attributes are evaluated before access is granted.


## Risk Scoring

The implementation uses the following risk weights:

| Condition            | Risk |
| -------------------- | ---: |
| Invalid UE identity  |  +40 |
| Invalid token        |  +50 |
| Unauthorized service |  +40 |
| Invalid NTN context  |  +20 |

The total risk score is calculated by adding the applicable risk values.

The decision logic is:

* Invalid identity, invalid token, or unauthorized service → `DENY`
* Invalid NTN context with risk below `60` → `REQUIRE REAUTHENTICATION`
* Risk score greater than or equal to `60` → `DENY`
* Otherwise → `ALLOW`

This provides a simple dynamic risk-based decision mechanism while keeping the implementation lightweight.


## NTN Context

The gateway considers contextual information specific to an NTN environment.

The simulated request contains:

* Serving gNB
* Serving satellite
* UE location
* Abnormal mobility indicator

A request is considered to have a valid NTN context when the expected serving gNB, satellite, and location are present and abnormal mobility is not detected.

An abnormal mobility condition is treated as a contextual risk rather than automatically denying the request. In the current implementation, this results in `REQUIRE REAUTHENTICATION` when no other high-risk condition is present.


## Design Decisions

### Lightweight local simulation

The assignment does not require integration with a real 5G Core, gNB, satellite, or external authentication system. Therefore, the implementation uses simulated access requests and local validation logic.


### Risk-based decisions

The gateway does not rely only on a binary allow/deny policy. Contextual risk is incorporated into the decision through a simple scoring mechanism.

### Simulated credentials

UE identities and tokens are represented by predefined test values. A production implementation would integrate with an appropriate identity and token validation system and use standard cryptographic mechanisms rather than implementing cryptography manually.


## Assumptions

The following assumptions are made for the prototype:

* UE identities are represented by predefined identifiers.
* Tokens are simulated predefined values.
* Service authorization policies are locally defined.
* NTN information is provided directly as part of the simulated request.
* Location is represented as a simple string for demonstration purposes.
* Abnormal mobility is represented by a boolean value.
* The gateway runs locally as a standalone C++ application.
* No real network communication is required.


## Build and Run

### Requirements

* C++17-compatible compiler
* CMake 3.20 or later

### Build

From the project root:

```bash
cmake -S . -B build -G "MinGW Makefiles"
cmake --build build
```

### Run

On Windows:

```powershell
.\build\gateway.exe
```

The application processes several simulated access requests and prints the security checks, risk score, decision, and audit log.


## Test Scenarios

The application includes the following test scenarios:

| Scenario                             | Expected Decision        |
| ------------------------------------ | ------------------------ |
| Valid request with abnormal mobility | REQUIRE REAUTHENTICATION |
| Valid request with normal context    | ALLOW                    |
| Invalid token                        | DENY                     |
| Unauthorized service                 | DENY                     |
| Invalid UE identity                  | DENY                     |

Example output:

```text
AUDIT LOG
UE=UE-001 SERVICE=telemetry RISK=20 DECISION=REQUIRE REAUTHENTICATION REASON=Abnormal NTN context

AUDIT LOG
UE=UE-001 SERVICE=telemetry RISK=0 DECISION=ALLOW REASON=All security checks passed

AUDIT LOG
UE=UE-001 SERVICE=telemetry RISK=50 DECISION=DENY REASON=Invalid token

AUDIT LOG
UE=UE-001 SERVICE=admin RISK=40 DECISION=DENY REASON=Unauthorized service

AUDIT LOG
UE=UE-999 SERVICE=telemetry RISK=80 DECISION=DENY REASON=Invalid UE identity
```

