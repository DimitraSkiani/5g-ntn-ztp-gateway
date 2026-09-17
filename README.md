# Zero Trust Policy Enforcement Gateway for 5G/6G NTN

Overview 

This project implements a lightweight Zero Trust Policy Enforcement Gateway for simulated access requests from User Equipment (UE) connected through a 5G/6G Non-Terrestrial Network (NTN). 
The gateway evaluates each access request using multiple security and contextual checks and produces one of three decisions:

- ALLOW
- DENY
- REQUIRE REAUTHENTICATION

The implementation is designed as a local simulation and does not require an operational 5G Core, gNB, satellite network, or external authentication infrastructure.

The project is implemented in C++17.
