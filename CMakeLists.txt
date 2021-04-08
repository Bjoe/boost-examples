cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")
include(CMakePrintHelpers)
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/refs/tags/v0.23.297.tar.gz"
    SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
    LOCAL
)


project(boost-example)

set(Boost_DEBUG ON)

hunter_add_package(Boost COMPONENTS log)
find_package(Boost CONFIG REQUIRED log)

cmake_print_properties(
        TARGETS Boost::log
        PROPERTIES INTERFACE_LINK_LIBRARIES
)

add_executable(bex main.cpp)
target_link_libraries(bex PRIVATE Boost::log)

