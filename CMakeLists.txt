project(compute_S)
enable_language(C)
cmake_minimum_required(VERSION 2.6)

find_package(MPI)
include_directories(${MPI_INCLUDE_PATH})

set(UTILS_SRC printResult.c)
add_library(utils ${UTILS_SRC})

set(CMAKE_C_FLAGS "-std=c99")
add_executable(compute_S compute_S.c)

set(CMAKE_C_FLAGS "-std=c99 -fopenmp")
add_executable(compute_S_OpenMP compute_S_OpenMP.c)
add_executable(compute_S_MPI compute_S_MPI.c)

target_link_libraries(compute_S utils)
target_link_libraries(compute_S_OpenMP utils)

target_link_libraries(compute_S_MPI ${MPI_C_LIBRARIES})
target_link_libraries(compute_S_MPI utils)
