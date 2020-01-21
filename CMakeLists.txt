cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.244.tar.gz"
    SHA1 "2c0f491fd0b80f7b09e3d21adb97237161ef9835"
)

project(boost-example)

hunter_add_package(Boost COMPONENTS program_options)
find_package(Boost CONFIG REQUIRED program_options)

add_executable(bex main.cpp)
target_link_libraries(bex PUBLIC Boost::program_options)
target_compile_features(bex PRIVATE cxx_constexpr)
#target_compile_definitions(bex PRIVATE BOOST_CHRONO_VERSION=2)
