cmake_minimum_required(VERSION 3.30)
project(sian)	# ${PROJECT_NAME}

# Environment
set(CMAKE_CXX_STANDARD			20)
set(CMAKE_CXX_STANDARD_REQUIRED	YES)
set(CMAKE_CXX_EXTENSIONS		OFF)
set(CMAKE_CXX_COMPILER			clang++)
set(CMAKE_C_COMPILER			clang)

# Directories
set(SRC_DIR		src)
set(INC_DIR		/Users/csian/projects/sian/include /opt/homebrew/include)
set(LIB_DIR		/Users/csian/projects/sian/lib)
set(BUILD_DIR	${CMAKE_BINARY_DIR})

# Headers
include_directories(${INC_DIR})

# Srcs
file(GLOB_RECURSE SRCS ${SRC_DIR}/*.cpp ${SRC_DIR}/*.c ${SRC_DIR}/*.s)
file(GLOB_RECURSE CUDA_SRCS ${SRC_DIR}/*.cu)

# Libraries
add_library(sian STATIC ${SRCS} ${CUDA_SRCS})	# STATIC/SHARED
target_include_directories(sian PRIVATE ${INC_DIR})		# PUBLIC/PRIVATE/INTERFACE
# set_target_properties(sian PROPERTIES OUTPUT_NAME "sian")

# Executable
add_executable(main main.cpp)
target_link_libraries(main PRIVATE sian)
target_include_directories(main PRIVATE ${INC_DIR})
target_link_directories(main PRIVATE ${LIB_DIR})
