cmake_minimum_required(VERSION 2.6)

# Project details
project("tx1inst")
set(tx1inst_VERSION_MAJOR 0)
set(tx1inst_VERSION_MINOR 1)
set(tx1inst_VERSION_PATCH 0)

# Add options
option(WITH_CUDA "Build with CUDA (ON) or without (OFF)" ON)
option(BUILD_SHARED "Build a shared (ON) or static library (OFF)" ON)
option(BUILD_EXAMPLES "Enable compilation of example programs" ON)
option(VERBOSE "Compile in verbose mode" OFF)
if(VERBOSE)
  message("-- Building in verbose mode")
  add_definitions(-DVERBOSE)
endif()

################################################################################

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -O3 -Wall")

################################################################################

# Gather all source files
file(GLOB SOURCES src/*.c)

file(GLOB HEADERS include/*.h)

# Include header files
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Create library
# if(BUILD_SHARED)
#   add_library(${PROJECT_NAME} SHARED ${SOURCES})
# else(BUILD_SHARED)
#   add_library(${PROJECT_NAME} STATIC ${SOURCES})
# endif()
if(BUILD_SHARED)
  set(LIB_TYPE SHARED)
else()
  set(LIB_TYPE STATIC)
endif(BUILD_SHARED)

if(WITH_CUDA)

  find_package(CUDA REQUIRED)

  if(CUDA_FOUND)

    set(GENCODE_SM53 -gencode=arch=compute_53,code=sm_53
            -gencode=arch=compute_53,code=compute_53)

    option(CSMATH_GENCODE_SM53
      "ON to generate code for Compute Capability 5.2 devices (e.g. Titan X)"
      ON)

    if(CUDPP_GENCODE_SM53)
      set(GENCODE ${GENCODE} ${GENCODE_SM53})
    endif(CUDPP_GENCODE_SM53)

    cuda_add_library(${PROJECT_NAME}
      ${LIB_TYPE}
      ${HEADERS}
      ${SOURCES}
      # ${KERNELS}
      OPTIONS ${GENCODE})
  endif(CUDA_FOUND)
else()
  # add_library(${PROJECT_NAME}
  #   ${LIB_TYPE}
  #   ${HEADERS})
  # set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
endif(WITH_CUDA)

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/${PROJECT_NAME})

# Install library headers
file(GLOB HEADERS include/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

################################################################################

# Build example programs
if(BUILD_EXAMPLES)
  cuda_add_executable(tx1inst_app example/tx1inst.c)
  target_link_libraries(tx1inst_app ${PROJECT_NAME} ${CUDA_LIBRARIES})
  cuda_add_cublas_to_target(tx1inst_app)

  cuda_add_executable(mdlbench example/mdlbench.c)
  target_link_libraries(mdlbench ${PROJECT_NAME} ${CUDA_LIBRARIES})
  cuda_add_cublas_to_target(mdlbench)
endif()

################################################################################

