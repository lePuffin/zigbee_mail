# Set the minimum version of CMake required for this project
cmake_minimum_required(VERSION 3.28)

# Set the project name and version
project(UnitTests VERSION 0.1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Gather all source files from the src directory
file(GLOB SOURCES
    *.cpp
    external_libs/*.cpp
)

# Gather all header files from the src and external_libs directories
file(GLOB HEADERS
    *.hpp
    external_libs/*.hpp
)

# Include directories (add external libraries or other directories here)
include_directories(
    ${CMAKE_SOURCE_DIR}/external_libs
    /usr/include/CppUTest   # Include the path to CppUTest headers
)


# Create an executable from the source files
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link the CppUTest library to the UnitTests executable
target_link_libraries(${PROJECT_NAME} PRIVATE CppUTest)


# Optionally, add installation rules for your project
# install(TARGETS ${PROJECT_NAME} DESTINATION /path/to/install)
