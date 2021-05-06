cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.299.tar.gz"
    SHA1 "3d215b4bfac80824778fe9a93510e5f651d79e3a"
    LOCAL
)

project(boost-example)

find_package(Threads)
#
# See https://hunter.readthedocs.io/en/latest/packages/pkg/Boost.html
#
hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

add_executable(bex main.cpp)
target_link_libraries(bex PUBLIC Boost::headers Threads::Threads)
target_compile_features(bex PRIVATE cxx_constexpr)
#target_compile_definitions(bex PRIVATE BOOST_CHRONO_VERSION=2)
