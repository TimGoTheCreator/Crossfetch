cmake_minimum_required(VERSION 3.10)

# Project metadata
project(Crossfetch VERSION 0.2 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(crossfetch
    main.cpp
)

# Installation rules
install(TARGETS crossfetch DESTINATION bin)
