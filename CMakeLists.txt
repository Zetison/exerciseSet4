cmake_minimum_required(VERSION 2.6)
project(compute_S)

find_package(MPI)
enable_language(C)

include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_C_FLAGS "-std=c99")
add_executable(compute_S compute_S.c utils.h)

set(CMAKE_C_FLAGS "-std=c99")
add_executable(compute_S_MPI compute_S_MPI.c utils.h)

set(CMAKE_C_FLAGS "-std=c99 -fopenmp")
add_executable(compute_S_OpenMP compute_S_OpenMP.c utils.h)

target_link_libraries(compute_S m)

target_link_libraries(compute_S_MPI ${MPI_C_LIBRARIES})
