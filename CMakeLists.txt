cmake_minimum_required(VERSION 2.6)

# Project details
project("tx1inst")
set(tx1inst_VERSION_MAJOR 0)
set(tx1inst_VERSION_MINOR 1)
set(tx1inst_VERSION_PATCH 0)

# Add options
option(BUILD_SHARED "Build a shared (ON) or static library (OFF)" ON)
option(BUILD_EXAMPLES "Enable compilation of example programs" ON)
option(VERBOSE "Compile in verbose mode" OFF)
if(VERBOSE)
  message("-- Building in verbose mode")
  add_definitions(-DVERBOSE)
endif()

################################################################################

# Gather all source files
file(GLOB SOURCES src/*.c)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create library
if(BUILD_SHARED)
  add_library(${PROJECT_NAME} SHARED ${SOURCES})
else(BUILD_SHARED)
  add_library(${PROJECT_NAME} STATIC ${SOURCES})
endif()

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

################################################################################

# Build example programs
if(BUILD_EXAMPLES)
  add_executable(tx1inst example/tx1inst.c)
  target_link_libraries(tx1inst ${PROJECT_NAME} m)
endif()

################################################################################

