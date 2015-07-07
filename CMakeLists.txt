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
  ${PROJECT_SOURCE_DIR}/src/tfidf/text-processor.cc
  ${PROJECT_SOURCE_DIR}/src/tfidf/result-document.cc
  ${PROJECT_SOURCE_DIR}/src/tfidf/word-cache.cc
  ${PROJECT_SOURCE_DIR}/src/tfidf/frequency-table.cc
  ${PROJECT_SOURCE_DIR}/src/tfidf/document-frequency.cc
  ${PROJECT_SOURCE_DIR}/src/tfidf/filesystem.cc
  ${PROJECT_SOURCE_DIR}/src/tfidf/tf-idf.cc
  ${PROJECT_SOURCE_DIR}/src/tfidf/main.cc
  )

target_link_libraries(simdoc
  ${Boost_LIBRARIES}
  )
