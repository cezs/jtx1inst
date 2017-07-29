cmake_minimum_required(VERSION 2.6)

# Project details
project("jtx1inst")
set(jtx1inst_VERSION_MAJOR 0)
set(jtx1inst_VERSION_MINOR 1)
set(jtx1inst_VERSION_PATCH 0)

# Add options
option(BUILD_SHARED "Build a shared (ON) or static library (OFF)" ON)
option(BUILD_EXAMPLES "Enable compilation of example programs" ON)
option(VERBOSE "Compile in verbose mode" OFF)
if(VERBOSE)
  message("-- Building in verbose mode")
  add_definitions(-DVERBOSE)
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -O3 -Wall")

# Gather all source files
file(GLOB SOURCES src/*.c)

file(GLOB HEADERS include/*.h)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create library
if(BUILD_SHARED)
  set(LIB_TYPE SHARED)
else()
  set(LIB_TYPE STATIC)
endif(BUILD_SHARED)

add_library(${PROJECT_NAME}
      ${LIB_TYPE}
      ${HEADERS}
      ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib)

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include)

# Build example programs
if(BUILD_EXAMPLES)
  add_executable(jtx1inst_demo samples/jtx1inst_demo.c)
  target_link_libraries(jtx1inst_demo ${PROJECT_NAME})
endif()

