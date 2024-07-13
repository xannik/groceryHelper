cmake_minimum_required(VERSION 3.5.0)
project(shoppinglist VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

find_package(SQLite3 REQUIRED)
# Add subdirectories
add_subdirectory(src)
add_subdirectory(main)

