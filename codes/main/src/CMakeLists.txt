cmake_minimum_required(VERSION 2.8)
set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_INCLUDE_DIR ../include)

find_package(Boost COMPONENTS system filesystem thread REQUIRED)
include_directories(${Boost_INCLUDE_DIR} ${PROJECT_INCLUDE_DIR})
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src CPP_LIST1)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/core CPP_LIST2)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/business CPP_LIST3)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/business/messages CPP_LIST4)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/util CPP_LIST5)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/business/util CPP_LIST6)
AUX_SOURCE_DIRECTORY(${CMAKE_SOURCE_DIR}/src/business/service CPP_LIST7)

add_executable(service ${CPP_LIST1} ${CPP_LIST2} ${CPP_LIST3} ${CPP_LIST4} ${CPP_LIST5} ${CPP_LIST6} ${CPP_LIST7})
target_link_libraries(service ${Boost_LIBRARIES} booster loki)

add_definitions(-Wall)


