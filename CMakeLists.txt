# --------------------- #
# (C) 2020 madoodia.com #
# --------------------- #

cmake_minimum_required(VERSION 3.3)

# include the project setting file
include($ENV{DEVKIT_LOCATION}/cmake/pluginEntry.cmake)

project($ENV{TARGET_NAME} CXX)

SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# set SOURCE_FILES
set(SOURCE_FILES
    rebuildCurvesPlugin.cpp
    rebuildCurves.cpp
    rebuildGUI.cpp
    logic.cpp
)

# set linking libraries
set(LIBRARIES
    ai
)

include_directories($ENV{MADAPI_LOCATION}/include)
