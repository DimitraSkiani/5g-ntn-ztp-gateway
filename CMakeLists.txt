cmake_minimum_required(VERSION 3.20)

project(g_ntn_ztp_gateway
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(gateway
    main.cpp
)