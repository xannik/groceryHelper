cmake_minimum_required(VERSION 3.5.0)
project(shoppinglist VERSION 0.1.0 LANGUAGES C CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Boost REQUIRED COMPONENTS program_options)
find_package(SQLite3 REQUIRED)

# Include directories
include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${SQLite3_INCLUDE_DIRS})

# Add subdirectories
add_subdirectory(src)
add_subdirectory(main)

