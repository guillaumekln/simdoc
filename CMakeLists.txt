# Setup
cmake_minimum_required(VERSION 3.0.2)

project(simdoc)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -std=c++11")

find_package(Boost REQUIRED COMPONENTS system filesystem thread)

# Binaries
include_directories(
  ${PROJECT_SOURCE_DIR}/lib/stemming
  ${Boost_INCLUDE_DIRS}
  )

add_executable(simdoc
  ${PROJECT_SOURCE_DIR}/src/text-processor.cc
  ${PROJECT_SOURCE_DIR}/src/result-document.cc
  ${PROJECT_SOURCE_DIR}/src/word-cache.cc
  ${PROJECT_SOURCE_DIR}/src/frequency-table.cc
  ${PROJECT_SOURCE_DIR}/src/document-frequency.cc
  ${PROJECT_SOURCE_DIR}/src/filesystem.cc
  ${PROJECT_SOURCE_DIR}/src/tf-idf.cc
  ${PROJECT_SOURCE_DIR}/src/main.cc
  )

target_link_libraries(simdoc
  ${Boost_LIBRARIES}
  )
