# Setup
cmake_minimum_required(VERSION 3.0.2)

project(simdoc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -pedantic -Wextra -std=c++11")

find_package(Boost REQUIRED COMPONENTS system filesystem program_options)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/")
find_package(TBB REQUIRED)

# Binaries
include_directories(
  ${PROJECT_SOURCE_DIR}/lib/stemming
  ${Boost_INCLUDE_DIRS}
  ${TBB_INCLUDE_DIRS}
  )

add_executable(simdoc
  ${PROJECT_SOURCE_DIR}/src/text-processor.cc
  ${PROJECT_SOURCE_DIR}/src/result-document.cc
  ${PROJECT_SOURCE_DIR}/src/frequency-table.cc
  ${PROJECT_SOURCE_DIR}/src/document-frequency.cc
  ${PROJECT_SOURCE_DIR}/src/data-source.cc
  ${PROJECT_SOURCE_DIR}/src/filesystem.cc
  ${PROJECT_SOURCE_DIR}/src/tf-idf.cc
  ${PROJECT_SOURCE_DIR}/src/main.cc
  )

target_link_libraries(simdoc
  ${Boost_LIBRARIES}
  ${TBB_LIBRARIES}
  )
