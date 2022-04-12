cmake_minimum_required(VERSION 3.16)

project(test_ranges)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(test_ranges main.cpp)

set_target_properties(test_ranges PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
)

target_include_directories(test_ranges PUBLIC ./include PUBLIC ${Boost_INCLUDE})

target_link_libraries(test_ranges
    ${Boost_LIBRARIES}
)



