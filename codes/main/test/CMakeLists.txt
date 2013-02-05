cmake_minimum_required(VERSION 2.8)

include(CheckFunctionExists)
include(CheckCXXSourceCompiles)
include(CheckLibraryExists)
include(CPack)
enable_testing()

set(PROJECT_INCLUDE_DIR ../include)

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)
set(CMAKE_BUILD_TYPE Debug)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/test CPP_LIST)
find_package(Boost COMPONENTS system filesystem thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR} ${PROJECT_INCLUDE_DIR})

add_executable(util_test ${CPP_LIST})
target_link_libraries(util_test ${Boost_LIBRARIES} booster)
add_test(name util_test command util_test)



