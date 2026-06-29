cmake_minimum_required(VERSION 3.25)
project(xpam-client VERSION 0.0.0.1 LANGUAGES CXX)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Windows-only validation
if(NOT WIN32)
    message(FATAL_ERROR "This project is Windows-only")
endif()

if(NOT MSVC)
    message(FATAL_ERROR "This project requires MSVC compiler")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR "This project requires x64 architecture")
endif()

# Qt settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt6
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Network
    WebEngineWidgets
    Widgets
)

# Find vcpkg packages
find_package(ZLIB REQUIRED)
find_package(BZip2 REQUIRED)
find_package(Boost REQUIRED COMPONENTS system)
find_package(QuaZip-Qt6 REQUIRED)
find_package(LibtorrentRasterbar REQUIRED)
find_package(StormLib CONFIG REQUIRED)

# Add application subdirectory
add_subdirectory(xpam)
