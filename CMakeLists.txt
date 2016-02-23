cmake_minimum_required(VERSION 2.6)
project(compute_S)

find_package(MPI REQUIRED)
find_package(OpenMP REQUIRED)
enable_language(C)

include_directories(${MPI_INCLUDE_PATH})

set(CMAKE_C_FLAGS "-std=c99")
add_executable(compute_S compute_S.c utils.h)

set(CMAKE_C_FLAGS "-std=c99")
add_executable(compute_S_MPI compute_S_MPI.c utils.h)
# https://cmake.org/pipermail/cmake/2011-June/045037.html
target_link_libraries(compute_S_MPI ${MPI_LIBRARIES})

if(MPI_COMPILE_FLAGS)
	set_target_properties(compute_S_MPI PROPERTIES
		      COMPILE_FLAGS "${MPI_COMPILE_FLAGS}")
endif()

if(MPI_LINK_FLAGS)
	set_target_properties(compute_S_MPI PROPERTIES
		      LINK_FLAGS "${MPI_LINK_FLAGS}")
endif()

set(CMAKE_C_FLAGS "-std=c99")
add_executable(compute_S_OpenMP compute_S_OpenMP.c utils.h)

# https://cmake.org/cmake/help/v3.0/module/FindOpenMP.html
#message(${OpenMP_C_FLAGS})
if(OpenMP_C_FLAGS)
	set_target_properties(compute_S_OpenMP PROPERTIES
				LINK_FLAGS "${OpenMP_C_FLAGS}")
endif()

target_link_libraries(compute_S ${catkin_LIBRARIES})
target_link_libraries(compute_S_MPI ${MPI_C_LIBRARIES})
target_link_libraries(compute_S_OpenMP ${catkin_LIBRARIES})
