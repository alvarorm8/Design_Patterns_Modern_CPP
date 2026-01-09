# Sources
# https://stackoverflow.com/questions/29191855/what-is-the-proper-way-to-use-pkg-config-from-cmake
# https://stackoverflow.com/questions/44487053/set-pkg-config-path-in-cmake

###############################################################################
## Initial definitions ########################################################
###############################################################################

cmake_minimum_required(VERSION 3.22) # setting this is required
cmake_policy(SET CMP0057 NEW) # Removes warning

# Set project name, version, description and language
project(19_Assignment VERSION 1.0 LANGUAGES CXX)

# Needed for using variables CMAKE_INSTALL_*DIR
include(GNUInstallDirs)

###############################################################################
## Dependencies ###############################################################
###############################################################################

############################ GTest library #########################

find_package(GTest 
            REQUIRED
            PATHS /usr/local/googletest NO_DEFAULT_PATH)

###############################################################################
## Target definitions #########################################################
###############################################################################

# Select source files
set(PROJECT_SOURCE_FILES
    #src/Behavioral.Mediator.MediatorCodingExercise.cpp
    src/exercise.cpp
)

# Create project executable including source files, main in included separately because in the test executable the main can not be added or
# the main definition would collide
add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES})

# Add some compiler flags for the project executable
target_compile_options(${PROJECT_NAME} 
    PUBLIC 
        -std=c++17 
        -Wall 
        -Wfloat-conversion
)

# This allows to include files relative to the root of the src/C++/headers, src/C++/public_headers and dep/C++/src directory with a <> pair
target_include_directories(${PROJECT_NAME} 
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        /usr/local/googletest/include
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC
        GTest::gtest
        GTest::gtest_main
)

add_test(${PROJECT_NAME}Test ${PROJECT_NAME}Test)