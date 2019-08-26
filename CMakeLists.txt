cmake_minimum_required(VERSION 3.11)

include("cmake/HunterGate.cmake")
HunterGate(
    URL "https://github.com/ruslo/hunter/archive/v0.23.208.tar.gz"
    SHA1 "0c91bb455d37945a71008cd07961ad72a8ba84e2"
)

project(boost-example)

hunter_add_package(Boost COMPONENTS program_options)
find_package(Boost REQUIRED program_options)

add_executable(bex main.cpp)
target_link_libraries(bex PUBLIC Boost::program_options)
target_compile_features(bex PRIVATE cxx_constexpr)
#target_compile_definitions(bex PRIVATE BOOST_CHRONO_VERSION=2)
