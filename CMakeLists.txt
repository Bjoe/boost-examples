cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.110.tar.gz"
    SHA1 "5524a56456bee0dbb653da3f5a192292cd135840"
)

project(boost-example)

find_package(Threads)

hunter_add_package(Boost)
find_package(Boost 1.69 REQUIRED)

add_executable(bex main.cpp)
target_link_libraries(bex Threads::Threads)
target_compile_features(bex PRIVATE cxx_constexpr)
#target_compile_definitions(bex PRIVATE BOOST_CHRONO_VERSION=2)
