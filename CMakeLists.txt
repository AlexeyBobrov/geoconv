cmake_minimum_required (VERSION 2.8)

include(env.cmake)
include(version.cmake)

project (${ProjectName})

set (Boost_USE_STATIC_LIBS OFF)
set (Boost_USE_STATIC_RUNTIME OFF)
set (Boost_USE_MULTITHREADED ON)
set (Boost_NO_SYSTEM_PATHS ON)

add_definitions(-DBOOST_TEST_DYN_LINK)

set (BOOST_INCLUDEDIR "/opt/local/include")
set (BOOST_LIBRARYDIR "/opt/local/lib")


set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost 1.55 COMPONENTS system thread date_time filesystem program_options unit_test_framework REQUIRED)

configure_file(
  "${PROJECT_SOURCE_DIR}/inc/geoconv_version.h.in"
  "${PROJECT_BINARY_DIR}/geoconv_version.h"
  )

include_directories(${PROJECT_BINARY_DIR}
  inc
  test
  ${Boost_INCLUDE_DIRS}
  )

set (EXECUTABLE_OUTPUT_PATH "../bin")

set (INCLUDES
  inc
  test
  ${Boost_INCLUDE_DIRS})

set (SOURCES 
  src/convert.cpp
  src/utils/parse_cmd.cpp
  src/types.cpp
  )

set (SOURCES_TEST 
  ${SOURCES}
  test/test_geoconv.cpp
  test/test_dataset.cpp
  )

set (LIBRARIES
  pthread
  ${Boost_LIBRARIES}
  )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set (CMAKE_CXX_FLAGS "-std=c++14 -stdlib=libc++ -Wall -Wextra")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  set (CMAKE_CXX_FLAGS "-std=c++14 -Wall")
else()
  message(FATAL_ERROR "Unknown compiler, compiler id = ${CMAKE_CXX_COMPILER_ID}")
endif()

add_executable(${ProjectName} ${INCLUDES} ${SOURCES} src/main.cpp)
target_link_libraries(${ProjectName} ${LIBRARIES})

add_executable(${ProjectName}_test ${INCLUDES} ${SOURCES_TEST} test/test_main.cpp)
target_link_libraries(${ProjectName}_test ${LIBRARIES})

if (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
  EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
endif()
 
